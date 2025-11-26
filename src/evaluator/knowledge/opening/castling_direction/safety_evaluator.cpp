// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "safety_evaluator.h"
#include "../../../../board/board.h"
#include "../../../../board/board_logic.h"
#include "../../../../board/square_constants.h"

const SKingSquareGroup KING_SQUARE_GRUP_BLACK_KINGSIDE = {
    G7, G6, F7, F6, H7, H6, F7, H8
};

const SKingSquareGroup KING_SQUARE_GRUP_BLACK_QUEENSIDE = {
    B7, B6, C7, C6, A7, A6 , A7, C8
};

const SKingSquareGroup KING_SQUARE_GRUP_WHITE_KINGSIDE = {
    G2, G3, F2, F3, H2, H3, F1, H2
};

const SKingSquareGroup KING_SQUARE_GRUP_WHITE_QUEENSIDE = {
    B2, B3, C2, C3, A2, A3, A1, C2
};

int CSafetyEvaluator::king_safety(bool player, int king_position) {
    // TODO: consider other factors, e.g. open-lines and opponents piece-activity
    if (player == WHITE_PLAYER) {
        switch (king_position) {
            case QUEENSIDE:
                return pawn_shelter_safety(WHITE_PLAYER, KING_SQUARE_GRUP_WHITE_QUEENSIDE);
            case UNCASTLED:
                return UNSAFE_KING_POSITION;
            case KINGSIDE:
                return pawn_shelter_safety(WHITE_PLAYER, KING_SQUARE_GRUP_WHITE_KINGSIDE);
        }
    }
    assert(player == BLACK_PLAYER);
    switch (king_position) {
        case QUEENSIDE:
            return pawn_shelter_safety(BLACK_PLAYER, KING_SQUARE_GRUP_BLACK_QUEENSIDE);
        case UNCASTLED:
            return UNSAFE_KING_POSITION;
        case KINGSIDE:
            return pawn_shelter_safety(BLACK_PLAYER, KING_SQUARE_GRUP_BLACK_KINGSIDE);
     }
    assert(THIS_MUST_NOT_HAPPEN);
    return UNSAFE_KING_POSITION;
}

int CSafetyEvaluator::pawn_shelter_safety(bool player,
        const SKingSquareGroup ksg) {
    assert(square_in_range(ksg.important_center_pawn_2));
    assert(square_in_range(ksg.important_center_pawn_3));
    assert(square_in_range(ksg.important_flank_pawn_2));
    assert(square_in_range(ksg.important_flank_pawn_3));
    assert(square_in_range(ksg.minor_flank_pawn_2));
    assert(square_in_range(ksg.minor_flank_pawn_3));
    assert(ksg.important_center_pawn_2.file == ksg.important_center_pawn_3.file);
    assert(ksg.important_flank_pawn_2.file == ksg.important_flank_pawn_3.file);
    assert(ksg.minor_flank_pawn_2.file == ksg.minor_flank_pawn_3.file);
    assert(ksg.important_center_pawn_2.rank == ksg.important_flank_pawn_2.rank);
    assert(ksg.important_center_pawn_2.rank == ksg.minor_flank_pawn_2.rank);
    assert(ksg.important_center_pawn_3.rank == ksg.important_flank_pawn_3.rank);
    assert(ksg.important_center_pawn_3.rank ==ksg.minor_flank_pawn_3.rank);
    assert(abs(ksg.important_center_pawn_2.rank - ksg.important_center_pawn_3.rank) == 1);
    assert(abs(ksg.important_center_pawn_2.file - ksg.important_flank_pawn_2.file) == 1);
    assert(abs(ksg.important_center_pawn_2.file - ksg.important_flank_pawn_2.file) == 1);
    assert(abs(ksg.important_flank_pawn_2.file - ksg.minor_flank_pawn_2.file) == 2);
    char pawn = (player == WHITE_PLAYER) ? WHITE_POWER : BLACK_POWER;
    if (CBoardLogic::is_pawn_missing(pawn, ksg.important_center_pawn_2) && CBoardLogic::is_pawn_missing(pawn, ksg.important_center_pawn_3)) {
        return UNSAFE_KING_POSITION;
    }
    // Example: f2, g2, h2
    if (CBoardLogic::is_pawn_structure(pawn, ksg.important_center_pawn_2, ksg.important_flank_pawn_2, ksg.minor_flank_pawn_2)) {
        return EXCELLENT_KING_POSITION;
    }
    // Examples: f2, g2 / g2, h2 / f2, g3, h2
    if (CBoardLogic::is_pawn_structure(pawn, ksg.important_center_pawn_2, ksg.important_flank_pawn_2)
        || CBoardLogic::is_pawn_structure(pawn, ksg.important_center_pawn_2, ksg.minor_flank_pawn_2)
        || CBoardLogic::is_pawn_structure(pawn, ksg.important_flank_pawn_2, ksg.important_center_pawn_3, ksg.minor_flank_pawn_2)) {
        return GOOD_KING_POSITION;
    }
    // Examples: g2, h3 / f2, g3
    if (CBoardLogic::is_pawn_structure(pawn, ksg.important_center_pawn_2, ksg.minor_flank_pawn_3)
        || CBoardLogic::is_pawn_structure(pawn, ksg.important_flank_pawn_2, ksg.important_center_pawn_3)) {
        return MEDIOCRE_KING_POSITION;
    }
    return UNSAFE_KING_POSITION;
}

