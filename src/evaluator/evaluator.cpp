// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "../board/board.h"

CEvaluator::CEvaluator() {
    init_main_psv_set();
    value = 0;
}

void CEvaluator::initial_full_evaluation() {
   value = 0; 
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            value += evaluate_square(j, k);
        }
    }
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

int CEvaluator::evaluate_white_pawn(const SSquare square) {
    assert(square_in_range(square));
    return main_piece_square_value_table_set[WHITE_POWER][square.file][square.rank];
}
 void CEvaluator::incremental_add(char piece, const SSquare square) {
     assert(square_in_range(square));
     assert(is_any_piece(piece) || (piece == EMPTY_SQUARE));
     value += main_piece_square_value_table_set[piece][square.file][square.rank];
 }

 void CEvaluator::incremental_clear_square(const SSquare square) {
     assert(square_in_range(square));
    value -= evaluate_square(square);
 }

