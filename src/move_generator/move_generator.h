#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move_list.h"
#include "../board/board.h"
#include "../technical_functions/standard_headers.h"

// Directions for pawns and sliding pieces (queen, rook, bishop)
constexpr int DIRECTION_NORTH = +1;
constexpr int DIRECTION_SOUTH = -1;
constexpr int DIRECTION_EAST = +1;
constexpr int DIRECTION_WEST = -1;
constexpr int DIRECTION_NEUTRAL = 0;

class CMoveGenerator {
  public:
    CMoveGenerator();
  public:
    void generate_all();
    void generate_captures();
    void generate_recaptures(const SSquare target_square);
  public:
    CMoveList move_list;
  private:
    void generate_all_white_moves();
    void generate_all_black_moves();
  private:
    void generate_pawn_moves(const int file, const int rank, const int positive_negative_direction);
    void generate_pawn_captures(const int file, const int rank, const int positive_negative_direction);
    void generate_pawn_forward_moves(const int file, const int rank, const int positive_negative_direction);
    void generate_king_moves(const int file, const int rank);
    void generate_castlings(const int file, const int rank);
    void generate_knight_moves(const int file, const int rank);
    void generate_bishop_moves(const int file, const int rank);
    void generate_rook_moves(const int file, const int rank);
    void generate_queen_moves(const int file, const int rank);
  private:
    void generate_potential_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void generate_sliding_moves(const int file, const int rank, const int direction_north_south, const int direction_east_west);
    void generate_potential_eng_passeng();
}; 

