// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_generator.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseMoveGenerator> testcases = {
    // Empty board
    { 0, 0, 0, "8/8/8/8/8/8/8/8 w" },
    // White king, simple  moves, no castling, no other pieces
    { 3, 0, 3, "K7/8/8/8/8/8/8/8 w" },
    { 5, 0, 5, "1K6/8/8/8/8/8/8/8 w" },
    { 8, 0, 8, "8/1K6/8/8/8/8/8/8 w" },
    // White king, simple moves, no castling, some other pieces
    { 8, 4, 4, "n1n5/1K6/n1n5/8/8/8/8/8 w" },
    { 4, 2, 4, "8/r1r5/P1P5/nKn5/P1P5/8/8/8 w" },
    // White king, testing all 8 directions separately
    { 3, 0, 3, "8/8/8/PPP5/PKP5/PPP5/8/8 w" },
    { 4, 0, 4, "8/8/8/1PP5/PKP5/PPP5/8/8 w" },
    { 3, 0, 3, "8/8/8/P1P5/PKP5/PPP5/8/8 w" },
    { 4, 0, 4, "8/8/8/PP15/PKP5/PPP5/8/8 w" },
    { 5, 0, 5, "8/8/8/PPP5/1KP5/PPP5/8/8 w" },
    { 5, 0, 5, "8/8/8/PPP5/PK15/PPP5/8/8 w" },
    { 4, 0, 4, "8/8/8/PPP5/PKP5/1PP5/8/8 w" },
    { 4, 0, 4, "8/8/8/PPP5/PKP5/P1P5/8/8 w" },
    { 4, 0, 4, "8/8/8/PPP5/PKP5/PP15/8/8 w" },
    // White knight, empty board
    { 2, 0, 2, "N7/8/8/8/8/8/8/8 w" },
    { 3, 0, 3, "1N6/8/8/8/8/8/8/8 w" },
    { 4, 0, 4, "2N5/8/8/8/8/8/8/8 w" },
    { 4, 0, 4, "8/1N6/8/8/8/8/8/8 w" },
    { 6, 0, 6, "8/2N5/8/8/8/8/8/8 w" },
    { 8, 0, 8, "8/8/2N5/8/8/8/8/8 w" },
    // White knight, some other pieces
    { 8, 2, 8, "qqqq4/8/2N5/8/8/8/8/8 w" },
    { 6, 0, 6, "k7/P7/p1N5/P7/8/8/8/8 w" },
    // White knight, testing all 8 directions separately
     { 0, 0, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1p11Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP11p2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/113P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P312/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1p12/2P1P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/211P3/8 w" },
    { 1, 0, 1, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P113/8 w" },
    // White bishop, empty board
    { 7, 0, 7, "8/8/8/8/8/8/8/B7 w" },
    { 7, 0, 7, "8/8/8/8/8/8/8/3B4 w" },
    { 13, 0, 13, "8/8/8/4B3/8/8/8/8 w" },
    // White bishop, some pieces
    { 8, 4, 8, "1n6/8/5n2/4B3/8/2n3n1/8/8 w" },
    { 5, 0, 5, "8/5p2/5P2/4B3/2p3p1/2P3P1/8/8 w" },
    // White rook, empty board
    { 14, 0, 14, "8/8/8/8/8/8/8/7R w" },
    { 14, 0, 14, "8/8/8/8/8/8/8/3R4 w" },
    { 14, 0, 14, "8/8/8/8/3R4/8/8/8 w" },
    // White rook, some pieces
    { 10, 4, 10, "8/3n4/8/8/1n1R2n1/8/3n4/8 w" },
    { 9, 1, 9, "8/8/8/1p4p1/1P1R2P1/8/3p4/8 w" },
    // White queen, empty board
    { 21, 0, 21, "8/8/8/8/8/8/8/Q7 w" },
    { 21, 0, 21, "8/8/8/8/8/8/8/3Q4 w" },
    { 27, 0, 27, "8/8/8/3Q4/8/8/8/8 w" },
    // White queen, some pieces
    { 12, 3, 12, "8/8/8/n3n3/8/8/8/Q3n3 w" },
    { 11, 0, 11, "2n1n1n1/2P1P1P1/2p3p1/2P1Q1P1/2P3P1/2P3P1/8/8 w" },
    // White pawns, simple single-jumps. No captures, no promotions, no eng-passeng
    { 8, 0, 8, "8/8/8/8/8/PPPPPPPP/8/8 w" },
    { 3, 0, 3, "8/8/8/8/P1P1P3/P1P1P3/P1P5/8 w" } ,
    { 2, 0, 2, "8/8/8/3PP3/3PP3/3PP3/3PP3/8 w" },
    { 2, 0, 2, "6k1/6P1/5PPP/6P1/6P1/6P1/6P1/8 w" },
    // White pawn, captures, not yet to the 8th rank (promotion)
    { 2, 2, 2, "8/ppp5/1P6/8/8/8/8/8 w" },
    // White pawn, promotion
    { 4, 4, 4, "8/1P6/8/8/8/8/8/8 w" },
    { 8, 8, 8, "nnn5/1P6/8/8/8/8/8/8 w" },
    { 12, 12, 12, "n1n5/1P6/8/8/8/8/8/8 w" },
    // White pawns, some double-jumps
    { 2, 0, 2, "8/8/8/8/8/8/P7/8 w" },
    { 16, 0, 16, "8/8/8/8/8/8/PPPPPPPP/8 w" },
    { 9, 0, 9, "8/8/8/8/p1p1pppp/P7/PPPPPPPP/8 w" },
    // White to move, multiple pieces   
    { 28, 0, 28, "3k4/8/8/5Q2/8/8/8/K7 w" },
    { 21, 7, 21, "3k1b1b/3pqppp/3n3r/3p1Q1p/3n3r/3p3p/8/K7 w" },
    { 14, 0, 14, "3k1b1b/3PqPpP/3n3r/3P1Q1P/3n3r/3P3P/8/K7 w" },
    { 0, 0, 0, "8/8/p7/Pp6/RP6/KP6/PP6/8 w" },
    // Eng-passeng
    { 1, 0, 1, "8/8/8/Pp6/8/8/8/8 w - - " },
    { 2, 1, 2, "8/8/8/Pp6/8/8/8/8 w - b6" },
    { 4, 2, 4, "8/8/8/PpP5/8/8/8/8 w - b6" },
    // White castling, no castling rights
    { 10, 0, 10, "8/8/8/8/8/p6p/P6P/R3K2R w -" },
    // White castling, pieces in the way
    { 7, 2, 5, "8/8/8/8/8/p6p/P6P/Rn2K1nR w KQ" },
    // White castling, not yet checking attacked squares
    { 9, 0, 9, "8/8/8/8/8/p7/P7/R3K3 w Q" },
    { 8, 0, 8, "8/8/8/8/8/7p/7P/4K2R w K" },
    // Black pawns, normal moves
    { 3, 0, 3, "8/p7/7p b" },
    // Black pawn captures
    { 4, 2, 4, "8/1p6/P1P b" },
    // Black pawn promotions
    { 8, 8, 8, "8/8/8/8/8/8/1p6/NNN b" },
    // Black pawn, eng-passeng
    { 2, 1, 2, "8/8/8/8/pP b - b3" },
    // Black  king, castling
    { 10, 1, 9, "r3k1Br/p6p/P6P b kq" },
    // Some real-world positions
    { 20, 0, 20, "startpos" },
    { 33, 3, 33, "r1nqkbnr/pppp2pp/2n5/1B2pp2/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq" },
    // Former bug: black knight moving like a king
    { 2, 0, 2, "n7 b" },
    { 4, 0, 4, "2n5 b" },
    { 8, 0, 8, "8/2ppp3/2pnp3/2P1P3 b" },
    { 0, 0, 0, "4n3/2p3p1/2Pp1pP1/3P1P2 b" },
    // Former bug: phantom eng-passeng from left, stupid brackets
    { 0, 0, 0, "8/8/8/p7/P7/8/8/8 b - a3" },
    // Former bug: sliding pieces and move-ordering
    { 16, 1, 13, "r1k/8/R1K w" },
    // Legality: king nearly stale_mate
    { 5, 0, 1, "1K/3q w" },
    // Legality: not capturing the protected attacker
    { 9, 1, 1, "8/8/8/8/8/5q/3n2KP w" },
    // Legality: stalemate
    { 3, 0, 0, "k/2Q b" },
    // Legality: castling over controlled squares
    { 12, 1, 8, "8/8/8/8/8/p6p/P3p2P/R3K2R w KQ" },
    { 12, 0, 6, "r3k2r/p6p/P6P/3R1R b kq" },
    // Legality: castling, king in check
    { 12, 1, 5, "8/8/8/8/8/p6p/P4p1P/R3K2R w KQ" },
    { 12, 0, 4, "r3k2r/p6p/P6P/4R b kq" },

};

bool CTestMoveGenerator::test_everything() {
    BEGIN_TESTSUITE("CTestMoveGenerator");
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
    assert(testcase.expected_pseudo_legal_moves <= MAX_MOVES_IN_CHESS_POSITION);
    CTEST << "Testcase: " << testcase.fen_position << std::endl;
    SILENT_EXPECT(board.set_fen_position(testcase.fen_position));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int generated_moves = move_generator.move_list.list_size();
    CTEST << "Pseudo-legal moves: " << generated_moves << "\n";
    SILENT_EXPECT(generated_moves == testcase.expected_pseudo_legal_moves);
    move_generator.move_list.prune_silent_moves();
    int generated_captures = move_generator.move_list.list_size();
    CTEST << "Pseudo-legal captures (method 1): " << generated_captures << "\n";
    SILENT_EXPECT(generated_captures == testcase.expected_pseudo_legal_captures);
    move_generator.move_list.clear();
    move_generator.generate_captures();
    generated_captures = move_generator.move_list.list_size();
    CTEST << "Pseudo-legal captures (method 2): " << generated_captures << "\n";
    move_generator.move_list.clear();
//    SILENT_EXPECT(generated_captures == testcase.expected_pseudo_legal_captures);
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
   int strictly_legal_moves = move_generator.move_list.list_size();
   CTEST << "Expected legal moves: " << int(testcase.expected_legal_moves) << "\n";
    CTEST << "Legal moves: " << strictly_legal_moves << "\n";
    SILENT_EXPECT(strictly_legal_moves == testcase.expected_legal_moves);
    return true;
}

