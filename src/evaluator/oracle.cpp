// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "piece_square_value_tables.h"
#include "../board/board_logic.h"

void init_endgame_king() {
    // TODO: move to own class
    assign_psv_table(WHITE_KING, endgame_king_psv_table);
    normalize_average(main_piece_square_value_table_set[WHITE_KING], 20000);
    clone_from_white_to_black(BLACK_KING);

}

COracle::COracle() {
}

void COracle::configure_knowledge() {
    init_main_psv_set();
    if (CBoardLogic::is_endgame()) {
        init_endgame_king();
    }
}

