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
  public:
    // The functions below consmue one token only on success
    bool next_token_is(const std::string &token);
    bool next_token_is_one_of(const std::string &token1, const std::string &token2);
    bool next_token_is_one_of(const std::string &token1, const std::string &token2, const std::string &token3);
  private:
    void push_nack(const std::string &token);
  private:
    std::istringstream input_stream;
    // Any reasonable parser uses one-token-lookahead
    std::string pushed_back_token;;
};

