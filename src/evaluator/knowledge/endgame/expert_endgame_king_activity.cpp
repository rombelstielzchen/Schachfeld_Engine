// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_endgame_king_activity.h"
#include "../../../board/board_logic.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/standard_headers.h"

TPieceSquareValueTable endgame_king_psv_table = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   210,   210,   210,   210,   210,   210,   210,   210 },
    { 0,   0,   210,   220,   220,   220,   220,   220,   220,   210 },
    { 0,   0,   210,   220,   230,   230,   230,   232,   220,   210 },
    { 0,   0,   210,   220,   230,   240,   250,   235,   220,   210 },
    { 0,   0,   210,   220,   230,   240,   245,   235,   220,   210 },
    { 0,   0,   210,   220,   230,   230,   230,   232,   220,   210 },
    { 0,   0,   210,   220,   220,   220,   220,   220,   220,   210 },
    { 0,   0,   210,   210,   210,   210,   210,   210,   210,   210 }}};

bool CExpertEndgameKingActivity::is_responsible() const {
    return CBoardLogic::is_endgame();
}

void CExpertEndgameKingActivity::apply_knowledge() {
    CPsvModifier::assign_psv_table(WHITE_KING, endgame_king_psv_table);
    CPsvModifier:: normalize_average(main_piece_square_value_table_set[WHITE_KING], 20000);
    CPsvModifier::clone_from_white_to_black(BLACK_KING);
}


