#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Utikity-class for derived board-information to keep the board-class lean

class CBoardLogic {
  public:
    // Piece encodings, depending on side-to-move
    static char my_king();
    static char my_rook();
    static char my_pawn();
  public:
    static int eng_passeng_pawn_rank();
    static int my_back_rank();
    bool castling_squares_empty(int TODO);
};

