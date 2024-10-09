// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_maker.h"
#include "board.h"

CMoveMaker::CMoveMaker() {
}

bool CMoveMaker::make_move(SMove move) {
    // TODO: castling, eng-passeng, promotion
    // TODO: lots of sanity checks
    DEBUG_METHOD();
    DEBUG_VALUE_OF(move.source.file);
    assert(move_in_range(move));
    char moving_piece = board.squares[move.source.file][move.source.rank];
    DEBUG_VALUE_OF(moving_piece);
    board.squares[move.source.file][move.source.rank] = EMPTY_SQUARE;
    board.squares[move.target.file][move.target.rank] = moving_piece;
    return true;
}

