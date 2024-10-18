#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

struct STestcaseSearch {
    // Order of elements reversed for more readable layout of the list
    int depth;
    std::string expected_move;
    std::string fen_position;
};

class CTestSearch {
  public:
      static bool test_everything();
  private:
      static bool test_position(const STestcaseSearch &testcase);
};
