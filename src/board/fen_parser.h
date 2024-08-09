#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// CFenParser: Utility class that sets up the board
// according to a FEN-string received from the UCI "position" command. 
//
// https://www.chessprogramming.org/Forsyth-Edwards_Notation

#include <string>

#include "board.h"

class CFenParser {
  public:
    static bool parse(CBoard &board_to_be_setup, const std::string &fen_board_specification);
  private:
    static bool parse_piece_placement(CBoard &board, const std::string &partial_input);
    static bool parse_side_to_move(CBoard &board, const std::string &partial_input);
    static bool parse_castling_rights(CBoard &board, const std::string &partial_input);
    static bool parse_eng_passeng(CBoard &board, const std::string &partial_input);
    static bool parse_100_ply_draw_counter(CBoard &board, const std::string &partial_input);
    bool parse_move_counter(CBoard &board, const std::string &partial_input);
};

