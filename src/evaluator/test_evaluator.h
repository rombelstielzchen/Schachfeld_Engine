#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// TODO: rmove this!
#include "../technical_functions/standard_headers.h"

#include "../move_generator/move.h"
#include <vector>

struct STestcaseEvaluator {
    std::string better_position;
    std::string worse_position;
};

typedef std::vector<STestcaseEvaluator> TTestcaseSetEvaluator;
 
class CTestEvaluator {
  public:
   static bool test_everything();
    static bool first_position_better(const std::string &first_fen, const std::string &second_fen);
  private:
    static bool test_equal_positions();
    static bool test_decided_positions();
    static bool test_move_sequence();
    static bool test_black_advantage();
    static bool test_pawn_values();
    static bool test_positions(const TTestcaseSetEvaluator &testcase_set);
  private:
    static bool first_position_better(const STestcaseEvaluator &testcase);
    static bool first_pawn_better(const SSquare first, const SSquare second);
    static bool first_square_better(char piece, const SSquare first, const SSquare second);
    static bool evaluates_approximately_to(const int score);
    static bool test_wood_points();
};

