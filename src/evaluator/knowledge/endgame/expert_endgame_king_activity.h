#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../piece_square_value_tables.h"
#include "../virtual_expert.h"
#include "../../piece_square_value_tables.h"

extern TPieceSquareValueTable endgame_king_psv_table;

extern TPieceSquareValueTable endgame_king_psv_table;

class CExpertEndgameKingActivity: public CVirtualExpert {
  public:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
};

