#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// CFenParser: Utility class that sets up the board
// according to a FEN-string received from the UCI "position" command. 
//
// https://www.chessprogramming.org/Forsyth-Edwards_Notation

#include "board.h"
#include "../technical_functions/standard_headers.h"

class CFenParser {
  public:
    static bool parse(const std::string &fen_board_specification);
  private:
    static bool parse_piece_placement(const std::string &partial_input);
    static bool parse_side_to_move(const std::string &partial_input);
    static bool parse_castling_rights(const std::string &partial_input);
    static bool parse_eng_passeng(const std::string &partial_input);
    static bool parse_100_ply_draw_counter(const std::string &partial_input);
    bool parse_move_counter(const std::string &partial_input);
};

