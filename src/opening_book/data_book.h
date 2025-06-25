#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a sorted list of textual lines,
// just to get some fun and variation.
// Nowadays we have multiple data-books (broad_GM tabijas, wonder_weapons);
// they get managed by the master_book.

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

typedef std::vector<std::string> TSortedVariationCollection;

class CDataBook {
  public:
    CDataBook(const TSortedVariationCollection &sorted_variation_collection);
    // Returns a null-move if no move could be found.
    std::string get_move(const std::string &moves_from_startpos_in_uci_format);
  private:
    size_t first_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const;
    size_t last_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const;
    size_t random_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const;
  private:
    std::string last_looked_up_moves_from_startpos;
    bool last_lookup_successful;
    const TSortedVariationCollection &sorted_variation_collection;
};

