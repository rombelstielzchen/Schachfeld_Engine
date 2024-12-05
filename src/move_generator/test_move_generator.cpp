// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_generator.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

const std::vector<STestcaseMoveGenerator> testcases = {
    // Empty board
    { 0, 0, "8/8/8/8/8/8/8/8 w" },
    // White king, simple  moves, no castling, no other pieces
    { 3, 0, "K7/8/8/8/8/8/8/8 w" },
    { 5, 0, "1K6/8/8/8/8/8/8/8 w" },
    { 8, 0, "8/1K6/8/8/8/8/8/8 w" },
    // White king, simple moves, no castling, some other pieces
    { 8, 4, "n1n5/1K6/n1n5/8/8/8/8/8 w" },
    { 4, 2, "8/r1r5/P1P5/nKn5/P1P5/8/8/8 w" },
    // White king, testing all 8 directions separately
    { 3, 0, "8/8/8/PPP5/PKP5/PPP5/8/8 w" },
    { 4, 0, "8/8/8/1PP5/PKP5/PPP5/8/8 w" },
    { 3, 0, "8/8/8/P1P5/PKP5/PPP5/8/8 w" },
    { 4, 0, "8/8/8/PP15/PKP5/PPP5/8/8 w" },
    { 5, 0, "8/8/8/PPP5/1KP5/PPP5/8/8 w" },
    { 5, 0, "8/8/8/PPP5/PK15/PPP5/8/8 w" },
    { 4, 0, "8/8/8/PPP5/PKP5/1PP5/8/8 w" },
    { 4, 0, "8/8/8/PPP5/PKP5/P1P5/8/8 w" },
    { 4, 0, "8/8/8/PPP5/PKP5/PP15/8/8 w" },
    // White knight, empty board
    { 2, 0, "N7/8/8/8/8/8/8/8 w" },
    
    { 3, 0, "1N6/8/8/8/8/8/8/8 w" },
    { 4, 0, "2N5/8/8/8/8/8/8/8 w" },
    { 4, 0, "8/1N6/8/8/8/8/8/8 w" },
    { 6, 0, "8/2N5/8/8/8/8/8/8 w" },
    { 8, 0, "8/8/2N5/8/8/8/8/8 w" },
    // White knight, some other pieces
    { 8, 2, "qqqq4/8/2N5/8/8/8/8/8 w" },
    { 6, 0, "k7/P7/p1N5/P7/8/8/8/8 w" },
    // White knight, testing all 8 directions separately
     { 0, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1p11Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP11p2/1P3P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/113P2/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P312/1p1N1p2/1Pp1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/11p1pP2/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1p12/2P1P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/211P3/8 w" },
    { 1, 0, "8/2p1p3/1pP1Pp2/1P3P2/1p1N1p2/1Pp1pP2/2P113/8 w" },
    // White bishop, empty board
    { 7, 0, "8/8/8/8/8/8/8/B7 w" },
    { 7, 0, "8/8/8/8/8/8/8/3B4 w" },
    { 13, 0, "8/8/8/4B3/8/8/8/8 w" },
    // White bishop, some pieces
    { 8, 4, "1n6/8/5n2/4B3/8/2n3n1/8/8 w" },
    { 5, 0, "8/5p2/5P2/4B3/2p3p1/2P3P1/8/8 w" },
    // White rook, empty board
    { 14, 0, "8/8/8/8/8/8/8/7R w" },
    { 14, 0, "8/8/8/8/8/8/8/3R4 w" },
    { 14, 0, "8/8/8/8/3R4/8/8/8 w" },
    // White rook, some pieces
    { 10, 4, "8/3n4/8/8/1n1R2n1/8/3n4/8 w" },
    { 9, 1, "8/8/8/1p4p1/1P1R2P1/8/3p4/8 w" },
    // White queen, empty board
    { 21, 0, "8/8/8/8/8/8/8/Q7 w" },
    { 21, 0, "8/8/8/8/8/8/8/3Q4 w" },
    { 27, 0, "8/8/8/3Q4/8/8/8/8 w" },
    // White queen, some pieces
    { 12, 3, "8/8/8/n3n3/8/8/8/Q3n3 w" },
    { 11, 0, "2n1n1n1/2P1P1P1/2p3p1/2P1Q1P1/2P3P1/2P3P1/8/8 w" },
    // White pawns, simple single-jumps. No captures, no promotions, no eng-passeng
    { 8, 0, "8/8/8/8/8/PPPPPPPP/8/8 w" },
    { 3, 0, "8/8/8/8/P1P1P3/P1P1P3/P1P5/8 w" } ,
    { 2, 0, "8/8/8/3PP3/3PP3/3PP3/3PP3/8 w" },
    { 2, 0, "6k1/6P1/5PPP/6P1/6P1/6P1/6P1/8 w" },
    // White pawn, captures, not yet to the 8th rank (promotion)
    { 2, 2, "8/ppp5/1P6/8/8/8/8/8 w" },
    // White pawn, promotion
    { 4, 4, "8/1P6/8/8/8/8/8/8 w" },
    { 8, 8, "nnn5/1P6/8/8/8/8/8/8 w" },
    { 12, 12, "n1n5/1P6/8/8/8/8/8/8 w" },
    // White pawns, some double-jumps
    { 2, 0, "8/8/8/8/8/8/P7/8 w" },
    { 16, 0, "8/8/8/8/8/8/PPPPPPPP/8 w" },
    { 9, 0, "8/8/8/8/p1p1pppp/P7/PPPPPPPP/8 w" },
    // White to move, multiple pieces   
    { 28, 0, "3k4/8/8/5Q2/8/8/8/K7 w" },
    { 21, 7, "3k1b1b/3pqppp/3n3r/3p1Q1p/3n3r/3p3p/8/K7 w" },
    { 14, 0, "3k1b1b/3PqPpP/3n3r/3P1Q1P/3n3r/3P3P/8/K7 w" },
    { 0, 0, "8/8/p7/Pp6/RP6/KP6/PP6/8 w" },
    // Eng-passeng
    { 1, 0, "8/8/8/Pp6/8/8/8/8 w - - " },
    { 2, 1, "8/8/8/Pp6/8/8/8/8 w - b6" },
    { 4, 2, "8/8/8/PpP5/8/8/8/8 w - b6" },
    // White castling, no castling rights
    { 10, 0, "8/8/8/8/8/p6p/P6P/R3K2R w -" },
    // White castling, pieces in the way
    { 7, 2, "8/8/8/8/8/p6p/P6P/Rn2K1nR w KQ" },
    // White castling, not yet checking attacked squares
    { 9, 0, "8/8/8/8/8/p7/P7/R3K3 w Q" },
    { 8, 0, "8/8/8/8/8/7p/7P/4K2R w K" },
    // Black pawns, normal moves
    { 3, 0, "8/p7/7p b" },
    // Black pawn captures
    { 4, 2, "8/1p6/P1P b" },
    // Black pawn promotions
    { 8, 8, "8/8/8/8/8/8/1p6/NNN b" },
    // Black pawn, eng-passeng
    { 2, 1, "8/8/8/8/pP b - b3" },
    // Black  king, castling
    { 10, 1, "r3k1Br/p6p/P6P b kq" },
    // Some real-world positions
    { 20, 0, "startpos" },
    { 33, 3, "r1nqkbnr/pppp2pp/2n5/1B2pp2/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq" },
    // Former bug: black knight moving like a king
    { 2, 0, "n7 b" },
    { 4, 0, "2n5 b" },
    { 8, 0, "8/2ppp3/2pnp3/2P1P3 b" },
    { 0, 0, "4n3/2p3p1/2Pp1pP1/3P1P2 b" },
    // Former bug: phantom eng-passeng from left, stupid brackets
    { 0, 0, "8/8/8/p7/P7/8/8/8 b - a3" },
    // Former bug: slifing pieces and move-ordering
    { 16, 1, "r1k/8/R1K w" },
};

bool CTestMoveGenerator::test_everything() {
    BEGIN_TESTSUITE("CTestMoveGenerator");
    EXPECT(test_prune_silent_moves());
    EXPECT(test_filter_by_target_square());
    EXPECT(test_reuse_list());
    EXPECT(test_shift_current_move_to_top());
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
    CTEST << "Moves: " << generated_moves << "\n";
    SILENT_EXPECT(generated_moves == testcase.expected_moves);
    move_generator.move_list.prune_silent_moves();
    int generated_captures = move_generator.move_list.list_size();
    CTEST << "Captures: " << generated_captures << "\n";
    SILENT_EXPECT(generated_captures == testcase.expected_captures);
    return true;
}

bool CTestMoveGenerator::test_prune_silent_moves() {
    CTEST << "CTestMoveGenerator::test_prune_silent_moves() ..." << std::endl;
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

bool CTestMoveGenerator::test_filter_by_target_square() {
    CTEST << "CTestMoveGenerator::test_filter_by_target_square() ...\n";
    board.set_start_position();
    CMoveGenerator move_generator;
    board.move_maker.play_variation("d2d4 d7d5 c2c4 e7e6 b1c3 g8f6 g1f3 c7c6 c1g5 f8b4 c4d5");
    move_generator.generate_all();
    move_generator.move_list.prune_silent_moves();
    EXPECT(move_generator.move_list.list_size() == 5);
    SSquare d5 = { FILE_D, RANK_5 };
    move_generator.move_list.filter_captures_by_target_square(d5);
    EXPECT(move_generator.move_list.list_size() == 4);
    SMove move = move_generator.move_list.get_least_valuable_aggressor();
    CTEST << "Least_valuanle_aggressot: " << move_as_text(move) << "\n";
    EXPECT((move == "c6d5") || (move == "e6d5"));
    return true;
}

bool CTestMoveGenerator::test_reuse_list() {
    CTEST << "CMoveGenerator::true\n() ...";
    assert(testcases.size() > 42);
    SILENT_EXPECT(board.set_fen_position(testcases[42].fen_position));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    SMove first_move = move_generator.move_list.get_next();
    move_generator.move_list.reuse_list();
    SMove first_move_again = move_generator.move_list.get_next();
    EXPECT(first_move == first_move_again);
    return true;
}
bool CTestMoveGenerator::test_shift_current_move_to_top() {
    CTEST << "CTestMoveGenerator::test_shift_current_move_to_top() ...\n";
    const std::string position = "k1K w";
    SILENT_EXPECT(board.set_fen_position(position));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int former_list_size = move_generator.move_list.list_size();
    SMove former_first = move_generator.move_list.get_next();
    SMove former_second = move_generator.move_list.get_next();
    SMove former_third = move_generator.move_list.get_next();
    move_generator.move_list.shift_current_move_to_top();
    SMove former_fourth = move_generator.move_list.get_next();
    move_generator.move_list.reuse_list();
    EXPECT(move_generator.move_list.list_size() == former_list_size);
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), former_third));
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), former_first));
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), former_second));
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), former_fourth));
    // One more test, reordering a single move
    std::string single_move_position = "8/8/P w";
    SILENT_EXPECT(board.set_fen_position(single_move_position));
    move_generator.generate_all();
    SMove only_move = move_generator.move_list.get_next();
    move_generator.move_list.shift_current_move_to_top();
    move_generator.move_list.reuse_list();
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), only_move)); 
    return true;
}

