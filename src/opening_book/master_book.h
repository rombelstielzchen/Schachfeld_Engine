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

typedef std::vector<std::string> TSortedVariationCollection;

class CMasterBook {
  public:
    CMasterBook();
    // Returns a null-move if no move could be found.
    std::string get_move(const std::string &moves_from_startpos_in_uci_format);
  private:
    std::string last_looked_up_moves_from_startpos;
    bool last_lookup_successful;
  private:
    CDataBook gm_book;
    CDataBook wonder_weapons_black;
    CDataBook wonder_weapons_white;
};

