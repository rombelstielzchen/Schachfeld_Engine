// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search_statistics.h"
#include "../universal_chess_interface/uci_protocol.h"

CSearchStatistics::CSearchStatistics() {
    reset_all();
}

void CSearchStatistics::reset_all() {
    nodes_calculated = 0;
    nodes_at_start_of_current_depth = 0;
    max_depth = 1;
    start_time = std::chrono::high_resolution_clock::now();
}

void CSearchStatistics::reset_current_depth(int new_depth) {
    assert(new_depth > 0);
    assert(new_depth >= max_depth);
    max_depth = std::max(max_depth, new_depth);
    std::string info = "depth " + std::to_string(new_depth);
    CUciProtocol::send_info(info);
    nodes_at_start_of_current_depth = nodes_calculated;
}

void CSearchStatistics::set_best_move(const std::string &best_move, const int score) {
    assert(move_in_range(text_to_basic_move(best_move)));
    std::string info = "bestmove " + best_move + " score cp " + std::to_string(score);
    CUciProtocol::send_info(info);
}

void CSearchStatistics::set_current_move(const std::string &current_move, int score) {
    assert(move_in_range(text_to_basic_move(current_move)));
    std::string info = "currmove " + current_move + " score cp " + std::to_string(score) + node_statistics();
    CUciProtocol::send_info(info);
}

void CSearchStatistics::add_nodes(const int64_t nodes) {
    assert(nodes >= 0);
    nodes_calculated += nodes;
}

std::string CSearchStatistics::node_statistics() const {
    std::chrono::time_point<std::chrono::high_resolution_clock> now_time = std::chrono::high_resolution_clock::now();
   std::chrono::duration<float> used_time_seconds = now_time - start_time; 
    assert(used_time_seconds.count() > 0);
    int64_t nodes_per_second = nodes_calculated / used_time_seconds.count();
   int64_t used_time_milliseconds = static_cast<int64_t>(used_time_seconds.count() * 1000);
    std::string info = " nodes " + std::to_string(nodes_calculated) + " time " + std::to_string(used_time_milliseconds) + " nps " + std::to_string(nodes_per_second);
    return info;
}

void CSearchStatistics::log_branching_factor() const {
    // Approximate value, not considering extensions and reductions
    int64_t nodes_for_this_iteration = nodes_calculated - nodes_at_start_of_current_depth;
    double branching_factor = pow(M_E, log(nodes_for_this_iteration) / max_depth);
    std::string message = "branching_factor: " + std::to_string(branching_factor);
    CUciProtocol::send_info(message);
}

