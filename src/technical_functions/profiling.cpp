// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "profiling.h"
#include <cassert>
#include <cstring>
#include <iostream>

constexpr size_t default_counter = 0;
const char *default_description = "";

CProfiling::CProfiling() {
    reset();
}

void CProfiling::reset() {
    counters.clear();
    counters.shrink_to_fit();
    descriptions.clear();
    descriptions.shrink_to_fit();
    constexpr size_t n_entries = 1;
    size_up(n_entries);
    assert(counters.size() >= n_entries);
    assert(counters[0] == default_counter);
    assert(counters.back() == default_counter);
    assert(descriptions.size() >= n_entries);
    assert(descriptions[0] != nullptr);
    assert(std::strcmp(descriptions[0], default_description) == 0);
    assert(descriptions.back() != nullptr);
    assert(std::strcmp(descriptions.back(), default_description) == 0);
}

void CProfiling::increment(size_t index_of_counter, const char *description) {
    assert(description != nullptr);
    size_up(index_of_counter + 1);
    assert(counters.size() > index_of_counter);
    assert(descriptions.size() > index_of_counter);
    ++counters[index_of_counter];
    descriptions[index_of_counter] = description;
}

void CProfiling::increment_if(size_t index_of_counter, bool condition, const char *description) {
    assert(description != nullptr);
    if (condition) {
        increment(index_of_counter, description);
    }
}

void CProfiling::show_results() const {
    std::cout << "*** CProfiling results *******\n";
    // TODO: range-based loop maybe (requires vector of struct)
    for (size_t index = 0; index < counters.size(); ++index) {
        show_result(index);
    }
}

void CProfiling::show_result(size_t index_of_counter) const {
    assert(index_of_counter < counters.size());
    assert(descriptions[index_of_counter] != nullptr);
    std::cout << index_of_counter << ": " << counters[index_of_counter] << " [" << descriptions[index_of_counter] <<"]\n";
}

void CProfiling::size_up(size_t n_entries) {
    assert(n_entries > 0);
    assert(counters.size() == descriptions.size());
    if (counters.size() >= n_entries) {
        return;
    }
    counters.resize(n_entries, default_counter);
    descriptions.resize(n_entries, default_description);
    assert(counters.size() >= n_entries);
    assert(counters.back() == default_counter);
    assert(descriptions.size() >= n_entries);
    assert(descriptions.back() != nullptr);
    assert(std::strcmp(descriptions.back(), default_description) == 0);
}

