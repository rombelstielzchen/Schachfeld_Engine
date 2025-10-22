// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Utility-class for derived board-information to keep the board-class lean

#include"board_logic.h"
#include "board.h"
#include "../evaluator/score_constants.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/standard_headers.h"

constexpr bool UNEXPECTED_MOVE_TYPE = false;

char CBoardLogic::my_king() {
    return (board.get_side_to_move() == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
}

char CBoardLogic::my_rook() {
    return (board.get_side_to_move() == WHITE_PLAYER) ? WHITE_ROOK : BLACK_ROOK;
}

char CBoardLogic::my_pawn() {
    return (board.get_side_to_move() == WHITE_PLAYER) ? WHITE_POWER : BLACK_POWER;
}

int CBoardLogic::eng_passeng_pawn_rank() {
    return (board.get_side_to_move() == WHITE_PLAYER) ? RANK_5 : RANK_4;
}

int CBoardLogic::eng_passeng_forward_rank() {
    return (eng_passeng_pawn_rank() == RANK_5) ? RANK_6 : RANK_3;
}

int CBoardLogic::my_back_rank() {
    return (board.get_side_to_move() == WHITE_PLAYER) ? RANK_1 : RANK_8;
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
        default:
            assert(UNEXPECTED_MOVE_TYPE);
            return false;
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
            return false;
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
            return (board.get_side_to_move() == BLACK_PLAYER);
            break;
        case BLACK_POWER:
        case BLACK_KNIGHT:
        case BLACK_BISHOP:
        case BLACK_ROOK:
        case BLACK_QUEEN:
        case BLACK_KING:
            return (board.get_side_to_move() == WHITE_PLAYER);
            break;
    }
    return false;
}

bool CBoardLogic::is_valid_target_square(const int file, const int rank) {
    if (board.square_is_empty(file, rank)) {
        return true;
    }
    return square_occupied_by_opponent(file, rank);
}

SSquare CBoardLogic::king_square(bool white_or_black) {
    char wanted_king_dead_or_alive = (white_or_black == WHITE_PLAYER) ? WHITE_KING : BLACK_KING;
    for (uint8_t j = FILE_A; j <= FILE_H; ++j) {
        for (uint8_t k = RANK_1; k <= RANK_8; ++k) {
            if (board.get_square(j, k) == wanted_king_dead_or_alive) {
                SSquare location = {j, k};
                return location;
            }
        }
    }
    return NULL_SQUARE;
}

bool CBoardLogic::piece_attacked_by_side_to_move(const SSquare square) {
    CMoveGenerator response_generator;
    response_generator.generate_all();
    response_generator.move_list.filter_captures_by_target_square(square);
    return (response_generator.move_list.list_size() > 0);
}

bool CBoardLogic::piece_attacked_by_side_not_to_move(const SSquare square) {
    board.move_maker.make_null_move();
    bool result = piece_attacked_by_side_to_move(square);
    board.move_maker.unmake_null_move();
    return result;
}

bool CBoardLogic::castling_possible(const int move_type) {
    assert((move_type == MOVE_TYPE_WHITE_SHORT_CASTLING) 
        || (move_type == MOVE_TYPE_WHITE_LONG_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_LONG_CASTLING));
    return (board.get_castling_rights(move_type)
        && rook_on_castling_square(move_type)
        && (castling_squares_empty(move_type)));
}

bool CBoardLogic::own_king_in_check() {
    board.move_maker.make_null_move();
    bool result = opponents_king_in_check();
    board.move_maker.unmake_null_move();
    return result;
}

bool CBoardLogic::opponents_king_in_check() {
    bool opponent_colour = !board.get_side_to_move();
    SSquare opponent_king_square = CBoardLogic::king_square(opponent_colour);
    if (opponent_king_square == NULL_SQUARE) {
        // No king, probably simplified test-case
        return false;
    }
    assert(square_in_range(opponent_king_square));
    return (CBoardLogic::piece_attacked_by_side_to_move(opponent_king_square));
}

bool CBoardLogic::illegal_move(SMove move) {
    assert(move_in_range(move));
    board.move_maker.make_move(move);
    bool result = opponents_king_in_check();
    board.move_maker.unmake_move();
    return result;
}

bool CBoardLogic::is_endgame() {
   constexpr int max_officers_to_be_considered_endgame = 4; 
    int n_officers = 0;
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case WHITE_KNIGHT:
                case WHITE_BISHOP:
                case WHITE_ROOK:
                case WHITE_QUEEN:
                case BLACK_KNIGHT:
                case BLACK_BISHOP:
                case BLACK_ROOK:
                case BLACK_QUEEN:
                    ++n_officers;
                    break;
            }
        }
    }
#ifndef NDEBUG
    constexpr int n_possible_officers_after_promotion = 30;
#endif
    assert(n_officers <= n_possible_officers_after_promotion);
    return (n_officers <= max_officers_to_be_considered_endgame);
}

bool CBoardLogic::one_king_missing() {
    return abs((board.evaluator.evaluate()) >= SCORE_HALF_KING);
}

bool CBoardLogic::is_pawn_at(char white_or_black_pawn, SSquare square) {
    assert((white_or_black_pawn == WHITE_POWER) || (white_or_black_pawn == BLACK_POWER));
    assert(square_in_range(square));
    return (board.get_square(square) == white_or_black_pawn);
}

bool CBoardLogic::is_pawn_anywhere(char white_or_black_pawn, SSquare square1, SSquare square2, SSquare square3, SSquare square4, SSquare square5, SSquare square6) {
    assert((white_or_black_pawn == WHITE_POWER) || (white_or_black_pawn == BLACK_POWER));
    assert(square_in_range(square1));
    assert(square_in_range(square2));
    return (is_pawn_at(white_or_black_pawn, square1)
        || is_pawn_at(white_or_black_pawn, square2)
        || ((square3 != NULL_SQUARE) && is_pawn_at(white_or_black_pawn, square3))
        || ((square4 != NULL_SQUARE) && is_pawn_at(white_or_black_pawn, square4))
        || ((square5 != NULL_SQUARE) && is_pawn_at(white_or_black_pawn, square5))
        || ((square6 != NULL_SQUARE) && is_pawn_at(white_or_black_pawn, square6)));

}

bool CBoardLogic::is_pawn_structure(char white_or_black_pawn, SSquare square1, SSquare square2, SSquare square3, SSquare square4) {
    assert((white_or_black_pawn == WHITE_POWER) || (white_or_black_pawn == BLACK_POWER));
    assert(square_in_range(square1));
    assert(square_in_range(square2));
    return (is_pawn_at(white_or_black_pawn, square1)
        && is_pawn_at(white_or_black_pawn, square2)
        && ((square3 == NULL_SQUARE) || is_pawn_at(white_or_black_pawn, square3))
        && ((square4 == NULL_SQUARE) || is_pawn_at(white_or_black_pawn, square4)));
}

