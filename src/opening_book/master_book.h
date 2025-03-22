#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a small list of short lines,
// just to get some fun and variation.

#include "data_book.h"
#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

typedef enum {
    BOOK_OPTIONS_BROAD_GM,
    BOOK_OPTIONS_TABIJAS,
    BOOK_OPTIONS_WONDER_WEAPONS,
    BOOK_OPTIONS_SOLID_MIX,
} EBookOptions;

typedef std::vector<std::string> TSortedVariationCollection;

class CMasterBook {
  public:
    CMasterBook();
    void on_new_game();
    // Returns a null-move if no move could be found.
    std::string get_move(const std::string &moves_from_startpos_in_uci_format);
    void set_option(const std::string &selected_uci_option);
  private:
    void randomize_book_for_this_game();
    void set_option(EBookOptions option);
  private:
    CDataBook gm_book;
    CDataBook tabijas;
//    CDataBook wonder_weapons_black;
//    CDataBook wonder_weapons_white;
  private:
     EBookOptions boook_option;
     // Pption might be randomized, but should be fix for an entire game
     EBookOptions boook_option_for_this_game;
};

