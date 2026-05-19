// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "knowledge/endgame/expert_endgame_king_activity.h"
#include "knowledge/endgame/expert_endgame_pawn.h"
#include "knowledge/endgame/expert_endgame_queen.h"
#include "knowledge/general/expert_general.h"
#include "knowledge/mating/expert_basic_mating.h"
#include "knowledge/opening/castling_direction/expert_castling_direction.h"
#include "../board/board_logic.h"

COracle::COracle() {
    // static experts here for global lifetime and proper order of initialization
    static CExpertGeneral expert_general;
    static CExpertCastlingDirection expert_castling_direction;
    static CExpertEndgameKingActivity expert_endgame_king_activity;
    static CExpertEndgamePawn expert_endgame_pawn;
    static CExpertEndgameQueen expert_endgame_queen;
    static CExpertBasicMating expert_basic_mating;
    // Order of insertions = order of execution.
    // Basic experts first, more specialized experts later
    expert_collection.push_back(&expert_general);
    expert_collection.push_back(&expert_castling_direction);
    expert_collection.push_back(&expert_endgame_king_activity);
    expert_collection.push_back(&expert_endgame_pawn);
    expert_collection.push_back(&expert_endgame_queen);
    expert_collection.push_back(&expert_basic_mating);
}

void COracle::configure_knowledge() {
    assert(expert_collection.size() > 0);
    for (CVirtualExpert *expert: expert_collection) {
        assert(expert != nullptr);
        assert(typeid(*expert).name());
        expert->configure();
    }
}

