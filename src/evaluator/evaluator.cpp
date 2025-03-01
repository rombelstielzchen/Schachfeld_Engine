// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "../board/board.h"

int CEvaluator::evaluate() const {
    int score = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            score += evaluate_square(j, k);
        }
    }
    return score;
}

int CEvaluator::evaluate_square(const SSquare &square) const {
    return evaluate_square(square.file, square.rank);
}

int CEvaluator::evaluate_square(const int file, const int rank) const {
    assert(file_in_range(file));
    assert(rank_in_range(rank));
    char square_content = board.get_square(file, rank);
    assert(square_content <= LAST_PIECE_TYPE);
    int result = main_piece_square_value_table_set[square_content][file][rank];
//    std::cout << square_content << ": " << result << "\n";
    assert((square_content != EMPTY_SQUARE) || (result == 0));
    assert((square_content == EMPTY_SQUARE) || (result != 0));
    return result;
}

bool CEvaluator::evaluates_approximately_to(const int score) const {
    int real_score = evaluate();
    constexpr int half_pawn = 50;
    return (abs(real_score - score) < half_pawn);
}

int CEvaluator::evaluate_white_pawn(const SSquare square) {
    assert(square_in_range(square));
    return main_piece_square_value_table_set[WHITE_POWER][square.file][square.rank];
}

