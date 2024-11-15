// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move_generator.h"

// TODO: extra class for statistics
uint64_t nodes_calculated = 0;

// We need some range here in order to distinguish different depths to mate,
// avoiding nonsense moves to longer nates or worse
constexpr int WHITE_MIN_SCORE = INT_MIN + 1000;
constexpr int BLACK_MIN_SCORE = INT_MAX - 1000;

SMove CSearch::search(int depth) {
    constexpr int min_meaningful_depth_to_avoid_illegal_moves = 2;
    depth = std::max(depth,  min_meaningful_depth_to_avoid_illegal_moves);
    search_statistics.reset();
    search_statistics.set_depth(depth);
    nodes_calculated = 0;
    bool side_to_move = board.get_side_to_move();
    SMove best_move = NULL_MOVE;
    int alpha = WHITE_MIN_SCORE;
    int beta = BLACK_MIN_SCORE;
    int best_score = (side_to_move == WHITE_TO_MOVE) ? WHITE_MIN_SCORE : BLACK_MIN_SCORE;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    assert(n_moves >= 0);
    for (int j = 0; j < n_moves; ++j) {
        // No alpha-beta-cutoffs here. Top-level search has to examine all moves,
        // but feed the recursive search with the current alpha-beta values.
        SMove move_candidate = move_generator.move_list.get_next();
        search_statistics.set_current_move(move_as_text(move_candidate));
        board.move_maker.make_move(move_candidate);
        ++nodes_calculated;
        int candidate_score = alpha_beta(depth - 1, alpha, beta); 
        if ((side_to_move == WHITE_TO_MOVE) && (candidate_score > best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            alpha = candidate_score;
        } else if ((side_to_move == BLACK_TO_MOVEE) && (candidate_score < best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            beta = candidate_score;
        }
        search_statistics.set_best_move(move_as_text(best_move), best_score);
        search_statistics.set_nodes(nodes_calculated);
        board.move_maker.unmake_move();
    }
    search_statistics.log_branching_factor(nodes_calculated, depth);
    return best_move;
}

int CSearch::alpha_beta(int remaining_depth, int alpha, int beta) {
    if (remaining_depth <= 0) {
        return board.evaluator.evaluate();
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
        ++nodes_calculated;
        int candidate_score = alpha_beta(remaining_depth - 1, alpha, beta);
        board.move_maker.unmake_move();
        if ((side_to_move == WHITE_TO_MOVE) && (candidate_score > best_score)) {
            if (white_scpre_way_too_good(candidate_score, beta)) {
                return beta;
            }
            best_score = candidate_score;
            alpha = std::max(alpha, best_score);
        } else if ((side_to_move == BLACK_TO_MOVEE) && (candidate_score < best_score)) {
            if (black_scpre_way_too_good(candidate_score, alpha)) {
                return alpha;
            }
            best_score = candidate_score;
            beta = std::min(beta, best_score);            
        }
    }
    return best_score;
}

inline bool CSearch::white_scpre_way_too_good(const int score, const int beta) const {
    return (score >= beta);
}

inline bool CSearch::black_scpre_way_too_good(const int score, const int alpha) const {
    return (score <= alpha);
}

