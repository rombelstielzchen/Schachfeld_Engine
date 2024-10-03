// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a snall list of short lines,
// just to get some fun and variation.

#include "opening_book.h"
#include "book_data/gm_book.h"


bool is_prefix_of(const std::string &pattern, const std::string &long_string, bool true_prefix = false) {
    DEBUG_METHOD();
    int pattern_size = pattern.length();
    if (long_string.find(pattern) != 0) {
        return false;
    }
    if (true_prefix && (pattern_size == long_string.length())) {
        return false;
    }
    return true;
}

constexpr int VARIATION_NOT_FOUND = -1;

COpeningBook::COpeningBook() {
    DEBUG_METHOD();
    last_looked_up_moves_from_startpos = "";
    last_lookup_successfull = true;
}

std::string COpeningBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    DEBUG_METHOD();
    int index = random_matching_index(gm_book, moves_from_startpos_in_uci_format);
    if (index == VARIATION_NOT_FOUND) {
        last_lookup_successfull = false;
        return NULL_MOVE_AS_TEXT;
    }
   assert(gm_book[index].length() > moves_from_startpos_in_uci_format.length());
   int first_char = 0;
   if (moves_from_startpos_in_uci_format != "") {
       first_char = moves_from_startpos_in_uci_format.length() + 1;
   }
   std::string next_move = gm_book[index].substr(first_char, 4);
   if (next_move == "x2x1") {
       // Bokelmann-Gambit for testability
        return "e2e4";
   }
    return next_move;
}

int COpeningBook::first_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    DEBUG_METHOD();
    int size = book.size(); 
    for (int j = 0; j < size; ++j) {
         if (is_prefix_of(moves_from_startpos_in_uci_format, book[j], true)) {
            return j;
        }
    }
    return VARIATION_NOT_FOUND;
}

int COpeningBook::last_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    DEBUG_METHOD();
    int last_element = book.size() - 1;
    for (int j = last_element; j >= 0; --j) {
         if (is_prefix_of(moves_from_startpos_in_uci_format, book[j], true)) {
            return j;
         }
    }
    return VARIATION_NOT_FOUND;
}

int COpeningBook::random_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    DEBUG_METHOD();
    int first_index = first_matching_index(book, moves_from_startpos_in_uci_format);
    if (first_index == VARIATION_NOT_FOUND) {
        return VARIATION_NOT_FOUND;
    }
    int last_index = last_matching_index(book, moves_from_startpos_in_uci_format);
    if (last_index == VARIATION_NOT_FOUND) {
         return VARIATION_NOT_FOUND;
    }
    assert(last_index >= first_index);
    int n_matching_variations = last_index - first_index + 1;
    int random_offset = rand() % n_matching_variations;
    int random_index = first_index + random_offset;
    assert(random_index >= first_index);
    assert(random_index <= last_index);
    return random_index;
}

