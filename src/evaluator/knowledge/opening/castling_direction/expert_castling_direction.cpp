// Project: Schachfeld_Engine
// 
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"expert_castling_direction.h"
#include "safety_evaluator.h"
#include "../../../piece_square_value_tables.h"
#include "../../../score_constants.h"
#include "../../../../board/board.h"
#include "../../../../board/board_logic.h"
#include "../../../piece_square_value_tables.h"
#include "../../../../technical_functions/standard_headers.h"

bool CExpertCastlingDirection::is_responsible() const {
    bool any_castling_possible = !CBoardLogic::is_endgame()
        || board.get_castling_rights(MOVE_TYPE_WHITE_SHORT_CASTLING)
        || board.get_castling_rights(MOVE_TYPE_WHITE_LONG_CASTLING)
        || board.get_castling_rights(MOVE_TYPE_BLACK_SHORT_CASTLING)
        || board.get_castling_rights(MOVE_TYPE_BLACK_LONG_CASTLING);
    return any_castling_possible;
}

void CExpertCastlingDirection::apply_knowledge() {
    DEBUG_METHOD();
    adapt_castling_squares(WHITE_PLAYER, QUEENSIDE);
    adapt_castling_squares(WHITE_PLAYER, KINGSIDE);
    adapt_castling_squares(BLACK_PLAYER, QUEENSIDE);
    adapt_castling_squares(BLACK_PLAYER, KINGSIDE);
}

void CExpertCastlingDirection::adapt_castling_squares(bool player, int king_position) {
    // TODO: support central squares, maybe
    assert((king_position == QUEENSIDE)  || (king_position == KINGSIDE));
    int safety_estimate = CSafetyEvaluator::king_safety(player, king_position);
    assert(safety_estimate <= EXCELLENT_KING_POSITION);
    assert(safety_estimate >= UNSAFE_KING_POSITION);
    int adaptation_factor = safety_estimate - EXCELLENT_KING_POSITION;
    assert(adaptation_factor <= 0);
    int malus = adaptation_factor * 12;
    assert(malus <= 0);
    assert(malus >= -SCORE_HALF_PAWN);
    if (player == WHITE_PLAYER) {
        if (king_position == KINGSIDE) {
            adapt_castling_squares(main_piece_square_value_table_set[WHITE_KING], KING_SQUARE_GROUP_WHITE_KINGSIDE, malus);
        }else {
            adapt_castling_squares(main_piece_square_value_table_set[WHITE_KING], KING_SQUARE_GROUP_WHITE_QUEENSIDE, malus);
        }
    } else {
        assert(player == BLACK_PLAYER);
        if (king_position == KINGSIDE) {
            adapt_castling_squares(main_piece_square_value_table_set[BLACK_KING], KING_SQUARE_GROUP_BLACK_KINGSIDE, -malus);
        } else {
            adapt_castling_squares(main_piece_square_value_table_set[BLACK_KING], KING_SQUARE_GROUP_BLACK_QUEENSIDE, -malus);
        }
    }
}

void CExpertCastlingDirection::adapt_castling_squares(TPieceSquareValueTable &psv, const SKingSquareGroup &square_group, int malus) {
    assert(square_in_range(square_group.important_flank_pawn_2));
    assert(square_in_range(square_group.minor_flank_pawn_3));
    CPsvModifier::add_bonus_to_area(psv, square_group.bottom_left_king_area, square_group.top_right_king_area, malus);
}

