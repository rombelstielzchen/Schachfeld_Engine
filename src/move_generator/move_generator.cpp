// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_generator.h"
#include "../board/board.h"
#include "../board/board_logic.h"
#include "../technical_functions/standard_headers.h"

CMoveGenerator::CMoveGenerator() {
}

void CMoveGenerator::generate_all() {
    bool side_to_move = board.get_side_to_move();
    if (side_to_move == WHITE_TO_MOVE) {
        generate_all_white_moves();
    } else {
        assert(side_to_move == BLACK_TO_MOVEE);
        generate_all_black_moves();
    }
}

void CMoveGenerator::generate_all_white_moves() {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case WHITE_POWER:
                    generate_pawn_moves(j, k, DIRECTION_NORTH);
                    break;
                case WHITE_KNIGHT:
                    generate_knight_moves(j, k);
                    break;
                case WHITE_BISHOP:
                    generate_bishop_moves(j, k);
                    break;
                case WHITE_ROOK:
                    generate_rook_moves(j, k);
                    break;
                case WHITE_QUEEN:
                    generate_queen_moves(j, k);
                    break;
                case WHITE_KING:
                    generate_king_moves(j, k);
                    break;
            }
        }
    }
    generate_potential_eng_passeng();
}

void CMoveGenerator::generate_all_black_moves() {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case BLACK_POWER:
                    generate_pawn_moves(j, k, DIRECTION_SOUTH);
                    break;
                case BLACK_KNIGHT:
                    generate_knight_moves(j, k);
                    break;
                case BLACK_BISHOP:
                    generate_bishop_moves(j, k);
                    break;
                case BLACK_ROOK:
                    generate_rook_moves(j, k);
                    break;
                case BLACK_QUEEN:
                    generate_queen_moves(j, k);
                    break;
                case BLACK_KING:
                    generate_king_moves(j, k);
                    break;
            }
        }
    }
    generate_potential_eng_passeng();
}

void CMoveGenerator::generate_pawn_captures(const int file, const int rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    const int next_rank = rank + positive_negative_direction;
    const int left_file = file - 1;
    const int right_file = file + 1;
    if (CBoardLogic::square_occupied_by_opponent(left_file, next_rank)) {
        move_list.store_pawn_move(file, rank, left_file, next_rank);
    }
    if (CBoardLogic::square_occupied_by_opponent(right_file, next_rank)) {
        move_list.store_pawn_move(file, rank, right_file, next_rank);
    }
}

void CMoveGenerator::generate_pawn_forward_moves(const int file, const int rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    const int next_rank = rank + positive_negative_direction;
    if (board.get_square(file, next_rank) == EMPTY_SQUARE) {
        move_list.store_pawn_move(file, rank, file, next_rank);
        const int second_next_rank = next_rank + positive_negative_direction;
        if (((rank == RANK_2) || (rank == RANK_7))
            && (board.get_square(file, second_next_rank) == EMPTY_SQUARE)) {
            // Normal store_move() here, no possible promotion
            move_list.store_silent_move(file, rank, file, second_next_rank, MOVE_TYPE_DOUBLE_JUMP);
        }
    }
}

void CMoveGenerator::generate_pawn_moves(const int file, const int rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    generate_pawn_captures(file, rank, positive_negative_direction);
    generate_pawn_forward_moves(file, rank, positive_negative_direction);
}

void CMoveGenerator::generate_king_moves(const int file, const int rank) {
    generate_potential_move(file, rank, file    , rank + 1);
    generate_potential_move(file, rank, file + 1, rank + 1);
    generate_potential_move(file, rank, file - 1, rank + 1);
    generate_potential_move(file, rank, file - 1, rank      );
    generate_potential_move(file, rank, file + 1, rank    );
    generate_potential_move(file, rank, file + 1, rank - 1);
    generate_potential_move(file, rank, file    , rank - 1);
    generate_potential_move(file, rank, file - 1, rank - 1);
    generate_castlings(file, rank);
}

void CMoveGenerator::generate_castlings(const int file, const int rank) {
    if ((file != FILE_E) || (rank != CBoardLogic::my_back_rank())) {
        return;
    }
    int my_short = MOVE_TYPE_WHITE_SHORT_CASTLING;
    int my_long = MOVE_TYPE_WHITE_LONG_CASTLING;
    if (rank == RANK_8) {
        my_short = MOVE_TYPE_BLACK_SHORT_CASTLING;
        my_long = MOVE_TYPE_BLACK_LONG_CASTLING;
    }
    if (castling_possible(my_short)) {
        move_list.store_silent_move(FILE_E, rank, FILE_G, rank, my_short);
    }
    if (castling_possible(my_long)) {
        move_list.store_silent_move(FILE_E, rank, FILE_C, rank, my_long);
    }
}

void CMoveGenerator::generate_knight_moves(const int file, const int rank) {
    generate_potential_move(file, rank, file - 1, rank + 2);
    generate_potential_move(file, rank, file + 1, rank + 2);
    generate_potential_move(file, rank, file - 2, rank + 1);
    generate_potential_move(file, rank, file + 2, rank + 1);
    generate_potential_move(file, rank, file - 2, rank - 1);
    generate_potential_move(file, rank, file + 2, rank - 1);
    generate_potential_move(file, rank, file - 1, rank - 2);
    generate_potential_move(file, rank, file + 1, rank - 2);
}

void CMoveGenerator::generate_bishop_moves(const int file, const int rank) {
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_WEST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_WEST);
}

void CMoveGenerator::generate_rook_moves(const int file, const int rank) {
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_NEUTRAL);
    generate_sliding_moves(file, rank, DIRECTION_NEUTRAL, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_NEUTRAL, DIRECTION_WEST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_NEUTRAL);
}

void CMoveGenerator::generate_queen_moves(const int file, const int rank) {
    generate_bishop_moves(file, rank);
    generate_rook_moves(file, rank);
}

void CMoveGenerator::generate_potential_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    // Checks the target-square, needed for king and knight
    // and for the final square of sliding moves
    assert(file_in_range(source_file));
    assert(rank_in_range(source_rank));
    // Target may be out of range (garden-fence), therefore no assertions
    if (board.square_is_empty(target_file, target_rank)) {
        move_list.store_silent_move(source_file, source_rank, target_file, target_rank);
    } else if (CBoardLogic::square_occupied_by_opponent(target_file, target_rank)) {
        move_list.store_capture(source_file, source_rank, target_file, target_rank);
    }
}

void CMoveGenerator::generate_sliding_moves(const int file, const int rank, const int direction_north_sourh, const int direction_east_west) {
    int next_file = file + direction_east_west;
    int next_rank = rank + direction_north_sourh;
    while (board.square_is_empty(next_file, next_rank)) {
        move_list.store_silent_move(file, rank, next_file, next_rank);
        next_file += direction_east_west;
        next_rank += direction_north_sourh;
    }
    if (CBoardLogic::square_occupied_by_opponent(next_file, next_rank)) {
        move_list.store_capture(file, rank, next_file, next_rank);
    }
}

void CMoveGenerator::generate_potential_eng_passeng() {
     int eng_passeng_file = board.get_eng_passeng_file();
    if (eng_passeng_file == NO_ENG_PASSENG_POSSIBLE) {
        return;
    }
    const int rank = CBoardLogic::eng_passeng_pawn_rank();
    int next_rank = CBoardLogic::eng_passeng_forward_rank();
    const char my_pawn = CBoardLogic::my_pawn();
    assert(toupper(board.get_square(eng_passeng_file, rank)) == WHITE_POWER);
    assert(board.get_square(eng_passeng_file, next_rank) == EMPTY_SQUARE);
    int left = eng_passeng_file - 1;
    int right = eng_passeng_file + 1;
    if (board.get_square(left, rank) == my_pawn) {
        move_list.store_eng_passeng(left, rank, eng_passeng_file, next_rank);
    }
    if (board.get_square(right, rank) == my_pawn) {
        move_list.store_eng_passeng(right, rank, eng_passeng_file, next_rank);
    }       
}

bool CMoveGenerator::castling_possible(const int move_type) const {
    assert((move_type == MOVE_TYPE_WHITE_SHORT_CASTLING) 
        || (move_type == MOVE_TYPE_WHITE_LONG_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_SHORT_CASTLING)
        || (move_type == MOVE_TYPE_BLACK_LONG_CASTLING));
    return (board.get_castling_rights(move_type)
        && CBoardLogic::rook_on_castling_square(move_type)
        && (CBoardLogic::castling_squares_empty(move_type)));
    // TODO (or not, maybe): keep track of moving pieces when calculating variations
}

