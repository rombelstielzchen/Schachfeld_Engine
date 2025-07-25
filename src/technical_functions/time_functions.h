#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

// Format specification: https://en.cppreference.com/w/cpp/chrono/c/strftime.html
std::string const TIME_FORMAT_YYYY_MM_DD = "%Y.%n.%d";

std::string time_string(const std::string &format);

