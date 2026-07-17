#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class CTestHashTable {
   public:
    static bool test_everything(); 
   private:
    static bool test_sizes();
    static bool test_resizing();
    static bool test_lookup();
    static bool test_lookup_after_resizing();
    static bool test_may_overwrite();
    static bool test_root_node_after_search();
};

