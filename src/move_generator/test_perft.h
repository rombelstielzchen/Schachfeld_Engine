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
  private:
    static bool test_basic();
  private:
    static int64_t perft(const int depth);
    static int64_t perft(const int depth, const std::string fen_position);
};

