#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestMoveMaker {
  public:
    static bool test_everything();
  private:
    static bool test_make_unmake_combinations();
    static bool test_make_unmake_combinations(const std::string &position);
    static bool test_algebraic_game();
};

