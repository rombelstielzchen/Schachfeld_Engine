#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../technical_functions/standard_headers.h"

// https://www.chessprogramming.org/Chess_Position
constexpr int MAX_MOVES_IN_CHESS_POSITION = 218;
// Just a guess!
// TEMP!!! Problems with stackframe mismatch!
constexpr unsigned int MAX_CAPTURES_IN_CHESS_POSITION = 25;
// Our move-list is bidirectional; left part for captures, right part for silent moves.
constexpr unsigned int LIST_SIZE = MAX_MOVES_IN_CHESS_POSITION + MAX_CAPTURES_IN_CHESS_POSITION;
constexpr unsigned int LIST_ORIGIN = MAX_CAPTURES_IN_CHESS_POSITION;

class CMoveList {
  public:
    CMoveList();
  public:
    int list_size() const;
    SMove get_random() const;
    SMove get_next();
    SMove get_least_valuable_aggressor() const;
    SMove lookup_move(const std::string &text_move) const;
  public:
    void store_castling(const char move_type);
    void store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank);
    // Special method for pawns, creating four moves on promotion
    void store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
  public:
    void store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type = MOVE_TYPE_NORMAL);
    void store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
  public:
    void prune_silent_moves();
    void filter_captures_by_target_square(const SSquare &target_square);
  public:
    // For root-node ordering
    void reuse_list();
    void shift_current_move_to_top();
  public:
    std::string as_text() const;
  private:
    void store_white_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_black_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank);
  private:
    inline void store_silent_move(const SMove &move);
    inline void store_capture(const SMove &move);
  private:
    void remove(const SMove move);
  private:
    // Using array instead of vector due to its known size and for better performance
    std::array<SMove,LIST_SIZE> bidirectional_move_list;
    unsigned int first_capture;
    unsigned int last_silent_move;
    unsigned int consumer_position;
};

