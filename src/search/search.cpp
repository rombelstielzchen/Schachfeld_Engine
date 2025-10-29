// Project: Schachfeld_Engine // Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "killer_heuristics.h"
#include "search_statistics.h"
#include "../board/board_logic.h"
#include "../evaluator/evaluator.h"
#include "../evaluator/score_constants.h"
#include "../move_generator/move_generator.h"
#include "../universal_chess_interface/command_interface.h"

constexpr int QUIESCENCE_DEPTH = 31;

constexpr bool CSearch::score_causes_beta_cutoff(int const score, int const beta) const {
    return (score >= beta);
}

int CSearch::alpha_beta_negamax(int const remaining_depth, int const distance_to_root, int alpha, int const beta) {
    DEBUG_METHOD();
    assert(remaining_depth >= 0);
    assert(distance_to_root > 0);
    assert(alpha <= beta);
    if (remaining_depth <= 0) {
        // No negamax-negation here. We did not yet make a move; still same side to act
        return quiescence_negamax(QUIESCENCE_DEPTH, distance_to_root, alpha, beta);
    }
    int best_score = SCORE_TECHNICAL_MIN;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    if (move_generator.move_list.king_capture_on_list()) {
        return SCORE_ENEMY_KING_CAPTURED;
    }
    int const n_moves = move_generator.move_list.list_size();
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next__capture_killer_silent(distance_to_root);
        assert(is_null_move(move_candidate) == false);
        assert(move_in_range(move_candidate));
        DEBUG_MESSAGE("make_move: ", move_as_text(move_candidate));
        board.move_maker.make_move(move_candidate);
        int candidate_score;
        if (remaining_depth > 1) {
            if (DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop) {
                board.move_maker.unmake_move();
                constexpr int score_does_not_matter_wont_get_used = 314159;
                return score_does_not_matter_wont_get_used;
            }
            assert(alpha <= beta); 
            candidate_score = -alpha_beta_negamax(remaining_depth - 1, distance_to_root + 1, -beta, -alpha);
        } else {
            // TODO: one of tzhe 2 calls t oquiescense might be superfluous.
            // This might change with fractional deepening
            candidate_score = -quiescence_negamax(QUIESCENCE_DEPTH, distance_to_root + 1, -beta, -alpha);
        }
        board.move_maker.unmake_move();
        if (candidate_score > best_score) {
            if (score_causes_beta_cutoff(candidate_score, beta)) {
                search_statistics.add_nodes(j + 1);
                killer_heuristic.store_killer(distance_to_root, move_candidate);
                return candidate_score;
            }
            best_score = candidate_score;
            alpha = std::max(alpha, best_score);
        }
    }
    assert(move_generator.move_list.get_next() == NULL_MOVE);
    search_statistics.add_nodes(n_moves);
    if (best_score != SCORE_OWN_KING_WILL_GET_CAPTURED) {
        return best_score;
    }
    if (CBoardLogic::own_king_in_check()) {
        return losing_mate_score(distance_to_root);
    }
    return SCORE_STALEMATE;
}

int CSearch::quiescence_negamax(int const remaining_depth, int const distance_to_root, int alpha, int const beta) {
    DEBUG_METHOD();
    assert(remaining_depth > 0);
    assert(distance_to_root > 0);
    assert(alpha <= beta);
    int best_score = board.evaluator.nega_score();
    if (score_causes_beta_cutoff(best_score, beta)) {
        return best_score;
    }
    CMoveGenerator move_generator;
    // TODO: on the first level of quiescence we generate the moves twice
    move_generator.generate_captures();
    if (move_generator.move_list.king_capture_on_list()) {
        // Last move of regular search was  illegal.
        return SCORE_ENEMY_KING_CAPTURED;
    }
    best_score = quiescence_negamax_recursive_no_stalemate_detection(remaining_depth, distance_to_root, alpha, beta);
    // Quiescense assumes, that both players can stand pat / "sit out" if all else fails.
    // Therefore no mate and stalemate scores possible.
    assert(abs(best_score) < SCORE_KING);
    return best_score;
}

int CSearch::quiescence_negamax_recursive_no_stalemate_detection(int const remaining_depth, int const distance_to_root, int alpha, int const beta) {
    DEBUG_METHOD();
    assert(remaining_depth > 0);
    assert(distance_to_root > 0);
    assert(alpha <= beta);
    int best_score = board.evaluator.nega_score();
    if (score_causes_beta_cutoff(best_score, beta)) {
        return best_score;
    }
    CMoveGenerator move_generator;
    move_generator.generate_captures();
    int const n_moves = move_generator.move_list.list_size();
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next__best_capture();
        assert(is_null_move(move_candidate) == false);
        assert(move_in_range(move_candidate));
        assert(is_any_capture(move_candidate));
        assert(move_candidate.potential_gain > 0);
        DEBUG_MESSAGE("make_move: ", move_as_text(move_candidate));
        board.move_maker.make_move(move_candidate);
        int candidate_score;
        if (remaining_depth > 1) {
            candidate_score = -quiescence_negamax(remaining_depth - 1, distance_to_root + 1, -beta, -alpha);
        } else {
            candidate_score = static_exchange_evaluation_negamax(move_candidate.target, -beta, -alpha);
        }
        board.move_maker.unmake_move();
        if (candidate_score > best_score) {
            if (score_causes_beta_cutoff(candidate_score, beta)) {
                search_statistics.add_nodes(j + 1);
                return candidate_score;
            }
            best_score = candidate_score;
            alpha = std::max(alpha, best_score);
        }
    }
    assert(is_any_capture(move_generator.move_list.get_next()) == false);
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::static_exchange_evaluation_negamax(const SSquare &target_square, int alpha, int const beta) {
    assert(square_in_range(target_square));
    assert(alpha <= beta);
    int const initial_score = board.evaluator.nega_score(); 
    if (score_causes_beta_cutoff(initial_score, beta)) {
        return -initial_score;
    }
    alpha = std::max(alpha, initial_score);
    CMoveGenerator move_generator;
    move_generator.generate_recaptures(target_square);
    SMove recapture = move_generator.move_list.get_least_valuable_aggressor();
    if (is_null_move(recapture)) {
        return initial_score;
    }
    assert(move_in_range(recapture));
    assert(recapture.target == target_square);
        DEBUG_MESSAGE("make_move: ", move_as_text(recapture));
    board.move_maker.make_move(recapture);
    search_statistics.add_nodes(1);
    // Recursion guaranteed to terminate, as recaptures are limited
    int const score_after_capture = -static_exchange_evaluation_negamax(target_square, -beta, -alpha);
    board.move_maker.unmake_move();
   int const final_Score = std::max(initial_score, score_after_capture);
    return final_Score;
}

bool CSearch::no_legal_moves() const {
    CMoveGenerator move_generator;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    return (move_generator.move_list.list_size() ==  0);
}

//### Old minimax functions, still used for testing ########

int CSearch::alpha_beta_minimax(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    assert(remaining_depth >= 0);
    assert(distance_to_root > 0);
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int const score = alpha_beta_negamax(remaining_depth, distance_to_root, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int const score = alpha_beta_negamax(remaining_depth, distance_to_root, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

int CSearch::quiescence_minimax(int const remaining_depth, int const distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int const score = quiescence_negamax(remaining_depth, distance_to_root, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int const score = quiescence_negamax(remaining_depth, distance_to_root, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

int CSearch::static_exchange_evaluation_minimax(const SSquare &target_square, const SAlphaBetaWindow alpha_beta_window) {
    assert(square_in_range(target_square));
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int const score = static_exchange_evaluation_negamax(target_square, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int const score = static_exchange_evaluation_negamax(target_square, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

int CSearch::search_position(const std::string fen_position, int remaining_depth) {
    assert(fen_position != "");
    assert(remaining_depth >= 0);
    bool valid_postion = board.set_fen_position(fen_position);
    if (!valid_postion) {
        return SCORE_TECHNICAL_MIN;
    }
    constexpr int initial_distance_to_root = 1;
    return alpha_beta_negamax(remaining_depth, initial_distance_to_root, INFINITE_ALPHA_BETA_WINDOW.alpha, INFINITE_ALPHA_BETA_WINDOW.beta);
}

