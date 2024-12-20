#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "standard_headers.h"

void replace_tabs_by_spaces(std::string &in_out_string);

void trim_left(std::string &in_out_string);

void trim_right(std::string &in_out_string);
    
void trim(std::string &in_out_string);


bool is_prefix_of(const std::string &pattern, const std::string &long_string, bool true_prefix = false);

