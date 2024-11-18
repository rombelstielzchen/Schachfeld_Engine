#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
 
class CEvaluator {
  public:
    int evaluate() const;
  public:
    // For testing purposes
    bool evaluates_approximately_to(const int score) const;
  private:
    int evaluate_square(const SSquare &square) const;
    int evaluate_square(const int file, const int rank) const;
  private:
    // Temp function to get some minimal positional understanding
    int central_bonus(const int file, const int rank) const;
    int castling_bonus(const int file, const int rank) const;
};

