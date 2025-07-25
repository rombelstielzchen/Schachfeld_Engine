#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "../move_generator/move.h"

class CEvaluator {
    friend class CTestEvaluator;
  public:
    CEvaluator();
  public:
    void init();
    void incremental_add(char piece, const SSquare square);
    void incremental_clear_square(const SSquare square);
    int evaluate() const { return value; }
    int nega_score() const;
  public:
    int evaluate_square(const SSquare &square) const;
    void log_board_evaluation() const;
  private:
    int evaluate_square(const int file, const int rank) const;
    static int evaluate_white_pawn(const SSquare square);
  private:
    int value;
    COracle oracle;
};

