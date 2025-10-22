// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Disable warning about "unsecure" localtime in Visual Studio.
// The "secure" localtime_s is not available for g++.
#define _CRT_SECURE_NO_DEPRECATE

#include "time_functions.h"
#include <cassert>
#include <chrono>
#include <cstring>

std::string time_string(const std::string &format) {
    char buffer[] = "tis is a long buffer a long buffer tis is is tis buffer fat enough pretty fat  pretty fat for sure";
    size_t const buffer_size = strlen(buffer);
    std::time_t now = std::time(nullptr);
    size_t const stored_bytes = std::strftime(buffer, buffer_size, format.c_str(), std::localtime(&now));
    assert(stored_bytes > 0);
    assert(stored_bytes <= buffer_size);
    if (stored_bytes <= 0) {
        return "--error--";
    }
    std::string result(buffer);
    return result;
}

