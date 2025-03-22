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
    set_option(BOOK_OPTIONS_SOLID_MIX);
}

std::string CMasterBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    std::string book_move = NULL_MOVE_AS_TEXT;
    switch (boook_option) {
        case BOOK_OPTIONS_BROAD_GM:
           // Nothing toi be done here in order to avoid double lookups.
           // Broad_GM is our backup for failed lookups.
            break;
        case BOOK_OPTIONS_TABIJAS:
            book_move = tabijas.get_move(moves_from_startpos_in_uci_format);
            break;
        case BOOK_OPTIONS_WONDER_WEAPONS:
            // TODO
            break;
        case BOOK_OPTIONS_SOLID_MIX:
            // TODO
            break;
    }
    if (book_move == NULL_MOVE_AS_TEXT) {
       book_move = gm_book.get_move(moves_from_startpos_in_uci_format);
    }
    return book_move;
}

void CMasterBook::set_option(EBookOptions option) {
    boook_option = option;
}

void CMasterBook::set_option(const std::string &selected_uci_option) {
    if (selected_uci_option == "broad_GM") {
        boook_option = BOOK_OPTIONS_BROAD_GM;
    } else if (selected_uci_option == "tabijas") {
        boook_option = BOOK_OPTIONS_TABIJAS;
    } else if (selected_uci_option == "wonder_weapons") {
        boook_option = BOOK_OPTIONS_WONDER_WEAPONS;
    } else if (selected_uci_option == "solid_mix") {
        boook_option = BOOK_OPTIONS_SOLID_MIX;
    } else {
       // Ignore unexpected vales from a potential stupid / malicious outside world 
    }
    std::cerr << "boook_option: " << boook_option << "\n";
}

