#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
 
class CTestEvaluator {
  public:
   static bool test_everything();
  private:
   static bool test_equal_positions();
   static bool test_decided_positions();
   // TODO: later, for incremental updates
   static bool test_make_unmake_moves();
};

