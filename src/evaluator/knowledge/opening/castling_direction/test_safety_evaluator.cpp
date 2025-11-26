// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_safety_evaluator.h"
#include "safety_evaluator.h"
#include "../../../../board/board.h"
#include "../../../../technical_functions/standard_headers.h"
#include "../../../../technical_functions/testing.h"

bool CTestSafetyEvaluator::test_everything() {
    BEGIN_TESTSUITE("CTestSafetyEvaluator");
    std::string funny_pawn_structure = "4k3/3ppp2/8/8/8/8/1PP3PP/2K3K1 w - - 0 1";
    SILENT_EXPECT(board.set_fen_position(funny_pawn_structure));
    // TODO: care about uncastled kings and the double effect to squares on the f-file
//    EXPECT(CSafetyEvaluator::king_safety(BLACK_PLAYER, UNCASTLED) == EXCELLENT_KING_POSITION);
    EXPECT(CSafetyEvaluator::king_safety(WHITE_PLAYER, QUEENSIDE) == GOOD_KING_POSITION);
    EXPECT(CSafetyEvaluator::king_safety(WHITE_PLAYER, KINGSIDE) == GOOD_KING_POSITION);
    std::string another_funny_pawn_structure = "2k3k1/p1p3p1/1p5p/8/6P1/1P6/2P2P1P/2K3K1 w - - 0 1";
    SILENT_EXPECT(board.set_fen_position(another_funny_pawn_structure));
    EXPECT(CSafetyEvaluator::king_safety(BLACK_PLAYER, QUEENSIDE) == GOOD_KING_POSITION);
    EXPECT(CSafetyEvaluator::king_safety(BLACK_PLAYER, KINGSIDE) == MEDIOCRE_KING_POSITION);
    EXPECT(CSafetyEvaluator::king_safety(WHITE_PLAYER, QUEENSIDE) == MEDIOCRE_KING_POSITION);
    EXPECT(CSafetyEvaluator::king_safety(WHITE_PLAYER, KINGSIDE) == UNSAFE_KING_POSITION);
    return true;
}

