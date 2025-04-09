// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "master_book.h"
#include "book_data/gm_book.h"
#include "book_data/tabijas.h"
#include "../technical_functions/string_functions.h"

// Probabilities for randomozing "solid_mix"
constexpr float probability_tabijas = 0.50;
constexpr float probability_wonder_weapons = 0.00;
constexpr float remaining_probability_broad_GM = 1.00 - probability_tabijas - probability_wonder_weapons;
static_assert(remaining_probability_broad_GM >= 0.00);

CMasterBook::CMasterBook() : gm_book(sorted_variation_collection_gm_book),
        tabijas(sorted_variation_collection_tabijas) {
    assert(rand() != rand());
    set_option(BOOK_OPTIONS_SOLID_MIX);
}

std::string CMasterBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    assert(boook_option_for_this_game != BOOK_OPTIONS_SOLID_MIX);
    std::string book_move = NULL_MOVE_AS_TEXT;
    switch (boook_option_for_this_game) {
        case BOOK_OPTIONS_BROAD_GM:
           // Nothing to be done here in order to avoid double lookups.
           // Broad_GM is our backup for failed lookups.
            break;
        case BOOK_OPTIONS_TABIJAS:
            book_move = tabijas.get_move(moves_from_startpos_in_uci_format);
            break;
        case BOOK_OPTIONS_WONDER_WEAPONS:
            // TODO
            break;
        default: 
           assert(THIS_MUST_NOT_HAPPEN); 
            break;
    }
    if (book_move == NULL_MOVE_AS_TEXT) {
       book_move = gm_book.get_move(moves_from_startpos_in_uci_format);
    }
    return book_move;
}

void CMasterBook::set_option(EBookOptions option) {
    boook_option = option;
    std::cerr << "boook_option: " << boook_option << "\n";
    on_new_game();
}

void CMasterBook::set_option(const std::string &selected_uci_option) {
    if (selected_uci_option == "broad_GM") {
        set_option(BOOK_OPTIONS_BROAD_GM);
    } else if (selected_uci_option == "tabijas") {
       set_option(BOOK_OPTIONS_TABIJAS);
    } else if (selected_uci_option == "wonder_weapons") {
        set_option(BOOK_OPTIONS_WONDER_WEAPONS);
    } else if (selected_uci_option == "solid_mix") {
        set_option(BOOK_OPTIONS_SOLID_MIX);
    } else {
       // Ignore unexpected valiues from a potential stupid / malicious outside world 
    }
}

void CMasterBook::randomize_book_for_this_game() {
    if (boook_option != BOOK_OPTIONS_SOLID_MIX) {
        boook_option_for_this_game = boook_option;
        return;
    }
    float random = float(rand()) / RAND_MAX;
    assert(random >= 0.0);
    assert(random <= 1.0);
    if (random < probability_tabijas) {
        boook_option_for_this_game = BOOK_OPTIONS_TABIJAS;
    } else if (random < (probability_tabijas + probability_wonder_weapons)) {
        boook_option_for_this_game = BOOK_OPTIONS_WONDER_WEAPONS;
    } else {
        boook_option_for_this_game = BOOK_OPTIONS_BROAD_GM;
    }
    std::cerr << "boook_option_for_this_game: " << boook_option_for_this_game << "\n";
}

void CMasterBook::on_new_game() {
    randomize_book_for_this_game();
}

