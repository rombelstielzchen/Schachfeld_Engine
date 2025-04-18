#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Utility-class for derived board-information to keep the board-class lean

#include "../move_generator/move.h"

class CBoardLogic {
  public:
    // Piece encodings, depending on side-to-move
    static char my_king();
    static char my_rook();
    static char my_pawn();
  public:
    static int eng_passeng_pawn_rank();
    static int eng_passeng_forward_rank();
    static int my_back_rank();
  public:
    static bool castling_squares_empty(const char move_type);
    static bool rook_on_castling_square(const char move_type);
    static bool square_occupied_by_opponent(const int file, const int rank);
    static bool is_valid_target_square(const int file, const int rank);
  public:
    // Simple and slow, meant for the root-node onlyy
    static SSquare king_square(bool white_or_black);
  public:
    static bool square_attacked_by_side_to_move();
   static bool square_attacked_by_opponent(); 

};

