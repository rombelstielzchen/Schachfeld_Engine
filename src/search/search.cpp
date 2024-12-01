// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "search_statistics.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move_generator.h"

constexpr int HALF_KING = 10000;

int CSearch::alpha_beta(int remaining_depth, int alpha, int beta) {
    assert(remaining_depth >= 0);
    assert(alpha <= beta);
    int score = board.evaluator.evaluate();
    if (remaining_depth <= 0) {
        return score;
    }
    if (abs(score) > HALF_KING) {
        return score;
    }
    bool side_to_move = board.get_side_to_move();
    int best_score = (side_to_move == WHITE_TO_MOVE) ? WHITE_MIN_SCORE : BLACK_MIN_SCORE;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    if (n_moves <= 0) {
        best_score = board.evaluator.evaluate();
        best_score += (side_to_move == WHITE_TO_MOVE) ? - remaining_depth : remaining_depth;
        return best_score;
    }
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next();
        board.move_maker.make_move(move_candidate);
        int candidate_score;
        if (remaining_depth > 1) {
            candidate_score = alpha_beta(remaining_depth - 1, alpha, beta);
        } else if (is_any_capture(move_candidate)) {
            candidate_score = static_exchange_evaluation(move_candidate.target, alpha, beta);
        } else {
            candidate_score = board.evaluator.evaluate();
        }
        board.move_maker.unmake_move();
        if ((side_to_move == WHITE_TO_MOVE) && (candidate_score > best_score)) {
            if (white_score_way_too_good(candidate_score, beta)) {
                search_statistics.add_nodes(j + 1);
                return beta;
            }
            best_score = candidate_score;
            alpha = std::max(alpha, best_score);
        } else if ((side_to_move == BLACK_TO_MOVEE) && (candidate_score < best_score)) {
            if (black_score_way_too_good(candidate_score, alpha)) {
                search_statistics.add_nodes(j + 1);
                return alpha;
            }
            best_score = candidate_score;
            beta = std::min(beta, best_score);            
        }
    }
    search_statistics.add_nodes(n_moves);
    return best_score;
}

int CSearch::static_exchange_evaluation(const SSquare &target_square, int alpha, int beta) {
    assert(square_in_range(target_square));
    assert(alpha <= beta);
    int score = board.evaluator.evaluate();
    if (board.get_side_to_move() == WHITE_TO_MOVE) {
        if (white_score_way_too_good(score, beta)) {
            return beta;
        }
    } else {
        if (black_score_way_too_good(score, alpha)) {
            return alpha;
        }
    }
    CMoveGenerator move_generator;
    move_generator.generate_all();
    move_generator.move_list.filter_captures_by_target_square(target_square);
    SMove recapture = move_generator.move_list.get_least_valuable_aggressor();
    if (is_null_move(recapture)) {
        return score;
    }
    assert(move_in_range(recapture));
    assert(recapture.target.file == target_square.file);
    assert(recapture.target.rank == target_square.rank);
    board.move_maker.make_move(recapture);
    search_statistics.add_nodes(1);
    // Recursion guaranteed to terminate, as recaptures are limited
    score = static_exchange_evaluation(target_square, alpha, beta);
    board.move_maker.unmake_move();
    return score;
}

inline bool CSearch::white_score_way_too_good(const int score, const int beta) const {
    return (score >= beta);
}

inline bool CSearch::black_score_way_too_good(const int score, const int alpha) const {
    return (score <= alpha);
}

