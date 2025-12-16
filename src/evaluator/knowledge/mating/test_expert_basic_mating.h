#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestExpertBasicMating {
  public:
    static bool test_everything();
  private:
    static bool test_is_responsable();
    static bool test_desired_mating_corner();
    static bool test_gradient();
    static bool test_gradiet_after_moves();
};

