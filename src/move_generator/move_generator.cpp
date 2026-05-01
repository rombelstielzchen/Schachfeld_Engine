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
    assert(move_list.is_empty());
    bool side_to_move = board.get_side_to_move();
    if (side_to_move == WHITE_PLAYER) {
        generate_all_white_moves();
    } else {
        assert(side_to_move == BLACK_PLAYER);
        generate_all_black_moves();
    }
}

void CMoveGenerator::generate_captures() {
    assert(move_list.is_empty());
    generate_all();
    move_list.prune_silent_moves();
}

void CMoveGenerator::generate_recaptures(const SSquare target_square) {
    assert(square_in_range(target_square));
    generate_captures();
    move_list.filter_captures_by_target_square(target_square);
}

void CMoveGenerator::generate_all_white_moves() {
    for (const SSquare s: ALL_SQUARES) {
        switch (board.get_square(s)) {
            case WHITE_POWER:
                generate_pawn_moves(s.file, s.rank, DIRECTION_NORTH);
                break;
            case WHITE_KNIGHT:
                generate_knight_moves(s.file, s.rank);
                break;
            case WHITE_BISHOP:
                generate_bishop_moves(s.file, s.rank);
                break;
            case WHITE_ROOK:
                generate_rook_moves(s.file, s.rank);
                break;
            case WHITE_QUEEN:
                generate_queen_moves(s.file, s.rank);
                break;
            case WHITE_KING:
                generate_king_moves(s.file, s.rank);
                break;
        }
    }
    generate_potential_eng_passeng();
}

void CMoveGenerator::generate_all_black_moves() {
    for (const SSquare s: ALL_SQUARES) {
        switch (board.get_square(s)) {
            // TODO: switch function parameters to SSquare
            case BLACK_POWER:
                generate_pawn_moves(s.file, s.rank, DIRECTION_SOUTH);
                break;
            case BLACK_KNIGHT:
                generate_knight_moves(s.file, s.rank);
                break;
            case BLACK_BISHOP:
                generate_bishop_moves(s.file, s.rank);
                break;
            case BLACK_ROOK:
                generate_rook_moves(s.file, s.rank);
                break;
            case BLACK_QUEEN:
                generate_queen_moves(s.file, s.rank);
                break;
            case BLACK_KING:
                generate_king_moves(s.file, s.rank);
                break;
        }
    }
    generate_potential_eng_passeng();
}

void CMoveGenerator::generate_pawn_captures(const TFile file, const TRank rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    // TODO: const + 1-liner below
    TRank next_rank = rank;
    next_rank = next_rank + positive_negative_direction;
    TFile left_file = file;
    left_file = left_file - 1;
    TFile right_file = file;
    right_file = right_file + 1;
    if (CBoardLogic::square_occupied_by_opponent(left_file, next_rank)) {
        move_list.store_pawn_capture(file, rank, left_file, next_rank);
    }
    if (CBoardLogic::square_occupied_by_opponent(right_file, next_rank)) {
        move_list.store_pawn_capture(file, rank, right_file, next_rank);
    }
}

void CMoveGenerator::generate_pawn_forward_moves(const TFile file, const TRank rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    TRank next_rank = rank;
    next_rank = next_rank + positive_negative_direction;
    if (board.square_is_empty(file, next_rank)) {
        move_list.store_pawn_move(file, rank, file, next_rank);
        TRank second_next_rank = next_rank + positive_negative_direction;
        if (((rank == RANK_2) || (rank == RANK_7))
            && (board.square_is_empty(file, second_next_rank))) {
            move_list.store_silent_move(file, rank, file, second_next_rank, MOVE_TYPE_DOUBLE_JUMP);
        }
    }
}

void CMoveGenerator::generate_pawn_moves(const TFile file, const TRank rank, const int positive_negative_direction) {
    assert(rank >= RANK_2);
    assert(rank <= RANK_7);
    assert((positive_negative_direction == DIRECTION_NORTH) || (positive_negative_direction == DIRECTION_SOUTH));
    generate_pawn_captures(file, rank, positive_negative_direction);
    generate_pawn_forward_moves(file, rank, positive_negative_direction);
}

void CMoveGenerator::generate_king_moves(const TFile file, const TRank rank) {
    generate_potential_move(file, rank, file, rank + 1);
    generate_potential_move(file, rank, file + 1, rank + 1);
    generate_potential_move(file, rank, file - 1, rank + 1);
    generate_potential_move(file, rank, file - 1, rank      );
    generate_potential_move(file, rank, file + 1, rank    );
    generate_potential_move(file, rank, file + 1, rank - 1);
    generate_potential_move(file, rank, file    , rank - 1);
    generate_potential_move(file, rank, file - 1, rank - 1);
    generate_castlings(file, rank);
}

void CMoveGenerator::generate_castlings(const TFile file, const TRank rank) {
    if ((file != FILE_E) || (rank != CBoardLogic::my_back_rank())) {
        return;
    }
    int my_short = MOVE_TYPE_WHITE_SHORT_CASTLING;
    int my_long = MOVE_TYPE_WHITE_LONG_CASTLING;
    if (rank == RANK_8) {
        my_short = MOVE_TYPE_BLACK_SHORT_CASTLING;
        my_long = MOVE_TYPE_BLACK_LONG_CASTLING;
    }
    if (CBoardLogic::castling_possible(my_short)) {
        move_list.store_castling(my_short);
    }
    if (CBoardLogic::castling_possible(my_long)) {
        move_list.store_castling(my_long);
    }
}

void CMoveGenerator::generate_knight_moves(const TFile file, const TRank rank) {
    generate_potential_move(file, rank, file - 1, rank + 2);
    generate_potential_move(file, rank, file + 1, rank + 2);
    generate_potential_move(file, rank, file - 2, rank + 1);
    generate_potential_move(file, rank, file + 2, rank + 1);
    generate_potential_move(file, rank, file - 2, rank - 1);
    generate_potential_move(file, rank, file + 2, rank - 1);
    generate_potential_move(file, rank, file - 1, rank - 2);
    generate_potential_move(file, rank, file + 1, rank - 2);
}

void CMoveGenerator::generate_bishop_moves(const TFile file, const TRank rank) {
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_WEST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_WEST);
}

void CMoveGenerator::generate_rook_moves(const TFile file, const TRank rank) {
    generate_sliding_moves(file, rank, DIRECTION_NORTH, DIRECTION_NEUTRAL);
    generate_sliding_moves(file, rank, DIRECTION_NEUTRAL, DIRECTION_EAST);
    generate_sliding_moves(file, rank, DIRECTION_NEUTRAL, DIRECTION_WEST);
    generate_sliding_moves(file, rank, DIRECTION_SOUTH, DIRECTION_NEUTRAL);
}

void CMoveGenerator::generate_queen_moves(const TFile file, const TRank rank) {
    generate_bishop_moves(file, rank);
    generate_rook_moves(file, rank);
}

void CMoveGenerator::generate_potential_move(const TFile source_file, const TRank source_rank, const TFile target_file, const TRank target_rank) {
    DEBUG_METHOD();
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
    // Else: coordinates out of range or target occupied by own piece
}

void CMoveGenerator::generate_sliding_moves(const TFile file, const TRank rank, const int direction_north_south, const int direction_east_west) {
    DEBUG_METHOD();
    TFile next_file = file + direction_east_west;
    TRank next_rank = rank + direction_north_south;
    while (board.square_is_empty(next_file, next_rank)) {
        assert(file_in_range(next_file));
        assert(rank_in_range(next_rank));
        move_list.store_silent_move(file, rank, next_file, next_rank);
        next_file += direction_east_west;
        next_rank += direction_north_south;
    }
    if (CBoardLogic::square_occupied_by_opponent(next_file, next_rank)) {
        move_list.store_capture(file, rank, next_file, next_rank);
    }
}

void CMoveGenerator::generate_potential_eng_passeng() {
     DEBUG_METHOD();
     TFile eng_passeng_file = board.get_eng_passeng_file();
    if (eng_passeng_file == NO_ENG_PASSENG_POSSIBLE) {
        return;
    }
    assert(file_in_range(eng_passeng_file));
    const TRank rank = CBoardLogic::eng_passeng_pawn_rank();
    assert((rank == RANK_4) || (rank == RANK_5));
    TRank next_rank = CBoardLogic::eng_passeng_forward_rank();
    assert((next_rank == RANK_3) || (next_rank == RANK_6));
    const char my_pawn = CBoardLogic::my_pawn();
    assert((board.get_square(eng_passeng_file, rank) == WHITE_POWER) || (board.get_square(eng_passeng_file, rank) == BLACK_POWER));
    assert(board.square_is_empty(eng_passeng_file, next_rank));
    TFile left = eng_passeng_file - 1;
    TFile right = eng_passeng_file + 1;
    if (board.get_square(left, rank) == my_pawn) {
        move_list.store_eng_passeng(left, rank, eng_passeng_file, next_rank);
    }
    if (board.get_square(right, rank) == my_pawn) {
        move_list.store_eng_passeng(right, rank, eng_passeng_file, next_rank);
    }       
}

void CMoveGenerator::reset() {
    move_list.clear();
}

