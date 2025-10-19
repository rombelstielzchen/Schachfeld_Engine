#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestDepthControl {
  public:
    static bool test_everything();
  private:
    static bool test_depth();
    static bool test_depth_adaption_for_better_mates();
};

