// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"../move_generator/move.h"
#include"../move_generator/move_generator.h"

class CIterativeDeepening {
  public:
    CIterativeDeepening();
  public:
    SMove search(int depth);
    SMove search_nodes(int64_t nodes);
  private:
    void root_node_search(int depth);
  private:
    // Long-living at the root-node for better move-ordering
    CMoveGenerator move_generator;
    SMove best_move;
};

