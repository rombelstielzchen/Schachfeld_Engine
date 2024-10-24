// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_generator.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

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
    // White king, testing all 8 directions separately
    { 3, "8/8/8/PPP5/PKP5/PPP5/8/8 w" },
    { 4, "8/8/8/1PP5/PKP5/PPP5/8/8 w" },
    { 3, "8/8/8/P1P5/PKP5/PPP5/8/8 w" },
    { 4, "8/8/8/PP15/PKP5/PPP5/8/8 w" },
    { 5, "8/8/8/PPP5/1KP5/PPP5/8/8 w" },
    { 5, "8/8/8/PPP5/PK15/PPP5/8/8 w" },
    { 4, "8/8/8/PPP5/PKP5/1PP5/8/8 w" },
    { 4, "8/8/8/PPP5/PKP5/P1P5/8/8 w" },
    { 4, "8/8/8/PPP5/PKP5/PP15/8/8 w" },
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
    // White knight, testing all 8 directions separately
     { 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1p11Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP11p2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/113P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P312/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1p12/2P1P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/211P3/8 w" },
    { 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P113/8 w" },
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
    { 4, "8/1P6/8/8/8/8/8/8 w" },
    { 8, "nnn5/1P6/8/8/8/8/8/8 w" },
    { 12, "n1n5/1P6/8/8/8/8/8/8 w" },
    // White pawns, some double-jumps
    { 2, "8/8/8/8/8/8/P7/8 w" },
    { 16, "8/8/8/8/8/8/PPPPPPPP/8 w" },
    { 9, "8/8/8/8/p1p1pppp/P7/PPPPPPPP/8 w" },
    // White to move, multiple pieces   
    { 28, "3k4/8/8/5Q2/8/8/8/K7 w" },
    { 21, "3k1b1b/3pqppp/3n3r/3p1Q1p/3n3r/3p3p/8/K7 w" },
    { 14, "3k1b1b/3PqPpP/3n3r/3P1Q1P/3n3r/3P3P/8/K7 w" },
    { 0, "8/8/p7/Pp6/RP6/KP6/PP6/8 w" },
    // Eng-passeng
    { 1, "8/8/8/Pp6/8/8/8/8 w - - " },
    { 2, "8/8/8/Pp6/8/8/8/8 w - b6" },
    { 4, "8/8/8/PpP5/8/8/8/8 w - b6" },
    // White castling, no castling rights
    { 10, "8/8/8/8/8/p6p/P6P/R3K2R w -" },
    // White castling, pieces in the way
    { 7, "8/8/8/8/8/p6p/P6P/Rn2K1nR w KQ" },
    // White castling, not yet checking attacked squares
    { 9, "8/8/8/8/8/p7/P7/R3K3 w Q" },
    { 8, "8/8/8/8/8/7p/7P/4K2R w K" },
    // Black pawns, normal moves
    { 3, "8/p7/7p b" },
    // Black pawn captures
    { 4, "8/1p6/P1P b" },
    // Black pawn promotions
    { 8, "8/8/8/8/8/8/1p6/NNN b" },
    // Black pawn, eng-passeng
    { 2, "8/8/8/8/pP b - b3" },
    // Black  king, castling
    { 10, "r3k1Br/p6p/P6P b kq" },
    // Some real-world positions
    { 20, "startpos" },
    { 33, "r1nqkbnr/pppp2pp/2n5/1B2pp2/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq" }
};

bool CTestMoveGenerator::test_everything() {
    BEGIN_TESTSUITE("CTestMoveGenerator");
    EXPECT(test_move_list());
    EXPECT(test_positions());
    return true;
}

bool CTestMoveGenerator::test_positions() {
    CTEST << "CTestMoveGenerator::test_positions() ..." << std::endl;
    for (const STestcaseMoveGenerator &testcase  : testcases) {
        SILENT_EXPECT(test(testcase));
    }
    board.set_start_position();
    CTEST << "CTestMoveGenerator::test_everything(): all " << testcases.size() << " passed." << std::endl;
    return true;
}

bool CTestMoveGenerator::test(const STestcaseMoveGenerator &testcase) {
    assert(testcase.fen_position != "");
    assert(testcase.expected_moves <= MAX_MOVES_IN_CHESS_POSITION);
    CTEST << "Testcase: " << testcase.fen_position << std::endl;
    SILENT_EXPECT(board.set_fen_position(testcase.fen_position));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int generated_moves = move_generator.move_list.list_size();
    SILENT_EXPECT(generated_moves == testcase.expected_moves);
    return true;
}

bool CTestMoveGenerator::test_move_list() {
    CTEST << "CTestMoveGenerator::test_move_list() ..." << std::endl;
    board.set_start_position();
    CMoveGenerator move_generator;
    EXPECT(is_null_move(move_generator.move_list.get_next()));
    move_generator.generate_all();
    constexpr int n_moves_in_startpos = 20;
    EXPECT(move_generator.move_list.list_size() == n_moves_in_startpos);
    for (int j = 0; j < n_moves_in_startpos; ++j) {
        SMove move = move_generator.move_list.get_next();
        SILENT_EXPECT(is_null_move(move) == false);
    }
    EXPECT(is_null_move(move_generator.move_list.get_next()));
    return true;
}

