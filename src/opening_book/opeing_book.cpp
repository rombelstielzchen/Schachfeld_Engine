// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a snall list of short lines,
// just to get some fun and variation.

#include "opeing_book.h"

constexpr int VARIATION_NOT_FOUND = -1;

COpwningBook::COpwningBook() {
    last_looked_up_moves_from_startpos = "";
    last_lookup_successfull = true;
}

SMove COpwningBook::get_move(std::string moves_from_startpos_in_uci_format) {
    int index = random_matching_index(moves_from_startpos_in_uci_format);
    if (index == VARIATION_NOT_FOUND) {
        last_lookup_successfull = false;
        return NULL_MOVE;
    }
    return text_to_move("e2e4");
}

int COpwningBook::first_matching_index(std::string moves_from_startpos_in_uci_format) const {
    return VARIATION_NOT_FOUND;
}

int COpwningBook::last_matching_index(std::string moves_from_startpos_in_uci_format) const {
    return VARIATION_NOT_FOUND;
}

int COpwningBook::random_matching_index(std::string moves_from_startpos_in_uci_format) const {
    int first_index = first_matching_index(moves_from_startpos_in_uci_format);
    if (first_index == VARIATION_NOT_FOUND) {
        return VARIATION_NOT_FOUND;
    }
    int last_index = last_matching_index(moves_from_startpos_in_uci_format);
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

