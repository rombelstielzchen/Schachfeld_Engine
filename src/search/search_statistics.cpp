// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search_statistics.h"
#include "../universal_chess_interface/uci_protocol.h"

constexpr int64_t anti_division_by_zero = 1;

const std::string separator = "********************************";

CSearchStatistics::CSearchStatistics() {
    reset_all();
}

void CSearchStatistics::reset_all() {
    nodes_total = anti_division_by_zero;
    nodes_at_start_of_current_depth = nodes_total;
    nodes_at_start_of_current_move = nodes_total;
    max_depth = 1;
    start_time = std::chrono::high_resolution_clock::now();
    subtree_size_bestmove = 0;
}

void CSearchStatistics::on_new_depth(int new_depth) {
    assert(new_depth > 0);
    assert(new_depth >= max_depth);
    max_depth = new_depth;
    std::string info = "depth " + std::to_string(new_depth);
    CUciProtocol::send_info(info);
    nodes_at_start_of_current_depth = nodes_total;
    nodes_at_start_of_current_move = nodes_total;
    subtree_size_bestmove = 0;
}

void CSearchStatistics::on_new_move() {
    nodes_at_start_of_current_move = nodes_total;
}

void CSearchStatistics::set_best_move(const SMove best_move, int score) {
    assert(move_in_range(best_move));
    std::string info = "bestmove " + move_as_text(best_move) + anti_adjudication_score(score);
    CUciProtocol::send_info(info);
    // TODO: remove this, once principal variation with hash-table is implemented
    info = "pv " + move_as_text(best_move) + anti_adjudication_score(score);
    CUciProtocol::send_info(info);
    subtree_size_bestmove = subtree_size();
}

void CSearchStatistics::set_current_move(const SMove current_move, int score, int movenumber) {
    assert(move_in_range(current_move));
#ifndef NDEBUG
    constexpr int uci_first_movenumber = 1;
#endif
    assert(movenumber >= uci_first_movenumber);
    std::string info = "currmove " 
        + move_as_text(current_move)
        + anti_adjudication_score(score)
        + " currmovenumber "
        + std::to_string(movenumber)
        + general_search_statistics();
    CUciProtocol::send_info(info);
    log_subtree_size();
}

std::string CSearchStatistics::general_search_statistics() const {
    std::string info = " nodes " 
        + std::to_string(nodes_total) 
        + " time " 
        + std::to_string(used_time_milliseconds()) 
        + " nps " 
        + std::to_string(nodes_per_second());
    return info;
}

std::string CSearchStatistics::anti_adjudication_score(int score) {
    // Some GUIs adjudicate the game, if the score is too good, too bad or too equal.
    // Let's thwart this! ;-)
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

void CSearchStatistics::log_branching_factors() const {
    assert(nodes_at_start_of_current_depth > 0);
    assert(nodes_total > nodes_at_start_of_current_depth);
    double branching_factor = static_cast<double>(nodes_for_this_iteration()) / nodes_at_start_of_current_depth;
    // branching_factor nay be < 1 in case of "stop"-command
    assert(branching_factor > 0);
    std::string message = "branching_factor: " + std::to_string(branching_factor);
    CUciProtocol::send_info(message);
}

void CSearchStatistics::log_subtree_size_bestmove() const {
    assert(nodes_for_this_iteration() > 0);
    double relative_size = static_cast<double>(subtree_size_bestmove) / nodes_for_this_iteration();
    double size_percent = 100 * relative_size;
    std::string message = " subtree_size_bestmove " 
        + std::to_string(subtree_size_bestmove) 
        + " percent " 
        + std::to_string(size_percent);
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
    int64_t nps = (nodes_total * 1000) / used_time_milliseconds();
    assert(nps > 0);
    return nps;
}

int64_t CSearchStatistics::subtree_size() const {
    int64_t size = nodes_total - nodes_at_start_of_current_move;
    assert(size >= 0);
    return size;
}

int64_t CSearchStatistics::nodes_for_this_iteration() const {
    assert(nodes_total > nodes_at_start_of_current_depth);
    return nodes_total - nodes_at_start_of_current_depth;
}

void CSearchStatistics::on_finished_search() const {
    CUciProtocol::send_info(separator);
    log_subtree_size_bestmove();
    log_branching_factors();
    CUciProtocol::send_info(separator);
}

void CSearchStatistics::log_principal_variation() const {
	// UCI-docu: e.g. "info depth 2 score cp 214 time 1242 nodes 2124 nps 34928 pv e2e4 e7e5 g1f3"
    std::string info = "depth "
        + std::to_string(max_depth);
    CUciProtocol::send_info(info);
}

