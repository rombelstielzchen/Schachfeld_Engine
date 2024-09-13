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
    // White bishop, some pieces
    { 8, "1n6/8/5n2/4B3/8/2n3n1/8/8 w" },
    { 5, "8/5p2/5P2/4B3/2p3p1/2P3P1/8/8 w" },
    // White rook, empty board
    { 14, "8/8/8/8/8/8/8/7R w" },
    { 14, "8/8/8/8/8/8/8/3R4 w" },
    { 14, "8/8/8/8/3R4/8/8/8 w" },
    // White rook, some pieces
    { 10, "8/3n4/8/8/1n1R2n1/8/3n4/8 w" },
    { 9, "8/8/8/1p4p1/1P1R2P1/8/3p4/8 w" },
    // White queen, empty board
    { 21, "8/8/8/8/8/8/8/Q7 w" },
    { 21, "8/8/8/8/8/8/8/3Q4 w" },
    { 27, "8/8/8/3Q4/8/8/8/8 w" },
    // White queen, some pieces
    { 12, "8/8/8/n3n3/8/8/8/Q3n3 w" },
    { 11, "2n1n1n1/2P1P1P1/2p3p1/2P1Q1P1/2P3P1/2P3P1/8/8 w" },
    // White pawns, simple single-jumps. No captures, no promotions, no eng-passeng
    { 8, "8/8/8/8/8/PPPPPPPP/8/8 w" },
    { 3, "8/8/8/8/P1P1P3/P1P1P3/P1P5/8 w" } ,
    { 2, "8/8/8/3PP3/3PP3/3PP3/3PP3/8 w" },
    { 2, "6k1/6P1/5PPP/6P1/6P1/6P1/6P1/8 w" },
    // White pawn, captures, not yet to the 8th rank (promotion)
    { 2, "8/ppp5/1P6/8/8/8/8/8 w" },
    // White pawn, promotion
    { 4, "8/1P6/8/8/8/8/8/8 w"},
    { 8, "nnn5/1P6/8/8/8/8/8/8 w"},
    { 12, "n1n5/1P6/8/8/8/8/8/8 w"},
    // White pawns, some double-jumps
//    { 2, "8/8/8/8/8/8/P7/8 w" },
    // White to move, multiple pieces   
    { 28, "3k4/8/8/5Q2/8/8/8/K7 w" },
    { 21, "3k1b1b/3pqppp/3n3r/3p1Q1p/3n3r/3p3p/8/K7 w" },
    { 14, "3k1b1b/3PqPpP/3n3r/3P1Q1P/3n3r/3P3P/8/K7 w"},
    { 0, "8/8/p7/Pp6/RP6/KP6/PP6/8 w" },
};

bool CTestMoveGenerator::test_all() {
    std::cerr << "CTestMoveGenerator::test_all()" << std::endl;
    for (const STestcaseMoveGenerator &testcase  : testcases) {
        if (!test(testcase)) {
           return false;
        }
    }
    board.set_start_position();
    std::cerr << "CTestMoveGenerator::test_all(): all " << testcases.size() << " passed." << std::endl;
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

