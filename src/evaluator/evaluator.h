#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
 
class CEvaluator {
    friend class CTestEvaluator;
  public:
    CEvaluator();
  public:
    void initial_full_evaluation();
    void incremental_add(char piece, const SSquare square);
    void incremental_clear_square(const SSquare square);
    int evaluate() const { return value; }
  public:
    // TODO: private?
    int evaluate_square(const SSquare &square) const;
  private:
    // For testing purposes
    // TODO: move to test?
    bool evaluates_approximately_to(const int score) const;
  private:
    int evaluate_square(const int file, const int rank) const;
    static int evaluate_white_pawn(const SSquare square);
  private:
    int value;
};

