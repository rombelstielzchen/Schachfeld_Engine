// Project: Schachfeld_Engine // Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "killer_heuristics.h"
#include "search_statistics.h"
#include "../board/board_logic.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move_generator.h"
#include "../universal_chess_interface/command_interface.h"

constexpr int HALF_KING = 10000;
constexpr int QUIESCENCE_DEPTH = 31;

inline bool CSearch::score_causes_beta_cutoff(const int score, const int beta) const { return (score >= beta); }

int CSearch::alpha_beta_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta) {
    assert(remaining_depth >= 0);
    assert(distance_to_root > 0);
    assert(alpha <= beta);
    // TODO: Revisit this, related to stalemate-detection
    if (remaining_depth <= 0) {
        // No negamax-negation here. We did not yet make a move; still same side to act
        return quiescence_negamax(QUIESCENCE_DEPTH, distance_to_root, alpha, beta);
    }
    int best_score = board.evaluator.nega_score();
    if (abs(best_score) > HALF_KING) {
        //  TODO: can this happen?
        return best_score;
    }
    best_score = WHITE_MIN_SCORE;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    // TODO: replace bad stalemate-logic below
    if ((distance_to_root == 1) && no_legal_moves()) {
        bool side_to_move = board.get_side_to_move();
        if (CBoardLogic::piece_attacked_by_side_not_to_move(CBoardLogic::king_square(side_to_move)) == false) {
            return SCORE_DRAW;
        } else {
            // Losing for the side whose moves we intend to analyze.
            // As we did not yet make a move, this is "winning" -- for th opponent.
          return WHITE_MIN_SCORE;
        }
    }
    // TODO: replace bad stalemate-logic above
    int n_moves = move_generator.move_list.list_size();
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next__capture_killer_silent(distance_to_root);
        assert(is_null_move(move_candidate) == false);
        assert(move_in_range(move_candidate));
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
            candidate_score = -quiescence_negamax(QUIESCENCE_DEPTH, distance_to_root + 1, -beta, -alpha);
        }
        board.move_maker.unmake_move();
        if (candidate_score > best_score) {
            if (score_causes_beta_cutoff(candidate_score, beta)) {
                search_statistics.add_nodes(j + 1);
                killer_heuristic.store_killer(distance_to_root, move_candidate);
                return beta;
            }
            best_score = candidate_score;
            alpha = std::max(alpha, best_score);
        }
    }
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::quiescence_negamax(const int remaining_depth, const int distance_to_root, int alpha, const int beta) {
    assert(remaining_depth > 0);
    assert(distance_to_root > 0);
    assert(alpha <= beta);
    int best_score = board.evaluator.nega_score();
    if (abs(best_score) > HALF_KING) {
        // TODO: needed? Alredy handled or needed to prevent situations with 2 captured kings?
        return best_score;
    }
    if (score_causes_beta_cutoff(best_score, beta)) {
        return best_score;
    }
    CMoveGenerator move_generator;
    move_generator.generate_captures();
    int n_moves = move_generator.move_list.list_size();
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next__best_capture();
        assert(is_null_move(move_candidate) == false);
        assert(move_in_range(move_candidate));
        assert(is_any_capture(move_candidate));
        assert(move_candidate.potential_gain > 0);
        board.move_maker.make_move(move_candidate);
        int candidate_score;
        // TODO: > 0?
        if (remaining_depth > 1) {
            candidate_score = -quiescence_negamax(remaining_depth - 1, distance_to_root + 1, -beta, -alpha);
        } else {
            candidate_score = static_exchange_evaluation_negamax(move_candidate.target, -beta, -alpha);
        }
        board.move_maker.unmake_move();
        if (candidate_score > best_score) {
            if (score_causes_beta_cutoff(candidate_score, beta)) {
                search_statistics.add_nodes(j + 1);
                return beta;
            }
            best_score = candidate_score;
            // TODO: revisit this
            alpha = std::max(alpha, best_score);
        }
    }
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::static_exchange_evaluation_negamax(const SSquare &target_square, int alpha, const int beta) {
    assert(square_in_range(target_square));
    assert(alpha <= beta);
    int score = board.evaluator.nega_score(); 
    if (score_causes_beta_cutoff(score, beta)) {
        return -beta;
    }
    // TODO: can score raise alpha or would this have caused a beta-cutoff earlier?
    CMoveGenerator move_generator;
    move_generator.generate_recaptures(target_square);
    SMove recapture = move_generator.move_list.get_least_valuable_aggressor();
    if (is_null_move(recapture)) {
        return score;
    }
    assert(move_in_range(recapture));
    assert(recapture.target == target_square);
    board.move_maker.make_move(recapture);
    search_statistics.add_nodes(1);
    // Recursion guaranteed to terminate, as recaptures are limited
    score = -static_exchange_evaluation_negamax(target_square, -beta, -alpha);
    board.move_maker.unmake_move();
    return score;
}

bool CSearch::no_legal_moves() const {
    CMoveGenerator move_generator;
    move_generator.generate_all();
        move_generator.move_list.prune_illegal_moves();
        return (move_generator.move_list.list_size() ==  0);
}

//### Old minimax funczions, still used for testing ########

int CSearch::alpha_beta_minimax(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    assert(remaining_depth >= 0);
    assert(distance_to_root > 0);
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int score = alpha_beta_negamax(remaining_depth, distance_to_root, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int score = alpha_beta_negamax(remaining_depth, distance_to_root, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

int CSearch::quiescence_minimax(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int score = quiescence_negamax(remaining_depth, distance_to_root, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int score = quiescence_negamax(remaining_depth, distance_to_root, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

int CSearch::static_exchange_evaluation_minimax(const SSquare &target_square, const SAlphaBetaWindow alpha_beta_window) {
    assert(square_in_range(target_square));
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    if (board.get_side_to_move() == WHITE_PLAYER) {
        int score = static_exchange_evaluation_negamax(target_square, alpha_beta_window.alpha, alpha_beta_window.beta);
        return score;
    }
    assert(board.get_side_to_move() == BLACK_PLAYER);
    int score = static_exchange_evaluation_negamax(target_square, -alpha_beta_window.beta, -alpha_beta_window.alpha);
    return -score;
}

