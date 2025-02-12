#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Testing the move_generator.
// Going fixed depth, counting positions.
// https://www.chessprogramming.org/Perft

#include "../technical_functions/standard_headers.h"

class CTestPerft {
  public:
    static bool test_everything();
    static bool test_extended_depth();
  private:
    static bool test_shallow_depth();
    static bool test_up_to_depth(const unsigned int depth);
  private:
    static int64_t perft( const std::string &fen_position, const unsigned int depth, bool display_moves = false);
    static int64_t perft(const unsigned int depth, bool display_moves = false);
  private:
    static bool illegal_castlings_possible_at_higher_depth_Rh1_g1_h1_00();
};

