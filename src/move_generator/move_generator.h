#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../board/board.h"
#include "../technical_functions/standard_headers.h"

// https://www.chessprogramming.org/Chess_Position
constexpr int MAX_MOVES_IN_CHESS_POSITION = 218;

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
    SMove get_random() const;
    int list_size() const;
  private:
    void generate_all_white_moves();
    void generate_all_black_moves();
  private:
    void generate_pawn_moves(const int file, const int rank, const int positive_negative_direction);
    void generate_king_moves(const int file, const int rank);
    void generate_knight_moves(const int file, const int rank);
    void generate_bishop_moves(const int file, const int rank);
  private:
    void generate_potential_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void generate_sliding_moves(const int file, const int rank, const int direction_north_sourh, const int direction_east_west);
    void store_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
  private:
    std::array<SMove, MAX_MOVES_IN_CHESS_POSITION> move_list;
    unsigned int number_of_moves;
}; 

