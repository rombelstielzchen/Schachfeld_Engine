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
    return true;
}

bool CTestMoveList::test_prune_silent_moves() {
    CTEST << "CTestMoveList::test_prune_silent_moves() ..." << std::endl;
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

bool CTestMoveList::test_filter_by_target_square() {
    CTEST << "CTestMoveList::test_filter_by_target_square() ...\n";
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
    CTEST << "Least_valuanle_aggressot: " << move << "\n";
    EXPECT((move == "c6d5") || (move == "e6d5"));
    return true;
}

bool CTestMoveList::test_reuse_list() {
    CTEST << "CMoveList::test_reuse_list\n() ...";
    // TODO: new test-case
///    assert(testcases.size() > 42);
///    SILENT_EXPECT(board.set_fen_position(testcases[42].fen_position));
///    CMoveGenerator move_generator;
///    move_generator.generate_all();
///    SMove first_move = move_generator.move_list.get_next();
///    move_generator.move_list.reuse_list();
//    SMove first_move_again = move_generator.move_list.get_next();
///    EXPECT(first_move == first_move_again);
    return true;
}
bool CTestMoveList::test_shift_current_move_to_top() {
    CTEST << "CTestMoveList::test_shift_current_move_to_top() ...\n";
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
    CTEST << "CTestMoveList::test_remove() ...\n";
    std::string nearly_stalemaze = "1k/3Q b";
    SILENT_EXPECT(board.set_fen_position(nearly_stalemaze));
    CMoveGenerator move_generator;
    move_generator.generate_all();
    SILENT_EXPECT(move_generator.move_list.list_size() == 5);
   constexpr SMove illegal_moveF = {{FILE_B, RANK_8}, C8, MOVE_TYPE_NORMAL};
   move_generator.move_list.remove(illegal_moveF);
    EXPECT(move_generator.move_list.list_size() == 4);
    move_generator.move_list.filter_captures_by_target_square(C8);
    EXPECT(move_generator.move_list.list_size() == 0);
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
