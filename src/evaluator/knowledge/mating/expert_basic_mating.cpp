// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_basic_mating.h"
#include "../../../board/board_logic.h"
#include "../../piece_square_value_tables.h"
#include "../../score_constants.h"
#include "../../../move_generator/move.h"
#include "../../../technical_functions/standard_headers.h"

bool CExpertBasicMating::is_responsible() const {
    if ((CBoardLogic::n_stones(WHITE_PLAYER) > 1) && (CBoardLogic::n_stones(BLACK_PLAYER) > 1)) {
        return false;
    }
    if (CBoardLogic::n_stones() <= 2) {
        return false;
    }
    if ((CBoardLogic::king_square(WHITE_PLAYER) == NULL_SQUARE) || (CBoardLogic::king_square(BLACK_PLAYER) == NULL_SQUARE)) {
        return false;
    }
    return true;
}

void CExpertBasicMating::apply_knowledge() {
    char winning_king = WHITE_KING;
    char losing_king = BLACK_KING;
    SSquare losing_king_square = CBoardLogic::king_square(BLACK_PLAYER);
    // Positive boni from whites POV
    // Getting the losing king towards the corner is important; far higher bonus
    int bonus_winning_king = 5;
    int bonus_losing_king = SCORE_HALF_PAWN;
    if (CBoardLogic::n_stones(WHITE_PLAYER) <= 1) {
        winning_king = BLACK_KING;
        losing_king = WHITE_KING;
        losing_king_square = CBoardLogic::king_square(WHITE_PLAYER);
        // Negative boni from blacks POV
        bonus_winning_king = -bonus_winning_king;
        bonus_losing_king = -bonus_losing_king;
    }
    assert(square_in_range(losing_king_square));
    SSquare target_corner = desired_mating_corner(losing_king_square);
    assert(square_in_range(target_corner));
    CPsvModifier::make_gradient(main_piece_square_value_table_set[losing_king], target_corner, bonus_losing_king);
    CPsvModifier::make_gradient(main_piece_square_value_table_set[winning_king], target_corner, bonus_winning_king);
}

SSquare CExpertBasicMating::desired_mating_corner(const SSquare losing_king_square) const {
    assert(square_in_range(losing_king_square));
    if ((losing_king_square.file <= FILE_D) && (losing_king_square.rank <= RANK_4)) {
        return A1;
    }
    if (losing_king_square.file <= FILE_D) {
        return A8;
    }
    if (losing_king_square.rank <= RANK_4) {
        return H1;
    }
    return H8;
}

