#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "safety_evaluator.h"
#include "../../../piece_square_value_tables.h"
#include "../../virtual_expert.h"

class CExpertCastlingDirection: public CVirtualExpert {
  public:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
    virtual std::string get_name() const override { return "CExpertCastlingDirection"; }
  private:
    void adapt_castling_squares(bool player, int king_position);
    void adapt_castling_squares(TPieceSquareValueTable &psv, const SKingSquareGroup &square_group, int malus);
};

