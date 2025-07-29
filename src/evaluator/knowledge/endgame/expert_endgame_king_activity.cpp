// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_endgame_king_activity.h"
#include "../../../board/board_logic.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/standard_headers.h"

void init_endgame_king() {
    // TODO: move to own class
    assign_psv_table(WHITE_KING, endgame_king_psv_table);
    normalize_average(main_piece_square_value_table_set[WHITE_KING], 20000);
    clone_from_white_to_black(BLACK_KING);
}

bool CExpertEndgameKingActivity::is_responsible() const {
    return CBoardLogic::is_endgame();
}

void CExpertEndgameKingActivity::apply_knowledge() {
    std::cerr << "here is the king\n";
    init_endgame_king();
}


