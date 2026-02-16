// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_endgame_queen.h"
#include "../../score_constants.h"
#include "../../../board/board_logic.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/engine_test.h"
#include "../../../technical_functions/standard_headers.h"

bool CExpertEndgameQueen::is_responsible() const {
    return (CBoardLogic::is_endgame() && !CEngineTest::is_testing());
}

void CExpertEndgameQueen::apply_knowledge() {
    // d5 is the center of gravity, because:
    //   * forward activity is important
    //   * queenside is usually more important than kingside (passers, week pawns)
    //   * we also want to protect a potentially weak fianchetto-diagonal
    constexpr int evaluation_delta_per_square = 5;
    CPsvModifier::make_gradient(main_piece_square_value_table_set[WHITE_QUEEN], D5, evaluation_delta_per_square);
    CPsvModifier:: normalize_average(main_piece_square_value_table_set[WHITE_QUEEN], score_average_queen);
    CPsvModifier::clone_from_white_to_black(BLACK_QUEEN);
}

