// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "profiling.h"
#include <cassert>
#include <iostream>

CProfiling::CProfiling() {
    reset();
}

void CProfiling::reset() {
    counters.resize(1);
    counters[0] = 0;
}

void CProfiling::increment(size_t index_of_counter) {
    size_up(index_of_counter + 1);
    ++counters[index_of_counter];
}

void CProfiling::increment_if(size_t index_of_counter, bool condition) {
    if (condition) {
        increment(index_of_counter);
    }
}

void CProfiling::show_results() const {
    std::cout << "*** CProfiling results ***\n";
    for (size_t index = 0; index < counters.size(); ++index) {
        show_result(index, "");
    }
}

void CProfiling::show_result(size_t index_of_counter, const std::string &description) const {
    assert(index_of_counter < counters.size());
    std::cout << index_of_counter << ": " << counters[index_of_counter] << " [" << description <<"]\n";
}

void CProfiling::size_up(size_t n_entries) {
    if (counters.size() < n_entries) {
        counters.resize(n_entries);
    }
}

