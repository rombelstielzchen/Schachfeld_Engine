#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../piece_square_value_tables.h"
#include "../virtual_expert.h"

class CExpertBasicMating: public CVirtualExpert {
    friend class CTestExpertBasicMating;
  private:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
    virtual std::string get_name() const override { return "CExpertBasicMating"; }
  private:
    void configure_king_tables(TPlayerColour winning_side, const SSquare target_square);
    void configure_queen_tables(TPlayerColour winning_side);
    void configure_rook_tables(TPlayerColour winning_side, const SSquare target_square);
    void configure_bishop_tables(TPlayerColour winning_side);
    void configure_knight_tables(TPlayerColour winning_side, const SSquare target_square);
  private:
    void configure_rook_tables__single_rook(TPlayerColour winning_side, const SSquare target_square);
  private:
    TPlayerColour winning_side() const;
    bool is_bishop_and_knight() const;
    SSquare desired_mating_corner(const SSquare losing_king_square) const;
    SSquare desired_mating_corner_for_bishop_and_knight(const SSquare losing_king_square) const;
};

