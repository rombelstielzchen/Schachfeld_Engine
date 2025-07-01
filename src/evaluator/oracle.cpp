// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "piece_square_value_tables.h"

COracle::COracle() {
}

void COracle::configure_knowledge() {
    init_main_psv_set();
}

