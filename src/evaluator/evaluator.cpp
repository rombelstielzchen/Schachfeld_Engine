// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "evaluator.h"
#include "piece_square_value_tables.h"
#include "../board/board.h"
#include "../universal_chess_interface/uci_protocol.h"

CEvaluator::CEvaluator() {
    // No full init() here, as the board might be not yet initialized,
    // but the value of the start-position is known
    value = 0; 
}

void CEvaluator::init() {
    oracle.configure_knowledge();
    value = 0;
    for (const SSquare s: ALL_SQUARES) {
        value += evaluate_square(s);
    }
}

void CEvaluator::log_board_evaluation() const {
    for (const SSquare s: ALL_SQUARES) {
        if (!board.square_is_empty(s)) {
            char piece = board.get_square(s);
            assert(is_any_piece(piece));
                int value = evaluate_square(s);
            assert(value != 0);
            std::string message = piece + square_as_text(s) + ": " + std::to_string( value);
            CUciProtocol::send_info(message);
        }
    }
}

int CEvaluator::evaluate_square(const SSquare &square) const {
    return evaluate_square(square.file, square.rank);
}

int CEvaluator::evaluate_square(const TFile file, const TRank rank) const {
    assert(file_in_range(file));
    assert(rank_in_range(rank));
    char square_content = board.get_square(file, rank);
    assert(square_content <= LAST_PIECE_TYPE);
    assert((square_content == EMPTY_SQUARE) || is_any_piece(square_content));
    assert(main_piece_square_value_table_set[WHITE_KING][FILE_E][RANK_1] > 0);
    int result = main_piece_square_value_table_set[square_content][file][rank];
    assert((square_content != EMPTY_SQUARE) || (result == 0));
    assert((square_content == EMPTY_SQUARE) || (result != 0));
    return result;
}

int CEvaluator::evaluate_white_pawn(const SSquare square) {
    assert(square_in_range(square));
    return main_piece_square_value_table_set[WHITE_POWER][square.file][square.rank];
}
 
void CEvaluator::incremental_add(const SSquare square) {
     assert(square_in_range(square));
     value += evaluate_square(square);
 }

 void CEvaluator::incremental_clear_square(const SSquare square) {
     assert(square_in_range(square));
    value -= evaluate_square(square);
 }

int CEvaluator::nega_score() const {
    int score = evaluate();
    if (board.get_side_to_move() == BLACK_PLAYER) {
        score = -score;
    }
    return score;
}

