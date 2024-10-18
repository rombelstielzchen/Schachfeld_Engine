// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"test_search.h"
#include "search.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseSearch> testcases = {
    // Vapturing the king
    { 1, "g7g8", "6k1/6Q1/6J1 w" }
};

bool CTestSearch::test_everything() {
    BEGIN_TESTSUITE("CTestSearch");
    for (const STestcaseSearch &testcase : testcases) {
        SILENT_EXPECT(test_position(testcase));
    }
    return true;
}

bool CTestSearch::test_position(const STestcaseSearch &testcase) {
    CTEST << "Searching: " << testcase.fen_position << "\n";
    CTEST << "Expecting: " << testcase.expected_move << "\n";
    board.set_fen_position(testcase.fen_position);
    CSearch searcher;
    SMove best_move = searcher.search();
    CTEST << "Got move: " << move_as_text(best_move) << "\n";
    EXPECT(move_as_text(best_move) == testcase.expected_move);
    return true;
}

