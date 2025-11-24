#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../../../move_generator/move.h"

enum {
    QUEENSIDE,
    UNCASTLED,
    KINGSIDE,
};

// Examples of usage
//   * "important center" = g2, g3 / e2, e3 / b2, b3
//   * "important flank" = f2, f3 / ...
//   * "minor flank" = h2, h3 / ...
//   * for black use 7th rank as 2nd rank, 6th rank as 3rd rank
typedef struct {
    SSquare important_center_pawn_2;
    SSquare important_center_pawn_3;
    SSquare important_flank_pawn_2;
    SSquare important_flank_pawn_3;
    SSquare minor_flank_pawn_2;
    SSquare minor_flank_pawn_3;
    SSquare bottom_left_king_area;
    SSquare top_right_king_area;
} SKingSquareGroup;

extern const SKingSquareGroup KING_SQUARE_GRUP_BLACK_KINGSIDE;
extern const SKingSquareGroup KING_SQUARE_GRUP_BLACK_QUEENSIDE;
extern const SKingSquareGroup KING_SQUARE_GRUP_WHITE_KINGSIDE;
extern const SKingSquareGroup KING_SQUARE_GRUP_WHITE_QUEENSIDE;

constexpr int EXCELLENT_KING_POSITION = 2;
constexpr int GOOD_KING_POSITION = 1;
constexpr int MEDIOCRE_KING_POSITION = 0;
constexpr int UNSAFE_KING_POSITION = -2;

class CSafetyEvaluator {
  public:
    static int king_safety(bool player, int king_position);
  private:
    static int pawn_shelter_safety(bool player,
        const SKingSquareGroup ksg);
};

