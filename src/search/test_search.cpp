// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include"test_search.h"
#include "iterative_deepening.h"
#include "search.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"
#include "../universal_chess_interface/command_interface.h"

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
    { 3, "d5e6", "8/1p6/2p1p3/3P3K w" },
    // Two knights under attack, one protected by recapture
    { 4, "a6a4", "8/6k1/R6n/8/n7/8/8/K7 w" }, 
    // Mate in 1, capturing the king in 3 plies
    { 3, "h6h8", "k6q/5R2/7R/8/8/8/8/K7 w" },
    // Skewer
     { 3, "d8a5", "k2b4/8/8/8/8/2K5/8/4Q3 b" },
    // Royal fork for black, no capture at first move
    { 3, "d4c2", "8/8/8/8/3n4/8/8/Q3K2k b" },
    // Smothered mate, very basic
    { 5, "a2g8", "5r1k/6pp/7N/8/8/8/Q7/7K w" },
    // Requires static exchange evaluation and depth >= 2, more than root-node
    { 2, "e6a6", "8/5k2/n3R1b1/8/8/8/8/7K w" },
    { 2, "b8c8", "RRb/p2b w" },
    { 2, "a8a7", "RRb/p2b/4b w" },
    { 2, "d5e4", "q/Bq/2q/3q/4R/5Q/6Q/7Q b" },
    { 2, "b7a7", "q/Bq/2q/3R/4Q/5Q/6Q/7Q b" },
    { 2, "b7a7", "8/Bq/2q/3q/4R/5Q/6Q/7Q b" },
    { 2, "b7a7", "q/Bq/2q/3q/4R/5Q/6B/7Q b" },
    { 2, "c8d8", "rrrQRRR b" },
    { 2, "b8c8", "RRnq/2k w" },
    { 2, "c6b6", "B/1B/1pQ/3b/4b w" },
    // Former bug: counter-attacks in check
    { 4, "h8g8", "5q1k/1q3pp1/8/8/8/8/7Q/K6R b" },
    // Avoid stalemate
    { 2, "d4b6", "/k/p//3q//5Q/7K b" },
};

bool CTestSearch::test_everything() {
    BEGIN_TESTSUITE("CTestSearch");
    bool former_dobb_dobb_dobb = DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop;
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    EXPECT(test_no_legal_moves());
    for (const STestcaseSearch &testcase : testcases) {
        SILENT_EXPECT(test_position(testcase));
    }
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = former_dobb_dobb_dobb;
    return true;
}

bool CTestSearch::test_position(const STestcaseSearch &testcase) {
    assert(testcase.depth > 0);
    assert(testcase.expected_move != "");
    assert(testcase.fen_position != "");
    CTEST << "Searching: " << testcase.fen_position << "\n";
    CTEST << "Expecting: " << testcase.expected_move << "\n";
    board.set_fen_position(testcase.fen_position);
    CIterativeDeepening searcher;
    SMove best_move = searcher.search(testcase.depth);
CTEST << "Got move: " << best_move << "\n";
    EXPECT(best_move == testcase.expected_move);
    return true;
}

bool CTestSearch::test_no_legal_moves() {
    TEST_FUNCTION();
    CSearch search;
    board.set_fen_position("1k//K1Q w");
    EXPECT(search.no_legal_moves() == false);
    board.move_maker.make_null_move();
    EXPECT(search.no_legal_moves() == true);
    return true;
}

