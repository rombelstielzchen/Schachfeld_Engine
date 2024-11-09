#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../technical_functions/standard_headers.h"

// https://www.chessprogramming.org/Chess_Position
constexpr int MAX_MOVES_IN_CHESS_POSITION = 218;

class CMoveList {
  public:
    CMoveList();
  public:
    int list_size() const;
    SMove get_random() const;
    SMove get_next();
    SMove lookup_move(const std::string &text_move) const;
  public:
    void store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type = MOVE_TYPE_NORMAL);
    void store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank);
    // Special method for pawns, creating four moves on promotion
    void store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
  private:
    // Temp, old implementation
    void store_move(const SMove &move);
  private:
    // Using array instead of vector due to its known size and for better performance
    std::array<SMove, MAX_MOVES_IN_CHESS_POSITION> move_list;
    unsigned int number_of_moves;
    unsigned int consumer_counter;
};

