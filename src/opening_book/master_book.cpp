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
#include "../technical_functions/string_functions.h"

CMasterBook::CMasterBook() {
    last_looked_up_moves_from_startpos = "";
    last_lookup_successful = true;
}

std::string CMasterBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    return NULL_MOVE_AS_TEXT;
}

