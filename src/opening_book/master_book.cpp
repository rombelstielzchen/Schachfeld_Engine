// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a small list of short lines,
// just to get some fun and variation.

#include "master_book.h"
#include "book_data/gm_book.h"
#include "book_data/tabijas.h"
#include "../technical_functions/string_functions.h"

CMasterBook::CMasterBook() : gm_book(sorted_variation_collection_gm_book),
        tabijas(sorted_variation_collection_tabijas) {
    last_looked_up_moves_from_startpos = "";
    last_lookup_successful = true;
}

std::string CMasterBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
        std::string book_move = tabijas.get_move(moves_from_startpos_in_uci_format);
    if (book_move == NULL_MOVE_AS_TEXT) {
       book_move = gm_book.get_move(moves_from_startpos_in_uci_format);
    }
    return book_move;
}

