// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_maker.h"
#include "board.h"
#include "board_logic.h"

CMoveMaker::CMoveMaker() {
}

bool CMoveMaker::make_move(SMove move) {
    assert(move_in_range(move));
    char moving_piece = board.squares[move.source.file][move.source.rank];
    board.clear_square(move.source.file, move.source.rank);
    board.put_piece(move.target.file, move.target.rank, moving_piece);
    switch (move.move_type) {
        case MOVE_TYPE_NORMAL:
        case MOVE_TYPE_DOUBLE_JUMP:
            break;
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            board.clear_square(FILE_H, RANK_1);
            board.put_piece(FILE_F, RANK_1, WHITE_ROOK);
            break;
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            board.clear_square(FILE_A, RANK_1);
            board.put_piece(FILE_C, RANK_1, WHITE_ROOK);
            break;
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            board.clear_square(FILE_H, RANK_8);
            board.put_piece(FILE_F, RANK_8, BLACK_ROOK);
            break;
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            board.clear_square(FILE_A, RANK_8);
            board.put_piece(FILE_C, RANK_8, BLACK_ROOK);
            break;
        case MOVE_TYPE_ENG_PASSENG:
            board.clear_square(board.get_eng_passeng_file(),  CBoardLogic::eng_passeng_pawn_rank());
            break;
        case WHITE_QUEEN:
        case WHITE_KNIGHT:
        case WHITE_ROOK:
        case WHITE_BISHOP:
        case BLACK_QUEEN:
        case BLACK_KNIGHT:
        case BLACK_ROOK:
        case BLACK_BISHOP:
            board.put_piece(move.target.file, move.target. rank, move.move_type);
            break;
        default:
            assert(THIS_MUST_NOT_HAPPEN);
            break;
    }
    move_history.push_back(move);
    return true;
}

void CMoveMaker::unmake_move() {
    // TODO
}

