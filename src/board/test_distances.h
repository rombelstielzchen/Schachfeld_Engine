#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board.h"

class CTestDistances {
  public:
      static bool test_everything();
  private:
      static bool test_euclidian_distance();
//      static SSquare nearest_squar(const SSquare target_square, TSquareList square_list);
};

