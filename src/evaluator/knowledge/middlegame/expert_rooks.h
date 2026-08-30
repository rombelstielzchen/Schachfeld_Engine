#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../../piece_square_value_tables.h"
#include "../virtual_expert.h"

class CExpertRooks: public CVirtualExpert {
  private:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
    virtual std::string get_name() const override { return "CExpertRooks"; }
  private:
    void add_to_king_files();
    void add_bonus_to_half_open_files();
    void add_bonuS_to_pawn_lever_files();
    void add_bonus_to_passed_pawn_files();
};

