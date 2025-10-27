#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../piece_square_value_tables.h"
#include "../virtual_expert.h"
#include "../../piece_square_value_tables.h"

// TODO: extern needed
extern TPieceSquareValueTable endgame_pawn_psv_table;

class CExpertEndgamePawn: public CVirtualExpert {
  private:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
    virtual std::string get_name() const override { return "CExpertEndgamePawn"; }
};

