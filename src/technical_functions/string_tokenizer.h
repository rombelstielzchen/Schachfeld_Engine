#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "standard_headers.h"

class CStringTokenizer {
  public:
    CStringTokenizer(const std::string &input = "");
  public:
    void set_input(const std::string &input);
    std::string next_token();
    int get_integer_token(int minimum_and_default);
    std::string get_the_rest();
  private:
    std::istringstream input_stream;
};

