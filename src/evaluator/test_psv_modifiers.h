#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestPsvModifiers {
  public:
    static bool test_everything();
  private:
    static bool test_square();
    static bool test_area();
    static bool test_make_equal();
    static bool test_make_gradient();
    static bool auto_cleanup_on_new_position();
};

