// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"test_search.h"
#include "search.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseSearch> testcases = {
    // Capturing the king
    { 1, "g7g8", "6k1/6Q1/6K1 w" },
    // Capturing the queen with royal fork and perpetual
    { 1, "f4g6", "2q2rk1/4qn1n/6q1/8/5N1q/8/8/8/1K6 q w" },
    // Capturing the queen with mate
    { 1, "a1h1", "7k/8/8/8/8/8/6R1/R6q w" },
    // Black to move: capturing the queen with mate
    { 1, "a1h1", "7K/8/8/8/8/8/6r1/r6Q b" },
    // Two pawns under attack, one protected by recapture
    { 2, "d5e6", "8/1p6/2p1p3/3P4 w" },
    // Two knights under attack, one protected by recapture
//    { 2, "a6a4", "8/6k1/R6n/8/n7/8/8/K7 w" }, 
    // Mate in 1, capturing the king in 3 plies
    { 3, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    // Skewer
     { 2, "d8a5", "k2b4/8/8/8/8/2K5/8/4Q3 b" },
    // Royal fork for black, no capture at first move
    { 2, "d4c2", "8/8/8/8/3n4/8/8/Q3K2k b" },
    // Smothered mate, very basic
    { 4, "a2g8", "5r1k/6pp/7N/8/8/8/Q7/7K w" },
};
// Requires recapture-extension
//    { 2, "e6a6", "8/5k2/n3R1n1/8/8/8/8/7K w" },

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
    SMove best_move = searcher.search(testcase.depth);
    CTEST << "Got move: " << move_as_text(best_move) << "\n";
    EXPECT(move_as_text(best_move) == testcase.expected_move);
    return true;
}

