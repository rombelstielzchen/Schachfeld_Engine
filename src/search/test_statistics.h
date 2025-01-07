#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestStatistics {
  public:
    static bool test_everything();
  private:
    static bool test_basic_stats();
    static bool test_expected_branching_factor();
};
