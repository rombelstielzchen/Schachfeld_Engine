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

class CStringTokenizer {
  public:
    CStringTokenizer(const std::string &input = "");
  public:
    void set_input(std::string &input);
    std::string next_token();
    std::string get_the_rest();
  private:
    std::istringstream input_stream;
};

