#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CTestRootNodeList {
  public:
    static bool test_everything();
  private:
    static bool test_empty_list();
    static bool test_generate_moves();
    static bool test_reuse_list();
    static bool test_only_one_legal_move();
    static bool test_remove();
    static bool test_shift_current_move_to_top();
    static bool test_move_on_list();
};

