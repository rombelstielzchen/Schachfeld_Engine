// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "knowledge/endgame/expert_endgame_king_activity.h"
#include "knowledge/endgame/expert_endgame_pawn.h"
#include "knowledge/general/expert_general.h"
#include "knowledge/mating/expert_basic_mating.h"
#include "knowledge/opening/castling_direction/expert_castling_direction.h"
#include "../board/board_logic.h"

// TODO: global?
CExpertGeneral expert_general;
CExpertCastlingDirection expert_castling_direction;
CExpertEndgameKingActivity expert_endgame_king_activity;
CExpertEndgamePawn expert_endgame_pawn;
CExpertBasicMating expert_basic_mating;

COracle::COracle() {
    // Order of insertions = order of execution.
    // Basic experts first, more specialized experts later
    expert_collection.push_back(&expert_general);
    expert_collection.push_back(&expert_castling_direction);
    expert_collection.push_back(&expert_endgame_king_activity);
    expert_collection.push_back(&expert_endgame_pawn);
    expert_collection.push_back(&expert_basic_mating);
}

void COracle::configure_knowledge() {
    assert(expert_collection.size() > 0);
    for (CVirtualExpert* const p_expert: expert_collection) {
        p_expert->configure();
    }
}

