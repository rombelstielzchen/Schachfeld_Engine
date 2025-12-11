// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_expert_basic_mating.h"
#include "expert_basic_mating.h"
#include "../../test_evaluator.h"
#include "../../../board/board.h"
#include "../../../board/square_constants.h"
#include "../../../technical_functions/testing.h"

bool CTestExpertBasicMating::test_everything() {
    BEGIN_TESTSUITE("CTestExpertBasicMating");
    EXPECT(test_is_responsable());
    EXPECT(test_desired_mating_corner());
    EXPECT(test_gradient());
    return true;
}

bool CTestExpertBasicMating::test_is_responsable() {
    TEST_FUNCTION();
    board.set_start_position();
    CExpertBasicMating expert_basic_mating;
    EXPECT(expert_basic_mating.is_responsible() == false);
    SILENT_EXPECT(board.set_fen_position("k b"));
    EXPECT(expert_basic_mating.is_responsible() == false);
    SILENT_EXPECT(board.set_fen_position("k1K b"));
    EXPECT(expert_basic_mating.is_responsible() == false);
    SILENT_EXPECT(board.set_fen_position("k1KQ b"));
    EXPECT(expert_basic_mating.is_responsible() == true);
    SILENT_EXPECT(board.set_fen_position("k1KQq b"));
    EXPECT(expert_basic_mating.is_responsible() == false);
    return true;
}

bool CTestExpertBasicMating::test_desired_mating_corner() {
    TEST_FUNCTION();
    CExpertBasicMating expert_basic_mating;
    EXPECT(expert_basic_mating.desired_mating_corner(D5) == A8);
    EXPECT(expert_basic_mating.desired_mating_corner(E5) == H8);
    EXPECT(expert_basic_mating.desired_mating_corner(D4) == A1);
    EXPECT(expert_basic_mating.desired_mating_corner(E4) == H1);
    return true;
}

bool CTestExpertBasicMating::test_gradient() {
    TEST_FUNCTION();
    // First check enemies position relative to all 4 corners
    EXPECT(first_position_better("k5KQ/ w", "6KQ/1k w"));
    EXPECT(first_position_better("QK5k/ w", "QK/6k w"));
    EXPECT(first_position_better("///////k5KQ w", "/////2k//6KQ w"));
    EXPECT(first_position_better("///////QK5k w", "/////5k//QK w"));
    // Position of the winning king relative to the losing king
    EXPECT(first_position_better("k//2K/3Q b", "k///2KQ b"));
    // Now with reversed colours.
    // Be careful, "better" is from whites POV"
    EXPECT(first_position_better("6kq/k b", "K5kq/ b"));
    EXPECT(first_position_better("K4k1q/ b", "K5kq/ b"));
    return false;
}

