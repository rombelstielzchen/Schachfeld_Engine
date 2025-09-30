#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

struct STestcaseStaticExchangeEvaluation {
    std::string fen_position;
    SSquare capture_square;
    bool favorable_capture;
};

struct STestcaseSearch {
    // Order of elements reversed for more readable layout of the list
    int depth;
    std::string expected_move;
    std::string fen_position;
};

class CTestSearch {
  public:
    static bool test_everything();
  private:
    static bool test_no_legal_moves();
    static bool test_position(const STestcaseSearch &testcase);
    static bool test_static_exchange_evaluation();
    static bool test_early_exit();
    static bool test_anti_repetition();
    static bool test_mate_score();
};

