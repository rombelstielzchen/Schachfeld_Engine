// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "search.h"
#include "../move_generator/move_generator.h"

// TODO; serious eval in own module
int evaluate() {
    int score = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            char piece = board.get_square(j, k);
            switch (piece) {
                case WHITE_KING:
                    score += 20000;
                    break;
                case WHITE_QUEEN:
                    score += 900;
                    break;
                case WHITE_ROOK:
                    score += 500;
                    break;
                case WHITE_BISHOP:
                    score += 310;
                    break;
                case WHITE_KNIGHT:
                    score += 290;
                    break;
                case WHITE_POWER:
                    score += 100;
                    break;
                case BLACK_KING:
                    score -= 20000;
                    break;
                case BLACK_QUEEN:
                    score -= 900;
                    break;
                case BLACK_ROOK:
                    score -= 500;
                    break;
                case BLACK_BISHOP:
                    score -= 310;
                    break;
                case BLACK_KNIGHT:
                    score -= 290;
                    break;
                case BLACK_POWER:
                    score -= 100;
                    break;
            }
        }
    }
    return score;
}

SMove CSearch::search() {
    bool side_to_move = board.get_side_to_move();
    SMove best_move = NULL_MOVE;
    int best_score = (side_to_move == WHITE_TO_MOVE) ? INT_MIN : INT_MAX;
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    assert(n_moves >= 0);
    for (int j = 0; j < n_moves; ++j) {
        SMove move_candidate = move_generator.move_list.get_next();
        board.move_maker.make_move(move_candidate);
        int candidate_score = evaluate();
        std::cerr << move_as_text(move_candidate) << ": " << candidate_score << "\n";
        if (((side_to_move == WHITE_TO_MOVE) && (candidate_score > best_score)) 
           || ((side_to_move == BLACK_TO_MOVEE) && (candidate_score < best_score))) {
            best_score = candidate_score;
            best_move = move_candidate;
        }
        board.move_maker.unmake_move();
    }
    return best_move;
}
