// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "expert_heterogenous_pawn_storm.h"
#include "../opening/castling_direction/safety_evaluator.h"
#include "../../piece_square_value_tables.h"
#include "../../../board/board_logic.h"

bool CExpertHeterogenousPawnStorm::is_responsible() const {
    // TODO: is_middlegame()
    return CBoardLogic::is_heterogebous_castling();
}

void CExpertHeterogenousPawnStorm::apply_knowledge() {
    assert(CBoardLogic::is_heterogebous_castling());
    constexpr int base_value = 70;
    constexpr int bonus_per_step = 5;
    constexpr int black_base_value = -base_value - (RANK_8 - RANK_1) * bonus_per_step;
    if (CBoardLogic::king_position(WHITE_PLAYER) == QUEENSIDE) {
        assert(CBoardLogic::king_position(BLACK_PLAYER) == KINGSIDE);
        CPsvModifier::make_forward_gradient(psv_white_power, FILE_G, base_value, bonus_per_step);
        CPsvModifier::make_forward_gradient(psv_white_power, FILE_H, base_value, bonus_per_step);
        CPsvModifier::make_forward_gradient(psv_black_power, FILE_A, black_base_value, bonus_per_step);
        CPsvModifier::make_forward_gradient(psv_black_power, FILE_B, black_base_value, bonus_per_step);
        return;
    }
    assert(CBoardLogic::king_position(BLACK_PLAYER) == QUEENSIDE);
    assert(CBoardLogic::king_position(WHITE_PLAYER) == KINGSIDE);
    CPsvModifier::make_forward_gradient(psv_white_power, FILE_A, base_value, bonus_per_step);
    CPsvModifier::make_forward_gradient(psv_white_power, FILE_B, base_value, bonus_per_step);
    CPsvModifier::make_forward_gradient(psv_black_power, FILE_G, black_base_value, bonus_per_step);
    CPsvModifier::make_forward_gradient(psv_black_power, FILE_H, black_base_value, bonus_per_step);
}

