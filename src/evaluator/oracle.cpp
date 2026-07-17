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
    // Basic experts first, more specialized experts later.
    // Especially endgame and mating last.
    expert_collection.push_back(&expert_general);
    /*** Opening **********************/
    expert_collection.push_back(&expert_castling_direction);
    // TODO: bad squares for the bishop
    // TODO: bad central pawns, creating weaknesses
    // TODO: prevent stupid artificial long castlings, especially in positions where only the f-pawn has moved.
    // TODO: maybe bonus for rook on f/d in order to eencourage real castling 
    // TODO: maybe malus for undevelopped pieces that prevent good castling
    /*** Middlegame *******************/
    // TODO: pawn-storm fafter heterogenous castlings
    // TODO: pawn-lewers
    // TODO: controlling intrusion-squares on open files
    // TODO: bad bishops, encouraging exhange and freeing pawn-moves
    // TODO: minimal bonus for enemy pawns that protect the king?
    /*** Endgame **********************/
    expert_collection.push_back(&expert_endgame_king_activity);
    expert_collection.push_back(&expert_endgame_pawn);
    expert_collection.push_back(&expert_endgame_queen);
    // TODO: key-squares
    // TODO: malus for squares in check after promotion
    // TODO: bonus for king nearby weaknesses
    // TODO: bonus for king on squares where he can't be checked easily (bishop and knight)
    // TODO: uneven exchange
    // TODO: queen on fianchetto-diagonal, preventing perpetual
    /*** Mating ***********************/
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

