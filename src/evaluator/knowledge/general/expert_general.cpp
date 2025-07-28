// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_general.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/standard_headers.h"

bool CExpertGeneral::is_responsible() const {
    return true;
}

void CExpertGeneral::apply_knowledge() {
    std::cerr << "here I am\n";
    init_main_psv_set();
}


