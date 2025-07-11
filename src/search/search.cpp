// Project: Schachfeld_Engine // Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "killer_heuristics.h"
#include "search_statistics.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move_generator.h"
#include "../board/board_logic.h"
#include "../universal_chess_interface/command_interface.h"

constexpr int HALF_KING = 10000;
constexpr int QUIESCENCE_DEPTH = 31;

inline int CSearch::losing_score(bool losing_side) {
    return (losing_side == WHITE_PLAYER) ? SCORE_BLACK_WIN : SCORE_WHITE_WIN;
}

int CSearch::alpha_beta(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    assert(remaining_depth >= 0);
    assert(distance_to_root > 0);
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    // TODO: Revisit this, related to stalemate-detection
    if (remaining_depth <= 0) {
        return quiescence(QUIESCENCE_DEPTH, distance_to_root, alpha_beta_window);
    }
    int best_score = board.evaluator.evaluate();
    if (abs(best_score) > HALF_KING) {
        return best_score;
    }
    bool side_to_move = board.get_side_to_move();
    best_score = (side_to_move == WHITE_PLAYER) ? WHITE_MIN_SCORE : BLACK_MIN_SCORE;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    // TODO: replace bad stalemate-logic below
    if ((distance_to_root == 1) && no_legal_moves()) {
        if (CBoardLogic::piece_attacked_by_side_not_to_move(CBoardLogic::king_square(side_to_move)) == false) {
            return SCORE_DRAW;
        } else {
            return losing_score(side_to_move);
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
            assert(is_valid_alpha_beta_window(alpha_beta_window)); 
            candidate_score = alpha_beta(remaining_depth - 1, distance_to_root + 1, alpha_beta_window);
        } else {
            candidate_score = quiescence(QUIESCENCE_DEPTH, distance_to_root + 1, alpha_beta_window);
        }
        board.move_maker.unmake_move();
        if ((side_to_move == WHITE_PLAYER) && (candidate_score > best_score)) {
            if (white_score_way_too_good(candidate_score, alpha_beta_window)) {
                search_statistics.add_nodes(j + 1);
                killer_heuristic.store_killer(distance_to_root, move_candidate);
                return alpha_beta_window.beta;
            }
            best_score = candidate_score;
            alpha_beta_window.alpha = std::max(alpha_beta_window.alpha, best_score);
        } else if ((side_to_move == BLACK_PLAYER) && (candidate_score < best_score)) {
            if (black_score_way_too_good(candidate_score, alpha_beta_window)) {
                search_statistics.add_nodes(j + 1);
                killer_heuristic.store_killer(distance_to_root,move_candidate);
                return alpha_beta_window.alpha;
            }
            best_score = candidate_score;
            alpha_beta_window.beta = std::min(alpha_beta_window.beta, best_score);
        }
    }
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::quiescence(int remaining_depth, int distance_to_root, SAlphaBetaWindow alpha_beta_window) {
    assert(remaining_depth > 0);
    assert(distance_to_root > 0);
    assert(is_valid_alpha_beta_window(alpha_beta_window));
    int best_score = board.evaluator.evaluate();
    if (abs(best_score) > HALF_KING) {
        // TODO: needed? Alredy handled or needed to prevent situations with 2 captured kings?
        return best_score;
    }
    bool side_to_move = board.get_side_to_move();
    CMoveGenerator move_generator;
    if (side_to_move == WHITE_PLAYER) {
        if (white_score_way_too_good(best_score, alpha_beta_window)) {
            return best_score;
        }
    } else {
        assert(side_to_move == BLACK_PLAYER);
        if (black_score_way_too_good(best_score, alpha_beta_window)) {
            return best_score;
        }
    }
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
            candidate_score = quiescence(remaining_depth - 1, distance_to_root + 1, alpha_beta_window);
        } else {
            candidate_score = static_exchange_evaluation_minimax(move_candidate.target, alpha_beta_window);            
        }
        board.move_maker.unmake_move();
        if ((side_to_move == WHITE_PLAYER) && (candidate_score > best_score)) {
            if (white_score_way_too_good(candidate_score, alpha_beta_window)) {
                search_statistics.add_nodes(j + 1);
                return alpha_beta_window.beta;
            }
            best_score = candidate_score;
            alpha_beta_window.alpha = std::max(alpha_beta_window.alpha, best_score);
        } else if ((side_to_move == BLACK_PLAYER) && (candidate_score < best_score)) {
            if (black_score_way_too_good(candidate_score, alpha_beta_window)) {
                search_statistics.add_nodes(j + 1);
                return alpha_beta_window.alpha;
            }
            best_score = candidate_score;
            alpha_beta_window.beta = std::min(alpha_beta_window.beta, best_score);
        }
    }
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::static_exchange_evaluation_minimax(const SSquare &target_square, const SAlphaBetaWindow alpha_beta_window) {
    assert(square_in_range(target_square));
    // TODO: Revisit this, related to stalemate-detection
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    int score = board.evaluator.evaluate();
    if (board.get_side_to_move() == WHITE_PLAYER) {
        if (white_score_way_too_good(score, alpha_beta_window)) {
            return alpha_beta_window.beta;
        }
    } else {
        if (black_score_way_too_good(score, alpha_beta_window)) {
            return alpha_beta_window.alpha;
        }
    }
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
    score = static_exchange_evaluation_minimax(target_square, alpha_beta_window);
    board.move_maker.unmake_move();
    return score;
}

inline bool CSearch::white_score_way_too_good(const int score, const SAlphaBetaWindow alpha_beta_window) const {
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    return (score >= alpha_beta_window.beta);
}

inline bool CSearch::black_score_way_too_good(const int score, const  SAlphaBetaWindow alpha_beta_window) const {
    assert(is_valid_alpha_beta_window(alpha_beta_window)); 
    return (score <= alpha_beta_window.alpha);
}

bool CSearch::no_legal_moves() {
    CMoveGenerator move_generator;
    move_generator.generate_all();
        move_generator.move_list.prune_illegal_moves();
        return (move_generator.move_list.list_size() ==  0);
}

