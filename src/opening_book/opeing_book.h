#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// A very simple, built-in opening book,
// based on a snall list of short lines,
// just to get some fun and variation.

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

class COpwningBook {
  public:
    COpwningBook();
    // Returns a null-move if no move could be found.
    SMove get_move(std::string moves_from_startpos_in_uci_format);
private:
    int first_matching_index(std::string moves_from_startpos_in_uci_format) const;
    int last_matching_index(std::string moves_from_startpos_in_uci_format) const;
    int random_matching_index(std::string moves_from_startpos_in_uci_format) const;
private:
    std::string last_looked_up_moves_from_startpos;
    bool last_lookup_successfull;
};

