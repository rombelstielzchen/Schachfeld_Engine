#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../board/square_constants.h"
#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

// Depth 128 is good enough for 2^128 nodes ~~ 3.4E38 nodes,
// a number that can never be calculated.
constexpr int MAX_KILLER_DEPTH = 128;

// For initialization and testing, a nearly-valid move that does not harm
constexpr SMove DUMMY_KILLER = { E1, F6, MOVE_TYPE_NORMAL, EMPTY_SQUARE };

class CKillerHeuristic {
   public:
    CKillerHeuristic();
   public:
    void store_killer(int distance_to_root, const SMove move);
   SMove get_killer(int distance_to_root);
   private:
    std::array<SMove, MAX_KILLER_DEPTH> killer_movess;
};

