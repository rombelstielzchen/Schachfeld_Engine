// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Utikity-class for derived board-information to keep the board-class lean

#include"board_logic.h"
#include "board.h"

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

int CBoardLogic::my_back_rank() {
    return (board.get_side_to_move() == WHITE_TO_MOVE) ? RANK_1 : RANK_8;
}

bool castling_squares_empty(int TODO) {
    return false;
}

