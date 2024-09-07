// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../board/board.h"
#include "test_move_generator.h"

const std::vector<STestcaseMoveGenerator> testcases = {
    // Empty board
    { 0, "8/8/8/8/8/8/8/8 w" },
    // Simple white king moves, no castling, no other pieces
    { 3, "K7/8/8/8/8/8/8/8 w" },
    { 5, "1K6/8/8/8/8/8/8/8 w" },
    { 8, "8/1K6/8/8/8/8/8/8/8 w" },
    // Simple white king moves, no castling, some other pieces
    { 8, "n1n5/1K6/n1n5/8/8/8/8/8/8 w" },
    { 8, "Q1R5/1K6/BNP5/8/8/8/8/8/8 w" }
};

bool CTestMoveGenerator::test_all() {
    std::cerr << "CTestMoveGenerator::test_all" << std::endl;
    for (const STestcaseMoveGenerator &testcase  : testcases) {
        if (!test(testcase)) {
           return false;
        }
    }
    return true;
}

bool CTestMoveGenerator::test(const STestcaseMoveGenerator &testcase) {
    assert(testcase.fen_position != "");
    assert(testcase.expected_moves <= MAX_MOVES_IN_CHESS_POSITION);
    std::cerr << "Testcase: " << testcase.fen_position << std::endl;
    bool result = board.set_fen_position(testcase.fen_position);
    CMoveGenerator move_generator;
    move_generator.generate_all(WHITE_TO_MOVE); //!!!
    int generated_moves = move_generator.list_size();
    result &= (generated_moves == testcase.expected_moves);
    return result;
}


