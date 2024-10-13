#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestMoveMaker {
  public:
    static bool test_everything();
  private:
    static bool test_make_unmake_combinations();
    static bool test_algebraic_game();
};

