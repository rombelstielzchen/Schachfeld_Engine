#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "square_constants.h"

class CBoard;

class CDistances {
  public:
    CDistances();
    void init_board_pointer(const CBoard *my_board);                
  public:
    double euclidian_distance(const SSquare a, const SSquare b) const;
    double manhattan_distance(const SSquare a, const SSquare b) const;
    double mixed_distance(const SSquare a, const SSquare b) const;
  public:
    SSquare nearest_square(const SSquare target_square, TSquareList square_list) const;
  private:
    const CBoard *my_board;
};

