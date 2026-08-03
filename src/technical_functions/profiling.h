#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>
#include <vector>

class CProfiling {
  public:
    CProfiling();
  public:
    void reset();
    void increment(size_t index_of_counter, const char *description);
    void increment_if(size_t index_of_counter, bool condition, const char *description);
  public:
    void show_results() const;
    void show_result(size_t index_of_counter) const;
  private:
    void size_up(size_t n_entries);
  private:
    std::vector<size_t> counters;
    std::vector<const char*> descriptions;
};

inline CProfiling profiling;

