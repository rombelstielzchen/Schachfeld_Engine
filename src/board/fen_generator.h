#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// CFenGenerator: utility class that generates a FEN-string for the current position,
// mainly for testing purposes
//
// https://www.chessprogramming.org/Forsyth-Edwards_Notation

#include "../technical_functions/standard_headers.h"

class CBoard;

class CFenGenerator {
  public:
    CFenGenerator();
  public:
    std::string get_fen_position() const;
  private:
    std::string get_piece_placement() const;
    std::string get_side_to_move() const;
    std::string get_castling_rights() const;
    std::string get_eng_passeng() const;
    std::string get_100_ply_draw_counter() const;
    std::string get_move_counter() const;
};

