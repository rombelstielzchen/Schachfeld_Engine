#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

#include "../search/hash_table.h"

class CTestHashFunction {
  public:
    static bool test_everything();
    static bool test_consistency();
  private:
    static THashKey hash_position(const std::string fen_position);
};

