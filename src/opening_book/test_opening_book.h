#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "opening_book.h"
#include "../technical_functions/standard_headers.h"

class CTestOpeningBook {
  public:
    static bool test_everything();
  private:
    static bool test_book_data(const TSortedVariationCollection &variation_collection, const std::string &book_name);
    static bool test_formatting(const TSortedVariationCollection &variation_collection);
    static bool test_sortedness(const TSortedVariationCollection &variation_collection);
    static bool test_playability(const TSortedVariationCollection & variation_collection);
  private:
    static bool test_move_lookup();
    static bool lookup_returns_null_move(std::string variation);
    static bool lookup_returns_any_move(std::string variation);
    static bool lookup_returns_exact_move(const std::string &variation, const std::string &text_move);
};

