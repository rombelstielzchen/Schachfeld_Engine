// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_endgame_pawn.h"
#include "../../../board/board_logic.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/engine_test.h"
#include "../../../technical_functions/standard_headers.h"

constexpr int average_endgame_pawn_value = 110;

// General considerations:
//   * pawns are more worth in the endgame (average 110)
//   * 2nd row is average; the king does no longer need shelter
//   * 3rd and 4th row are slightly less worth; keep reserve-tempi
//   * 5th row becomes strong (space-advantage, limiting opponents tempi)
//   * 6th row is super-strong, as explained for the general tables
//   * 7th row slightly weaker, as it sometimes messes things up
//   * ATM we do not distinguish the files; they all have pros and cons
TPieceSquareValueTable endgame_pawn_psv_table = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 },
    { 0,   0, 110, 110, 109, 108, 120, 130, 125, 110 }}};

bool CExpertEndgamePawn::is_responsible() const {
    return (CBoardLogic::is_endgame() && !CEngineTest::is_testing());
}

void CExpertEndgamePawn::apply_knowledge() {
    CPsvModifier::assign_psv_table(WHITE_POWER, endgame_pawn_psv_table);
    CPsvModifier:: normalize_average(main_piece_square_value_table_set[WHITE_POWER], average_endgame_pawn_value);
    CPsvModifier::clone_from_white_to_black(BLACK_POWER);
}

