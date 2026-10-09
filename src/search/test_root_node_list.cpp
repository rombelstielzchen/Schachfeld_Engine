// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_root_node_list.h"
#include "root_node_list.h"
#include "../technical_functions/testing.h"
#include "../board/board.h"

bool CTestRootNodeList::test_everything() {
    BEGIN_TESTSUITE("CTestRootNodeList");
    EXPECT(test_empty_list());
    EXPECT(test_generate_moves());
    EXPECT(test_reuse_list());
    EXPECT(test_only_one_legal_move());
    EXPECT(test_remove());
    EXPECT(test_shift_current_move_to_top());
    EXPECT(test_move_on_list());
    return true;
}

bool CTestRootNodeList::test_empty_list() {
    TEST_FUNCTION();
    CRootNodeList root_node_list;
    EXPECT(root_node_list.list_size() == 0);
    EXPECT(root_node_list.get_next() == NULL_MOVE);
    return true;
}

bool CTestRootNodeList::test_generate_moves() {
    TEST_FUNCTION();
    board.set_start_position();
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    EXPECT(root_node_list.list_size() == 20);
    SMove first = root_node_list.get_next();
    EXPECT(move_in_range(first));
    EXPECT(first.source.rank <= RANK_2);
    SMove second = root_node_list.get_next();
    EXPECT(move_in_range(second));
    EXPECT(first != second);
    std::string no_legal_moves = "k/2QK b";
    EXPECT(board.set_fen_position(no_legal_moves));
    root_node_list.generate_moves();
    EXPECT(root_node_list.list_size() == 0);
    const std::string another_position = "R4rk/////6P/5PKP/ w";
    EXPECT(board.set_fen_position(another_position));
   root_node_list.generate_moves();
    EXPECT(root_node_list.list_size() == 21);
    for (size_t j = 0; j < root_node_list.list_size(); ++j) {
        EXPECT(move_in_range(root_node_list.get_next()));
    }
    EXPECT(root_node_list.get_next() == NULL_MOVE);
    return true;
}

bool CTestRootNodeList::test_reuse_list() {
    TEST_FUNCTION();
    board.set_start_position();
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    size_t original_size = root_node_list.list_size();
    SMove first = root_node_list.get_next();
    SMove second = root_node_list.get_next();
    SMove third = root_node_list.get_next();
    root_node_list.reuse_list();
    EXPECT(root_node_list.list_size() == original_size);
    EXPECT(root_node_list.get_next() == first);
    EXPECT(root_node_list.get_next() == second);
    EXPECT(root_node_list.get_next() == third);
    return true;
}

bool CTestRootNodeList::test_only_one_legal_move() {
    TEST_FUNCTION();
    board.set_start_position();
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    EXPECT(root_node_list.only_one_legal_move() == false);
    const std::string nearly_mate = "1k/3Q/1K b";
    EXPECT(board.set_fen_position(nearly_mate));
    root_node_list.generate_moves();
    EXPECT(root_node_list.only_one_legal_move());
    EXPECT(root_node_list.only_move() == "b8a8");
    return true;
}

bool CTestRootNodeList::test_remove() {
    TEST_FUNCTION();
    board.set_start_position();
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    EXPECT(root_node_list.list_size() == 20);
    SMove former_last_move = root_node_list.back().move;
    SMove former_move_6 = root_node_list.data[6].move;
    SMove former_move_8 = root_node_list.data[8].move;
    root_node_list.remove(7);
    EXPECT(root_node_list.list_size() == 19);
    EXPECT(root_node_list.back().move == former_last_move);
    EXPECT(root_node_list.data[6].move == former_move_6);
    EXPECT(root_node_list.data[7].move == former_move_8);
    return true;
}

bool CTestRootNodeList::test_shift_current_move_to_top() {
    TEST_FUNCTION();
    board.set_start_position();
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    SMove former_first_move = root_node_list.get_next();
    SMove former_second_move = root_node_list.get_next();
    SMove former_third_move = root_node_list.get_next();
    SMove former_fourth_move = root_node_list.data[3].move;
    root_node_list.shift_current_move_to_top();
    EXPECT(root_node_list.data[0].move == former_third_move);
    EXPECT(root_node_list.data[1].move == former_first_move);
    EXPECT(root_node_list.data[2].move == former_second_move);
    EXPECT(root_node_list.data[3].move == former_fourth_move);
    return true;
}

bool CTestRootNodeList::test_move_on_list() {
    TEST_FUNCTION();
    EXPECT(board.set_fen_position("startpos moves e2e4 b7b5"));
    CRootNodeList root_node_list;
    root_node_list.generate_moves();
    SMove d2d4 = { D2, D4, MOVE_TYPE_DOUBLE_JUMP, EMPTY_SQUARE, 0 };
    EXPECT(root_node_list.move_on_list(d2d4));
    SMove f1xb5 = { F1, B5, MOVE_TYPE_CAPTURE, BLACK_POWER, 3141 };
    EXPECT(root_node_list.move_on_list(f1xb5));
    SMove f1xa6 = { F1, A6, MOVE_TYPE_NORMAL, EMPTY_SQUARE, 0 };
    EXPECT(root_node_list.move_on_list(f1xa6) == false);
    return true;
}

