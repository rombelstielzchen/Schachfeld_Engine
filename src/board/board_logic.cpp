// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Utikity-class for derived board-information to keep the board-class lean

#include"board_logic.h"
#include "board.h"

constexpr bool UNEXPECTED_MOVE_TYPE = false;

char CBoardLogic::my_king() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? WHITE_KING : BLACK_KING;
}

char CBoardLogic::my_rook() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? WHITE_ROOK : BLACK_ROOK;
}

char CBoardLogic::my_pawn() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? WHITE_POWER : BLACK_POWER;
}

int CBoardLogic::eng_passeng_pawn_rank() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? RANK_5 : RANK_4;
}

int CBoardLogic::eng_passeng_forward_rank() {
    return (eng_passeng_pawn_rank() == RANK_5) ? RANK_6 : RANK_3;
}

int CBoardLogic::my_back_rank() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? RANK_1 : RANK_8;
}

bool CBoardLogic::castling_squares_empty(const char move_type) {
    switch (move_type) {
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            return (board.square_is_empty(FILE_F, RANK_1) && board.square_is_empty(FILE_G, RANK_1));
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            return (board.square_is_empty(FILE_D, RANK_1) && board.square_is_empty(FILE_C, RANK_1) && board.square_is_empty(FILE_B, RANK_1));
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            return (board.square_is_empty(FILE_F, RANK_8) && board.square_is_empty(FILE_G, RANK_8));
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            return (board.square_is_empty(FILE_D, RANK_8) && board.square_is_empty(FILE_C, RANK_8) && board.square_is_empty(FILE_B, RANK_8));
    }
}

bool CBoardLogic::rook_on_castling_square(const char move_type) {
    switch(move_type) {
        case MOVE_TYPE_WHITE_SHORT_CASTLING:
            return (board.get_square(FILE_H, RANK_1) == WHITE_ROOK);
        case MOVE_TYPE_WHITE_LONG_CASTLING:
            return (board.get_square(FILE_A, RANK_1) == WHITE_ROOK);
        case MOVE_TYPE_BLACK_SHORT_CASTLING:
            return (board.get_square(FILE_H, RANK_8) == BLACK_ROOK);
        case MOVE_TYPE_BLACK_LONG_CASTLING:
            return (board.get_square(FILE_A, RANK_8) == BLACK_ROOK);
        default:
            assert(UNEXPECTED_MOVE_TYPE);
            break;
    }
}

bool CBoardLogic::square_occupied_by_opponent(const int file, const int rank) {
    switch (board.get_square(file, rank)) {
        case WHITE_POWER:
        case WHITE_KNIGHT:
        case WHITE_BISHOP:
        case WHITE_ROOK:
        case WHITE_QUEEN:
        case WHITE_KING:
            return (board.get_side_to_move() == BLACK_TO_MOVEE);
            break;
        case BLACK_POWER:
        case BLACK_KNIGHT:
        case BLACK_BISHOP:
        case BLACK_ROOK:
        case BLACK_QUEEN:
        case BLACK_KING:
            return (board.get_side_to_move() == WHITE_TO_MOVE);
            break;
    }
    return false;
}

bool CBoardLogic::is_valid_target_square(const int file, const int rank) {
    if (board.get_square(file, rank) == EMPTY_SQUARE) {
        return true;
    }
    return square_occupied_by_opponent(file, rank);
}

