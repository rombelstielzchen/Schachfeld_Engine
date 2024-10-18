#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CTestSearch {
  public:
      static bool test_everything();
  private:
      static bool test_position(std::string &position, std::string expected_move);
};
