#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestOracle {
  public:
    CTestOracle();
  public:
    static bool test_everything();
  private:
    static bool test_reasonable_initialization();
    static bool test_endgame_king();
};

