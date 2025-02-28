// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "iterative_deepening.h"
#include "search.h"
#include "search_statistics.h"
#include "../universal_chess_interface/command_interface.h"
#include "../universal_chess_interface/uci_protocol.h"

CIterativeDeepening::CIterativeDeepening() {
    best_move = NULL_MOVE;
    search_statistics.reset_all();
}

constexpr int min_meaningful_depth_to_avoid_illegal_moves = 2;

SMove CIterativeDeepening::search(int depth) {
    assert(depth >= 0);
    depth = std::max(depth,  min_meaningful_depth_to_avoid_illegal_moves);
    search_statistics.reset_all();
    best_move = NULL_MOVE;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    if (only_one_legal_move() && (depth < INFINITE_DEPTH)) {
        return only_move();
    }
    std::string root_position = board.get_fen_position();
    for (int current_depth = min_meaningful_depth_to_avoid_illegal_moves; current_depth <= depth; ++current_depth) {
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop) {
            break;
        }
        assert(board.get_fen_position() == root_position);
        root_node_search(current_depth);
        assert(best_move != NULL_MOVE);
    }
    assert(board.get_fen_position() == root_position);
    return best_move;
}

void CIterativeDeepening::root_node_search(int depth) {
    assert(depth >= min_meaningful_depth_to_avoid_illegal_moves);
    CSearch search;
    search_statistics.reset_current_depth(depth);
    bool side_to_move = board.get_side_to_move();
    SAlphaBetaWindow alpha_beta_window = INFINIE_AKPHA_BETA_WINDOW;
    int best_score = (side_to_move == WHITE_PLAYER) ? WHITE_MIN_SCORE : BLACK_MIN_SCORE;
    move_generator.move_list.reuse_list();
    int n_moves = move_generator.move_list.list_size();
    assert(n_moves >= 0);
    constexpr int uci_first_movenumber = 1;
    for (int j = uci_first_movenumber; j <= n_moves; ++j) {
        // No alpha-beta-cutoffs here. Top-level search has to examine all moves,
        // but feed the recursive search with the current alpha-beta values.
        search_statistics.reset_for_next_move();
        SMove move_candidate = move_generator.move_list.get_next();
        assert(move_candidate != NULL_MOVE);
        assert(move_in_range(move_candidate));
        board.move_maker.make_move(move_candidate);
        constexpr int distance_to_first_children = 1;
        int candidate_score = search.alpha_beta(depth - 1, distance_to_first_children, alpha_beta_window); 
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop) {
            // Break HERE. Do not update bestmove based on potentially crappy data
            board.move_maker.unmake_move();
            break;
        }
        search_statistics.set_current_move(move_candidate, candidate_score, j);
        if ((side_to_move == WHITE_PLAYER) && (candidate_score > best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            alpha_beta_window.alpha = candidate_score;
            move_generator.move_list.shift_current_move_to_top();
            search_statistics.set_best_move(best_move, best_score);
        } else if ((side_to_move == BLACK_PLAYER) && (candidate_score < best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            alpha_beta_window.beta = candidate_score;
            move_generator.move_list.shift_current_move_to_top();
            search_statistics.set_best_move(best_move, best_score);
        }
        board.move_maker.unmake_move();
    }
    search_statistics.add_nodes(n_moves);
    CUciProtocol::send_info(move_generator.move_list.as_text());
    search_statistics.log_branching_factor();
    search_statistics.log_subtree_size_bestmove();
}

SMove CIterativeDeepening::search_nodes(int64_t nodes) {
    search_statistics.reset_all();
    best_move = NULL_MOVE;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    if (only_one_legal_move()) {
        return only_move();
    }
    int current_depth = min_meaningful_depth_to_avoid_illegal_moves;
    do {
        root_node_search(current_depth);
        ++current_depth;
    }  while ((search_statistics.get_nodes_calculated() < nodes) && !DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop);
    return best_move;
}

SMove CIterativeDeepening::search_movetime(const int64_t movetime_ms) {
    search_statistics.reset_all();
    best_move = NULL_MOVE;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    if (only_one_legal_move()) {
        return only_move();
    }
    int current_depth = min_meaningful_depth_to_avoid_illegal_moves;
    do {
        root_node_search(current_depth);
        ++current_depth;
    }  while ((enough_time_left_for_one_more_iteration(movetime_ms)) && !DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop);
    return best_move;
}

bool CIterativeDeepening::enough_time_left_for_one_more_iteration(const int64_t available_movetime) const {
   constexpr int estimated_branching_factor = 8;
    return (available_movetime > estimated_branching_factor * search_statistics.used_time_milliseconds());
}

SMove CIterativeDeepening::search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t blacl_increment_milliseconds,
        const int64_t moves_to_go) {
   // TODO: extra class, move to CCommandInterface
    int64_t total_time_ms;
    if (board.get_side_to_move() == WHITE_PLAYER) {
        total_time_ms = white_time_milliseconds + moves_to_go * white_increment_milliseconds;
    } else {
        total_time_ms = black_time_milliseconds + moves_to_go * blacl_increment_milliseconds;
    }
    assert(total_time_ms > 0);
    int estimated_moves_to_go = (moves_to_go > 0) ? moves_to_go : 30;
    constexpr int time_trouble_reserve = 1;
    estimated_moves_to_go += time_trouble_reserve;
    int64_t time_for_next_move_ms = total_time_ms / estimated_moves_to_go;
    ++time_for_next_move_ms;
    assert(time_for_next_move_ms > 0);
    return search_movetime(time_for_next_move_ms);
}

bool CIterativeDeepening::only_one_legal_move() const {
    return move_generator.move_list.list_size() == 1;
}

SMove CIterativeDeepening::only_move() {
    assert(only_one_legal_move());
    return move_generator.move_list.get_next();
}

