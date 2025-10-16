// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "iterative_deepening.h"
#include "depth_control.h"
#include "search.h"
#include "search_statistics.h"
#include "../universal_chess_interface/command_interface.h"
#include "../universal_chess_interface/uci_protocol.h"

constexpr int64_t minimum_search_depth = 1;

CIterativeDeepening::CIterativeDeepening() {
    mate_found = false;
    search_statistics.reset_all();
}

/*** Public search-interface below ****/

SMove CIterativeDeepening::search_depth(int64_t depth) {
    assert(depth >= 0);
    depth = std::max(depth,  minimum_search_depth);
    depth_control.set_depth(depth);
    SMove best_move = search_common_entry_point();
    return best_move;
}

SMove CIterativeDeepening::search_nodes(const int64_t nodes) {
    assert(nodes > 0);
    depth_control.set_nodes(nodes);
    return search_common_entry_point();
}

SMove CIterativeDeepening::search_movetime(const int64_t movetime_ms) {
    assert(movetime_ms > 0);
    depth_control.set_movetime_ms(movetime_ms);
    SMove best_move = search_common_entry_point();
    assert(best_move != NULL_MOVE);
    return best_move;
}

SMove CIterativeDeepening::search_time(
        const int64_t white_time_milliseconds,
        const int64_t black_time_milliseconds,
        const int64_t white_increment_milliseconds,
        const int64_t black_increment_milliseconds,
        const int64_t moves_to_go) {
    assert(white_time_milliseconds >= 0);
    assert(black_time_milliseconds >= 0);
    assert(white_increment_milliseconds >= 0);
    assert(black_increment_milliseconds >= 0);
    assert(moves_to_go >= 0);
    int64_t total_time_ms;
    if (board.get_side_to_move() == WHITE_PLAYER) {
        total_time_ms = white_time_milliseconds + moves_to_go * white_increment_milliseconds;
    } else {
        total_time_ms = black_time_milliseconds + moves_to_go * black_increment_milliseconds;
    }
    assert(total_time_ms > 0);
    int64_t estimated_moves_to_go = (moves_to_go > 0) ? moves_to_go : 30;
    constexpr int time_trouble_reserve = 1;
    estimated_moves_to_go += time_trouble_reserve;
    int64_t time_for_next_move_ms = total_time_ms / estimated_moves_to_go;
    ++time_for_next_move_ms;
    assert(time_for_next_move_ms > 0);
    SMove best_move = search_movetime(time_for_next_move_ms);
    assert(best_move != NULL_MOVE);
    return best_move;
}

/*** End of public search interface ***/

SMove CIterativeDeepening::search_common_entry_point() {
    mate_found = false;
    search_statistics.reset_all();move_generator.generate_all();
    if (move_generator.move_list.king_capture_on_list()) {
        // This should happen only in case of some test-cases
        constexpr int no_killer_distance_to_root = 0;
        SMove king_capture = move_generator.move_list.get_next__capture_killer_silent(no_killer_distance_to_root);
        assert(move_in_range(king_capture));
        assert(king_capture.potential_gain >= SCORE_HALF_KING);
        return king_capture;
    }
    move_generator.move_list.prune_illegal_moves();
    if (only_one_legal_move()  && !depth_control.infinite_depth()) {
        return only_move();
    }
    if (move_generator.move_list.list_size() == 0) {
        return NULL_MOVE;
    }
    return search_anti_repetition();
}

SMove CIterativeDeepening::search_anti_repetition() {
    SMove repetitive_move = board.move_maker.get_repetitive_move();
    if (repetitive_move != NULL_MOVE) {
        assert(move_in_range(repetitive_move));
        assert(board.get_square(repetitive_move.source) != EMPTY_SQUARE);
        assert(move_generator.move_list.move_on_list(repetitive_move));
        move_generator.move_list.prune_silent_piece_moves(repetitive_move.source);
        assert(move_generator.move_list.move_on_list(repetitive_move) == false);
    }
    SMove search_result = search_iterative();
    if ((search_result.potential_gain < 0) && (repetitive_move != NULL_MOVE)) {
        // No better alternative found
        return repetitive_move;
    }
    return search_result;
}

SMove CIterativeDeepening::search_iterative() {
    // static in order to handle a badly timed stop-command
    static SMove best_move = NULL_MOVE;
    std::string const root_position = board.get_fen_position();
    constexpr int one_before_minimum_search_depth = minimum_search_depth - 1;
    int current_depth = one_before_minimum_search_depth;
    while(depth_control.go_deeper(current_depth)) {
        ++current_depth;
        assert(current_depth > 0);
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop) {
            break;
        }
        assert(board.get_fen_position() == root_position);
        best_move = search_fixed_depth(current_depth);
        assert(best_move != NULL_MOVE);
        assert(move_in_range(best_move));
        if (mate_found  && !depth_control.infinite_depth()) {
           // TODO: this might need to be changed, when we look for better mates
           break; 
        }
    }
    assert(board.get_fen_position() == root_position);
    assert(best_move != NULL_MOVE);
    assert(move_in_range(best_move));
    return best_move;
}

SMove CIterativeDeepening::search_fixed_depth(int depth) {
    // Top-level search
    //   * managing alpha-beta-windows, but no cutoffs here ("all-node")
    //   * Sorting and reusing the move-list, therefore...
    //     - no hash-moves here
    //     - no killer-moves here (impossible)
    assert(depth >= minimum_search_depth);
    CSearch search;
    search_statistics.on_new_depth(depth);
    SAlphaBetaWindow alpha_beta_window = INFINITE_ALPHA_BETA_WINDOW;
    assert(is_valid_alpha_beta_window(alpha_beta_window));
    int best_score = SCORE_TECHNICAL_MIN;
    move_generator.move_list.reuse_list();
    int const n_moves = move_generator.move_list.list_size();
    constexpr int at_least_two_moves__other_cases_already_handled = 2;
    assert(n_moves >= at_least_two_moves__other_cases_already_handled);
    constexpr int uci_first_movenumber = 1;
    // static in order to handle a badly timed stop-command
    static SMove best_move = NULL_MOVE;
    for (int j = uci_first_movenumber; j <= n_moves; ++j) {
        // No alpha-beta-cutoffs here. Top-level search has to examine all moves,
        // but feed the recursive search with the current alpha-beta values.
        search_statistics.on_new_move();
        SMove const move_candidate = move_generator.move_list.get_next();
        assert(move_candidate != NULL_MOVE);
        assert(move_in_range(move_candidate));
        board.move_maker.make_move(move_candidate);
        constexpr int distance_to_first_children = 1;
        assert(is_valid_alpha_beta_window(alpha_beta_window));
        // Careful here, once the window becomes asymmetric in the future
        int const candidate_score = -search.alpha_beta_negamax(depth - 1, distance_to_first_children, -alpha_beta_window.beta, -alpha_beta_window.alpha); 
        if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop) {
            // Break HERE. Do not update bestmove based on potentially crappy data
            board.move_maker.unmake_move();
            break;
        }
        search_statistics.set_current_move(move_candidate, candidate_score, j);
        if (candidate_score > best_score) {
            best_score = candidate_score;
            best_move = move_candidate;
            best_move.potential_gain = best_score;
            alpha_beta_window.alpha = std::max(alpha_beta_window.alpha, candidate_score);
            assert(is_valid_alpha_beta_window(alpha_beta_window));
            move_generator.move_list.shift_current_move_to_top();
            search_statistics.set_best_move(best_move, best_score);
        }
        board.move_maker.unmake_move();
    }
    assert((move_generator.move_list.get_next() == NULL_MOVE) || DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop);
    search_statistics.add_nodes(n_moves);
    CUciProtocol::send_info(move_generator.move_list.as_text());
    search_statistics.on_finished_search();
    if (abs(best_score) > SCORE_HALF_KING) {
        mate_found = true;
    }
    assert(best_move != NULL_MOVE);
    assert(move_in_range(best_move));
    return best_move;
}

bool CIterativeDeepening::only_one_legal_move() const {
    return move_generator.move_list.list_size() == 1;
}

SMove CIterativeDeepening::only_move() {
    assert(only_one_legal_move());
    SMove result =  move_generator.move_list.get_next();
    // We reuse the list here, otherwise we get unexpected behaviour,
    // if we use this function again, e.g. for debug-output. 
    move_generator.move_list.reuse_list();
    return result;
}

