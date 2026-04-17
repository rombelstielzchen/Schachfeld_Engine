#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board.h"
#include "square_constants.h"

class CDistances {
  public:
    static double euclidian_distance(const SSquare a, const SSquare b);
    static SSquare nearest_square(const SSquare target_square, TSquareList square_list);
};

