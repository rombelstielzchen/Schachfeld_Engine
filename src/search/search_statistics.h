// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../technical_functions/standard_headers.h"

class CSearchStatistics {
  public:
    CSearchStatistics();
  public:
    void reset_all();
    void reset_current_depth(int new_depth);
    void set_best_move(const std::string &best_move, const int score);;
    void set_current_move(const std::string &current_move, int score);
    void add_nodes(const int64_t nodes);
    void log_branching_factor() const;
  public:
    int64_t get_nodes_calculated() { return nodes_calculated; }
  private:
    std::string node_statistics() const;
  private:
    int64_t nodes_calculated;
    int64_t nodes_at_start_of_current_depth;
    int max_depth;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

inline CSearchStatistics search_statistics;

