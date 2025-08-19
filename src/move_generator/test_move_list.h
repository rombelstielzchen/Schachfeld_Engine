#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CTestMoveList {
  public:
    static bool test_everything();
    static bool test_basics();
    static bool test_extremes();
  private:
    static bool test_prune_silent_moves();
    static bool test_filter_by_target_square();
    static bool test_reuse_list();
    static bool test_shift_current_move_to_top();
    static bool test_remove();
    static bool test_get_best_capture();
    static bool test_move_lookup();
    static bool test_king_capture();
    static bool test_prune_silent_piecee_moves ();
};

