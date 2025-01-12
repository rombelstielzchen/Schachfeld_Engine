// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search_statistics.h"
#include "../universal_chess_interface/uci_protocol.h"

constexpr int64_t anti_division_by_zero = 1;

CSearchStatistics::CSearchStatistics() {
    reset_all();
}

void CSearchStatistics::reset_all() {
    nodes_calculated = anti_division_by_zero;
    nodes_at_start_of_current_depth = nodes_calculated;
    nodes_at_start_of_current_move = nodes_calculated;
    max_depth = 1;
    start_time = std::chrono::high_resolution_clock::now();
}

void CSearchStatistics::reset_current_depth(int new_depth) {
    assert(new_depth > 0);
    assert(new_depth >= max_depth);
    max_depth = new_depth;
    std::string info = "depth " + std::to_string(new_depth);
    CUciProtocol::send_info(info);
    nodes_at_start_of_current_depth = nodes_calculated;
    nodes_at_start_of_current_move = nodes_calculated;
}

void CSearchStatistics::set_best_move(const SMove best_move, const int score) {
    assert(move_in_range(best_move));
    std::string info = "bestmove " + move_as_text(best_move) + anti_adjudication_score(score);
    CUciProtocol::send_info(info);
}

void CSearchStatistics::set_current_move(const SMove current_move, int score, int movenumber) {
    assert(move_in_range(current_move));
    constexpr int uci_first_movenumber = 1;
    assert(movenumber >= uci_first_movenumber);
    std::string info = "currmove " 
        + move_as_text(current_move)
        + anti_adjudication_score(score)
        + " currmovenumber "
        + std::to_string(movenumber)
        + node_statistics();
    CUciProtocol::send_info(info);
    log_subtree_size();
    nodes_at_start_of_current_move = nodes_calculated;
}

std::string CSearchStatistics::node_statistics() const {
    std::string info = " nodes " 
        + std::to_string(nodes_calculated) 
        + " time " 
        + std::to_string(used_time_milliseconds()) 
        + " nps " 
        + std::to_string(nodes_per_second());
    return info;
}

std::string CSearchStatistics::anti_adjudication_score(int score) {
    // Some GUIs adjudicate the game, if the score is too good, too bad or too equal.
    // Let's conterfeit this! ;-)
    constexpr int max_score = 599;
    constexpr int min_score = -max_score;
    constexpr int epsilon_score = 007;
    score = std::min(score, max_score);
    score = std::max(score, min_score);
    if (abs(score) < epsilon_score) {
        score = epsilon_score;
    }
    std::string result = " score cp " + std::to_string(score) + " ";
    return result;
}

void CSearchStatistics::log_branching_factor() const {
    assert(nodes_at_start_of_current_depth > 0);
    assert(nodes_calculated > nodes_at_start_of_current_depth);
    int64_t nodes_for_this_iteration = nodes_calculated - nodes_at_start_of_current_depth;
    double branching_factor = static_cast<double>(nodes_for_this_iteration) / nodes_at_start_of_current_depth;
    // branching_factor nay be < 1 in case of "stop"-command
    assert(branching_factor > 0);
    std::string message = "branching_factor: " + std::to_string(branching_factor);
    CUciProtocol::send_info(message);
}

int64_t CSearchStatistics::used_time_milliseconds() const {
    std::chrono::time_point<std::chrono::high_resolution_clock> now_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> used_time_seconds = now_time - start_time; 
    assert(used_time_seconds.count() > 0);
    int64_t milliseconds = static_cast<int64_t>(1000 * used_time_seconds.count());
    milliseconds += anti_division_by_zero; 
    assert(milliseconds > 0);
    return milliseconds;
}

void CSearchStatistics::log_subtree_size() const {
    std::string message = "subtree_size " + std::to_string(subtree_size());
    CUciProtocol::send_info(message);
}

int64_t CSearchStatistics::nodes_per_second() const {
    int64_t nps = (nodes_calculated * 1000) / used_time_milliseconds();
    assert(nps > 0);
    return nps;
}

int64_t CSearchStatistics::subtree_size() const {
    int64_t size = nodes_calculated - nodes_at_start_of_current_move;
    assert(size >= 0);
    return size;
}

