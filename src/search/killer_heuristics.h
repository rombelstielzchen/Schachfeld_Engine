#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CKillerHeuristic {
   public:
    CKillerHeuristic();
   public:
    void store_hiller(int distance_to_root, const SMove move);
   SMove get_killer(int distance_to_root);
   private:
    std::vector<SMove> killer_movess;
};

