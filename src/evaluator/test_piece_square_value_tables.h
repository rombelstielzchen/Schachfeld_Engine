#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "piece_square_value_tables.h"

class CTestPieceSquareValueTables {
  public:
    static bool test_everything();
  private:
    static bool test_plausibility();
    static bool test_plausibility(const TPieceSquareValueTableSet &psv_table_set);
    static bool test_plausibility(const TPieceSquareValueTable &psv_table);
};

