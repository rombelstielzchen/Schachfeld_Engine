#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

class CProfiling {
  public:
    CProfiling();
  public:
    void reset();
    void increment(int index_of_counter);
    void increment_if(int index_of_counter, bool condition);
  public:
    void show_results() const;
    void show_result(int index_of_counter, std::string description) const;
};

inline CProfiling profiling;

