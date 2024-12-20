#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move_generator.h"
#include "../technical_functions/standard_headers.h"

struct STestcaseMoveGenerator {
    // Order of elements reversed for more readable layout of the list
    uint8_t expected_moves;
    uint8_t expected_captures;
    std::string fen_position;
};

class CTestMoveGenerator {
  public:
    static bool test_everything();
  private:
    static bool test_prune_silent_moves();
    static bool test_filter_by_target_square();
    static bool test_reuse_list();
    static bool test_shift_current_move_to_top();
    static bool test_positions();
    static bool test(const STestcaseMoveGenerator &testcase);
};

