// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_general.h"
#include "../../piece_square_value_tables.h"
#include "../../../technical_functions/standard_headers.h"

TPieceSquareValueTable psv_white_king = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 120, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 130, 120, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 115, 118, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 125, 130, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 110, 100, 100, 100, 100, 100, 100, 100 }}};
TPieceSquareValueTable psv_white_queen = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100,  70, 100 },
    { 0,   0, 100, 102,  90, 107, 107, 107, 100, 100 },
    { 0,   0, 100, 101,  95, 111, 117, 112, 100, 100 },
    { 0,   0, 100, 102, 105, 112, 119, 110, 100, 100 },
    { 0,   0, 100, 100, 107, 107, 109, 111, 110, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 110, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 110, 110 }}};

TPieceSquareValueTable psv_white_rook = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 140, 120 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 135, 120 }}};

// The kings bishop is worth more in general, but offensive and defensive.
// Therefore the values are not symmetric, difference 15
// TODO
TPieceSquareValueTable psv_white_bishop = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0, 100, 120, 120, 120, 120, 120, 120, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 150, 150, 140, 100, 100 },
    { 0,   0, 100, 100, 130, 130, 130, 130, 100, 100 },
    { 0,   0, 100, 120, 120, 120, 120, 120, 120, 100 },
    { 0,   0, 100, 100, 100, 100, 100, 100, 100, 100 }}};
TPieceSquareValueTable psv_white_knight = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,  60,  70,  80,  80,  80,  80,  70,  60 },
    { 0,   0,  70,  80,  90,  90,  90,  90,  80,  70 },
    { 0,   0,  80,  90, 125, 125, 125, 125,  90,  80 },
    { 0,   0,  80,  90, 125, 145, 145, 135,  90,  80 },
    { 0,   0,  80,  90, 130, 150, 150, 140,  90,  80 },
    { 0,   0,  80,  90, 130, 130, 130, 135,  90,  80 },
    { 0,   0,  70,  80,  90,  90,  90,  90,  80,  70 },
    { 0,   0,  60,  70,  80,  80,  80,  80,  70,  60 }}};

TPieceSquareValueTable psv_white_power = {{
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
    { 0,   0, 100, 100,  97,  95,  96, 110, 108, 100 },
    { 0,   0, 100, 110, 105, 110, 100, 120, 117, 100 },
    { 0,   0, 100, 121, 110, 113, 110, 120, 117, 100 },
    { 0,   0, 100, 100, 115, 125, 114, 130, 127, 100 },
    { 0,   0, 100, 100, 112, 130, 124, 135, 132, 100 },
    { 0,   0, 100, 130, 115, 120, 114, 130, 127, 100 },
    { 0,   0, 100, 120, 115, 100, 100, 130, 127, 100 },
    { 0,   0, 100, 110, 105, 100, 104, 120, 117, 100 }}};

bool CExpertGeneral::is_responsible() const {
    return true;
}

void CExpertGeneral::apply_knowledge() {
   DEBUG_METHOD(); 
   CPsvModifier::normalize_average(psv_white_power, 100);
    CPsvModifier::assign_psv_table(WHITE_POWER, psv_white_power);
    CPsvModifier::normalize_average(psv_white_knight, 290);
    CPsvModifier::assign_psv_table(WHITE_KNIGHT, psv_white_knight);
    CPsvModifier::normalize_average(psv_white_bishop, 320);
    CPsvModifier::assign_psv_table(WHITE_BISHOP, psv_white_bishop);
    CPsvModifier::normalize_average(psv_white_rook, 470);
    CPsvModifier::assign_psv_table(WHITE_ROOK, psv_white_rook);
    CPsvModifier::normalize_average(psv_white_queen, 890);
    CPsvModifier::assign_psv_table(WHITE_QUEEN, psv_white_queen);
    CPsvModifier::normalize_average(psv_white_king, 20000);
    CPsvModifier::assign_psv_table(WHITE_KING, psv_white_king);
    CPsvModifier::clone_from_white_to_black(BLACK_POWER);
    CPsvModifier::clone_from_white_to_black(BLACK_KNIGHT);
    CPsvModifier::clone_from_white_to_black(BLACK_BISHOP);
    CPsvModifier::clone_from_white_to_black(BLACK_ROOK);
    CPsvModifier::clone_from_white_to_black(BLACK_QUEEN);
    CPsvModifier::clone_from_white_to_black(BLACK_KING);
}

