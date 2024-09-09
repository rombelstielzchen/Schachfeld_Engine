// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_generator.h"
#include "../board/board.h"
#include "../technical_functions/standard_headers.h"

constexpr int WHITE_PAWN_DIRECTION = +1;
constexpr int BLACK_PAWN_DIRECTION = -1;

CMoveGenerator::CMoveGenerator() {
    number_of_moves = 0;
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
                    generate_pawn_moves(j, k, WHITE_PAWN_DIRECTION);
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
                case WHITE_KING:
                    generate_king_moves(j, k);
                    break;
            }
        }
    }
}

void CMoveGenerator::generate_all_black_moves() {
    for (int j = FILE_A; j <= FILE_H; ++j) {
        for (int k = RANK_1; k <= RANK_8; ++k) {
            switch (board.get_square(j, k)) {
                case BLACK_POWER:
                    generate_pawn_moves(j, k, BLACK_PAWN_DIRECTION);
                    break;
                case BLACK_KNIGHT:
                    generate_king_moves(j, k);
                    break;
                case BLACK_BISHOP:
                    generate_bishop_moves(j, k);
                    break;
                case BLACK_ROOK:
                    generate_rook_moves(j, k);
                    break;
                case BLACK_KING:
                    generate_king_moves(j, k);
                    break;
            }
        }
    }
}

void CMoveGenerator::generate_pawn_moves(const int file, const int rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == WHITE_PAWN_DIRECTION) || (positive_negative_direction == BLACK_PAWN_DIRECTION));
    const int next_rank = rank + positive_negative_direction;
    if (board.get_square(file, next_rank) == EMPTY_SQUARE) {
        store_move(file, rank, file, next_rank);
    }
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

void CMoveGenerator::generate_potential_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    if (board.is_valid_target_square(target_file, target_rank)) {
        store_move(source_file, source_rank, target_file, target_rank);
    }
}

void CMoveGenerator::generate_sliding_moves(const int file, const int rank, const int direction_north_sourh, const int direction_east_west) {
    int next_file = file + direction_east_west;
    int next_rank = rank + direction_north_sourh;
    while (board.get_square(next_file, next_rank) == EMPTY_SQUARE) {
        store_move(file, rank, next_file, next_rank);
        next_file += direction_east_west;
        next_rank += direction_north_sourh;
    }
    if (board.is_valid_target_square(next_file, next_rank)) {
        // Opponent piece
        store_move(file, rank, next_file, next_rank);
    }
}

SMove CMoveGenerator::get_random() const {
    if (number_of_moves <= 0) {
        return NULL_MOVE;
    }
    // Quick and dirty random numbers are OK for a temp function
    int index = rand() % number_of_moves;
    return move_list[index];
}

int CMoveGenerator::list_size() const {
    assert(number_of_moves <= MAX_MOVES_IN_CHESS_POSITION);
    return number_of_moves;
}

void CMoveGenerator::store_move(const int source_file, const int source_rank, const int target_file, const int target_rank) {
    assert(source_file >= FILE_A);
    assert(source_file <= FILE_H);
    assert(source_rank >= RANK_1);
    assert(source_rank <= RANK_8);
    assert(target_file >= FILE_A);
    assert(target_file <= FILE_H);
    assert(target_rank >= RANK_1);
    assert(target_rank <= RANK_8);
    assert(number_of_moves < MAX_MOVES_IN_CHESS_POSITION);
    SMove new_move;
    new_move.source.file = source_file;
    new_move.source.rank = source_rank;
    new_move.target.file = target_file;
    new_move.target.rank = target_rank;
    move_list[number_of_moves] = new_move;
    number_of_moves++;
}
