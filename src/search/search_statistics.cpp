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
    start_time = std::chrono::high_resolution_clock::now();
}

void CSearchStatistics::reset_current_depth() {
    // TODO
}

void CSearchStatistics::set_best_move(const std::string &best_move, const int score) {
    assert(move_in_range(text_to_basic_move(best_move)));
    std::string info = "bestmove " + best_move + " score cp " + std::to_string(score);
    CUciProtocol::send_info(info);
}

void CSearchStatistics::set_depth(const int depth) {
    assert(depth > 0);
    std::string info = "depth " + std::to_string(depth);
    CUciProtocol::send_info(info);
}

void CSearchStatistics::set_current_move(const std::string &current_move) {
    assert(move_in_range(text_to_basic_move(current_move)));
    std::string info = "currmove " + current_move;
    CUciProtocol::send_info(info);
}

void CSearchStatistics::set_nodes(const int64_t nodes) {
    assert(nodes > 0);
    now_time = std::chrono::high_resolution_clock::now();
   std::chrono::duration<float> used_time_seconds = now_time - start_time; 
    assert(used_time_seconds.count() > 0);
    int64_t nodes_per_second = nodes / used_time_seconds.count();
   int64_t used_time_milliseconds = static_cast<int64_t>(used_time_seconds.count() * 1000);
    std::string info = "nodes " + std::to_string(nodes) + " time " + std::to_string(used_time_milliseconds) + " nps " + std::to_string(nodes_per_second);
    CUciProtocol::send_info(info);
}

void CSearchStatistics::log_branching_factor(const int  nodees, const int depth) const {
    // Approximate value, not considering extensions and reductions
    double branching_factor = pow(M_E, log(nodees) / depth);
    std::string message = "branching_factor: " + std::to_string(branching_factor);
    CUciProtocol::send_info(message);
}

