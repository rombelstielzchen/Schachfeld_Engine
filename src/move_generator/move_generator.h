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

class CMoveGenerator {
  public:
      CMoveGenerator();
  public:
    void generate_all();
    SMove get_random() const;
    int list_size() const;
  public:
    static constexpr std::string as_text(const SMove move);
  private:
    void generate_white_pawn_moves(const int file, const int rank);
    void store_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
  private:
    std::array<SMove, MAX_MOVES_IN_CHESS_POSITION> move_list;
    int number_of_moves;
}; 

