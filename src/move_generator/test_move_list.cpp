// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_list.h"
#include "move_generator.h"
#include "../board/board.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestMoveList::test_everything() {
    BEGIN_TESTSUITE("CTestMoveList");
    EXPECT(test_basics());
    EXPECT(test_prune_silent_moves());
    EXPECT(test_filter_by_target_square());
    EXPECT(test_reuse_list());
    EXPECT(test_shift_current_move_to_top());
    EXPECT(test_remove());
    EXPECT(test_extremes());
    EXPECT(test_get_best_capture());
    EXPECT(test_move_lookup());
    return true;
}

bool CTestMoveList::test_prune_silent_moves() {
   TEST_FUNCTION(); 
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
    move_generator.move_list.reuse_list();
    EXPECT(move_generator.move_list.list_size() == n_moves_in_startpos);
    move_generator.move_list.prune_silent_moves();
    EXPECT(move_generator.move_list.is_empty());
    EXPECT(move_generator.move_list.get_next() == NULL_MOVE);
    move_generator.move_list.unprune_silent_moves();
    EXPECT(move_generator.move_list.list_size() == n_moves_in_startpos);
    return true;
}

bool CTestMoveList::test_filter_by_target_square() {
    TEST_FUNCTION(); 
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
    CTEST << "Least_valuable_aggressor: " << move << "\n";
    EXPECT((move == "c6d5") || (move == "e6d5"));
    return true;
}

bool CTestMoveList::test_reuse_list() {
    TEST_FUNCTION(); 
    board.set_start_position();
    CMoveGenerator move_generator;
    move_generator.generate_all();
    SMove first_move = move_generator.move_list.get_next();
    move_generator.move_list.reuse_list();
    SMove first_move_again = move_generator.move_list.get_next();
    EXPECT(first_move == first_move_again);
    return true;
}

bool CTestMoveList::test_shift_current_move_to_top() {
    TEST_FUNCTION(); 
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
    move_generator.move_list.clear();
    move_generator.generate_all();
    SMove only_move = move_generator.move_list.get_next();
    move_generator.move_list.shift_current_move_to_top();
    move_generator.move_list.reuse_list();
    EXPECT(move_coords_are_equal(move_generator.move_list.get_next(), only_move)); 
    return true;
}

bool CTestMoveList::test_remove() {
    TEST_FUNCTION(); 
    std::string nearly_stalemate = "1k/3Q b";
    SILENT_EXPECT(board.set_fen_position(nearly_stalemate));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    EXPECT(move_generator.move_list.consumer_position <= LIST_ORIGIN);
    SILENT_EXPECT(move_generator.move_list.list_size() == 5);
    constexpr SMove illegal_move = {{FILE_B, RANK_8}, C8, MOVE_TYPE_NORMAL, EMPTY_SQUARE,0};
    EXPECT(move_generator.move_list.consumer_position <= LIST_ORIGIN);
   move_generator.move_list.remove(illegal_move);
    EXPECT(move_generator.move_list.consumer_position <= LIST_ORIGIN);
    EXPECT(move_generator.move_list.list_size() == 4);
    move_generator.move_list.filter_captures_by_target_square(C8);
    EXPECT(move_generator.move_list.is_empty());
    return true;
}

bool CTestMoveList::test_basics() {
    TEST_FUNCTION();
    board.set_start_position();
    CMoveGenerator move_generator;
    move_generator.generate_all();
    EXPECT(move_generator.move_list.move_on_list("g1f3"));
    EXPECT(move_generator.move_list.move_on_list("h1h3") == false);
    return true;
}

bool CTestMoveList::test_extremes() {
    TEST_FUNCTION();
    const std::string position_with_218_moves = "3Q4/1Q4Q1/4Q3/2Q4R/Q4Q2/3Q4/1Q4Rp/1K1BBNNk w - - 0 1";
    SILENT_EXPECT(board.set_fen_position(position_with_218_moves));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    EXPECT(move_generator.move_list.list_size() == 218);
    std::string position_with_74_captures = "r1n1n1b/1P1P21P/1N1N1N/2RnQrRq/2pKp/3BNQbQ/k/4Bq w";
    SILENT_EXPECT(board.set_fen_position(position_with_74_captures));
    move_generator.move_list.clear();
    move_generator.generate_captures();
    CTEST << move_generator.move_list.as_text() << "\n";
    // TODO: revisit this. 74/78? 
    EXPECT(move_generator.move_list.list_size() == 78);
    return true;
}

bool CTestMoveList::test_get_best_capture() {
    TEST_FUNCTION();
    const std::string test_position = "5Q1K/4R3/6n1/4B3/5N1P/8/1p6/8 b - - 0 1";
    SILENT_EXPECT(board.set_fen_position(test_position));
    CMoveGenerator move_generator;
    move_generator.generate_captures();
    EXPECT(move_generator.move_list.list_size() == 10);
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6h8");
    EXPECT(move_generator.move_list.get_next__best_capture() == "b2b1q");
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6f8");
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6e7");
    EXPECT(move_generator.move_list.get_next__best_capture() == "b2b1n");
    EXPECT(move_generator.move_list.get_next__best_capture() == "b2b1r");
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6e5");
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6f4");
    EXPECT(move_generator.move_list.get_next__best_capture() == "b2b1b");
    EXPECT(move_generator.move_list.get_next__best_capture() == "g6h4");
    return true;
}

bool CTestMoveList::test_move_lookup() {
    std::string position = "k/2P4R/K w";
    SILENT_EXPECT(board.set_fen_position(position));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    EXPECT(move_generator.move_list.lookup_move("g1f3") == NULL_MOVE);
    SMove stupid_king_move = { A6, A5, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    std::cerr << move_generator.move_list.as_text() << "\n";
    EXPECT(move_generator.move_list.lookup_move("a6a5") != NULL_MOVE);
    EXPECT(move_generator.move_list.lookup_move("a6a5") == stupid_king_move);
    SMove queen_promotion = { C7, C8, WHITE_QUEEN, EMPTY_SQUARE, 0 };
    EXPECT(move_generator.move_list.lookup_move("c7c8Q") == queen_promotion);
    SMove rook_promotion = { C7, C8, WHITE_ROOK, EMPTY_SQUARE, 0 };
    EXPECT(move_generator.move_list.lookup_move("c7c8R").source == C7);
    EXPECT(move_generator.move_list.lookup_move("c7c8R").target == C8);
    EXPECT(move_generator.move_list.lookup_move("c7c8R").move_type == WHITE_ROOK);
    SMove looked_up_move = move_generator.move_list.lookup_move("c7c8R");
    EXPECT(looked_up_move == rook_promotion);
    EXPECT(move_generator.move_list.lookup_move("c7c8R") == rook_promotion);
    SMove rook_mate = { H7, H8, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    EXPECT(move_generator.move_list.lookup_move("h7h8") == rook_mate);
    EXPECT(move_generator.move_list.lookup_move("h7h8R") == NULL_MOVE);
    return true;
}

