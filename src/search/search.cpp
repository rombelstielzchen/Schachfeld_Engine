// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "../move_generator/move_generator.h"

int evaluate() {
    int score = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            char piece = board.get_square(j, k);
            if (!is_any_piece(piece)) {
                continue;
            }
            score += isupper(piece) ? +1: -1;
        }
    }
    return score;
}

SMove CSearch::search() {
    SMove best_move = NULL_MOVE;
    int best_score = INT_MIN;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    assert(n_moves >= 0);
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next();
        board.move_maker.make_move(move_candidate);
        int candidate_score = evaluate();
        std::cerr << move_as_text(move_candidate) << ": " << candidate_score << "\n";
        if (candidate_score > best_score) {
            best_score = candidate_score;
            best_move = move_candidate;
        }
        board.move_maker.unmake_move();
    }
    return best_move;
}
