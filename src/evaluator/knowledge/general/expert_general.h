#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../virtual_expert.h"

class CExpertGeneral : public CVirtualExpert {
  public:
    virtual bool is_responsible() const override;
    virtual void apply_knowledge() override;
};

