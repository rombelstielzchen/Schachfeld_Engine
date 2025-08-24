#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestMove {
  public:
    static bool test_everything();
  private:
    static bool test_text_to_basic_move();
    static bool test_reversed_move();
};

