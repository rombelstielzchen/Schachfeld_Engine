// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CSearchStatistics {
  public:
    CSearchStatistics();
  public:
    void reset();
    void set_best_move(const std::string &best_move, const int score);;
    void set_depth(const int depth);
    void set_current_move(const std::string &current_move);
    void set_nodes(const int64_t nodes);
  private:
    int64_t nodes_calculated;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, now_time;
};


