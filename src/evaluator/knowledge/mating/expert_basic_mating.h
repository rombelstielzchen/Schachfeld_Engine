#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../piece_square_value_tables.h"
#include "../virtual_expert.h"

///extern TPieceSquareValueTable endgame_king_psv_table;

class CExpertBasicMating: public CVirtualExpert {
    friend class CTestExpertBasicMating;
  private:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
    virtual std::string get_name() const override { return "CExpertBasicMating"; }
  private:
    void configure_king_tables(bool winning_side);
    void configure_queen_tables(bool winning_side);
    void configure_rook_tables(bool winning_side);
    void configure_knight_tables(bool winning_side);
  private:
    bool winning_side() const;
    SSquare desired_mating_corner(const SSquare losing_king_square) const;
};

