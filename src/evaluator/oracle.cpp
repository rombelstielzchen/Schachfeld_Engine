// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "oracle.h"
#include "piece_square_value_tables.h"
#include "knowledge/endgame/expert_endgame_king_activity.h"
#include "knowledge/general/expert_general.h"
#include "../board/board_logic.h"

CExpertGeneral expert_general;
CExpertEndgameKingActivity expert_endgame_king_activity;
std::vector<CVirtualExpert*>expert_collection;

COracle::COracle() {
    // Order of insertions = order of execution.
    // Basic exoerts first, more specialized experts later
    expert_collection.push_back(&expert_general);
    expert_collection.push_back(&expert_endgame_king_activity);
}

void COracle::configure_knowledge() {
    for (CVirtualExpert* const p_expert: expert_collection) {
        p_expert->configure();
    }
}

