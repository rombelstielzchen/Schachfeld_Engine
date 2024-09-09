// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_generator.h"
#include "../board/board.h"

const std::vector<STestcaseMoveGenerator> testcases = {
    // Empty board
    { 0, "8/8/8/8/8/8/8/8 w" },
    // White king, simple  moves, no castling, no other pieces
    { 3, "K7/8/8/8/8/8/8/8 w" },
    { 5, "1K6/8/8/8/8/8/8/8 w" },
    { 8, "8/1K6/8/8/8/8/8/8 w" },
    // White king, simple moves, no castling, some other pieces
    { 8, "n1n5/1K6/n1n5/8/8/8/8/8 w" },
    { 4, "8/r1r5/P1P5/nKn5/P1P5/8/8/8 w" },
    // White knight, empty board
    { 2, "N7/8/8/8/8/8/8/8 w" },
    
    { 3, "1N6/8/8/8/8/8/8/8 w" },
    { 4, "2N5/8/8/8/8/8/8/8 w" },
    { 4, "8/1N6/8/8/8/8/8/8 w" },
    { 6, "8/2N5/8/8/8/8/8/8 w" },
    { 8, "8/8/2N5/8/8/8/8/8 w" },
    // White knight, some other pieces
    { 8, "qqqq4/8/2N5/8/8/8/8/8 w" },
    { 6, "k7/P7/p1N5/P7/8/8/8/8 w" },
    // White bishop, empty board
    { 7, "8/8/8/8/8/8/8/B7 w" },
    { 7, "8/8/8/8/8/8/8/3B4 w" },
    { 13, "8/8/8/4B3/8/8/8/8 w" },
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
    if (!board.set_fen_position(testcase.fen_position)) {
            std::cerr << "ERROR: invalid FEN-position" << std::endl;
            return false;
    }
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int generated_moves = move_generator.list_size();
    if (generated_moves != testcase.expected_moves) {
        std::cerr << "ERROR: got " << generated_moves << ", expected " << int(testcase.expected_moves) << std:: endl;
        return false;;
    }
    return true;
}

