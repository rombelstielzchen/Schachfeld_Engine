// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "iterative_deepening.h"
#include "search.h"
#include "search_statistics.h"

int64_t nodes_calculated = 0; //!!!
                           CIterativeDeepening::CIterativeDeepening() {
    best_move = NULL_MOVE;
}

constexpr int min_meaningful_depth_to_avoid_illegal_moves = 2;

SMove CIterativeDeepening::search(int depth) {
    assert(depth >= 0);
    depth = std::max(depth,  min_meaningful_depth_to_avoid_illegal_moves);
    best_move = NULL_MOVE;
    move_generator.generate_all();
    for (int current_depth = min_meaningful_depth_to_avoid_illegal_moves; current_depth <= depth; ++current_depth) {
        move_generator.move_list.reuse_list();
        root_node_search(current_depth);
    }
    return best_move;
}

void CIterativeDeepening::root_node_search(int depth) {
    assert(depth >= min_meaningful_depth_to_avoid_illegal_moves);
    CSearch search;
    search_statistics.reset();
    search_statistics.set_depth(depth);
    nodes_calculated = 0;
    bool side_to_move = board.get_side_to_move();
    best_move = NULL_MOVE; //!!!
    int alpha = WHITE_MIN_SCORE;
    int beta = BLACK_MIN_SCORE;
    int best_score = (side_to_move == WHITE_TO_MOVE) ? WHITE_MIN_SCORE : BLACK_MIN_SCORE;
    int n_moves = move_generator.move_list.list_size();
    assert(n_moves >= 0);
    for (int j = 0; j < n_moves; ++j) {
        // No alpha-beta-cutoffs here. Top-level search has to examine all moves,
        // but feed the recursive search with the current alpha-beta values.
        SMove move_candidate = move_generator.move_list.get_next();
        assert(is_null_move(move_candidate) == false);
        assert(move_in_range(move_candidate));
//        search_statistics.set_current_move(move_as_text(move_candidate));
        board.move_maker.make_move(move_candidate);
        ++nodes_calculated;
        int candidate_score = search.alpha_beta(depth - 1, alpha, beta); 
        if ((side_to_move == WHITE_TO_MOVE) && (candidate_score > best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            alpha = candidate_score;
        } else if ((side_to_move == BLACK_TO_MOVEE) && (candidate_score < best_score)) {
            best_move = move_candidate;
            best_score = candidate_score;
            beta = candidate_score;
        }
///        search_statistics.set_best_move(move_as_text(best_move), best_score);
        search_statistics.set_nodes(nodes_calculated);
        board.move_maker.unmake_move();
    }
    search_statistics.log_branching_factor(nodes_calculated, depth);
}
