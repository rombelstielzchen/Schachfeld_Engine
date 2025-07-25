// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "time_functions.h"
#include <cassert>
#include <chrono>
#include <cstring>

std::string time_string(const std::string &format) {
    char buffer[] = "tis is a long buffer a long buffer tis is is tis buffer fat enough pretty fat  pretty fat for sure";
    int const buffer_size = strlen(buffer);
    std::time_t now = std::time(nullptr);
    int const stored_bytes = std::strftime(buffer, buffer_size, format.c_str(), std::localtime(&now));
    assert(stored_bytes > 0);
    assert(stored_bytes <= buffer_size);
    std::string result(buffer);
    return result;
}

