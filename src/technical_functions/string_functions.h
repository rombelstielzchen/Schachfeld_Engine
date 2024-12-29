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

// returns position or std::string::npos if not found
size_t find_substring(const std::string &text, const std::string substring);

size_t replace_substring(std::string &source, const std::string &substring, const std::string &by_what, bool case_insensitive = false);

void replace_all_substrings(std::string &source, const std::string &substring, const std::string &by_what, bool case_insensitive = false);

void remove_all_substrings(std::string &source, const std::string &substring, bool case_insensitive = false);

