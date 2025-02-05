// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Testing the move_generator.
// Going fixed depth, counting positions.
// https://www.chessprogramming.org/Perft
// https://www.chessprogramming.org/Perft_Results

#include "test_perft.h"
#include "../board/board.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/testing.h"

bool CTestPerft::test_everything() {
    BEGIN_TESTSUITE("CTestPerft");
    EXPECT(test_basic());
    return true;
}

bool CTestPerft::test_basic() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(perft(1) == 20);
    EXPECT(perft(2) == 400);
    EXPECT(perft(3) == 8902);
    EXPECT(perft(4) == 197281);
    EXPECT(perft(5) == 4865609);
    EXPECT(perft(6) == 119060324);
    return true;
}

int64_t CTestPerft::perft(const int depth) {
    assert(depth >= 1);
    CMoveGenerator move_generator;
    move_generator.generate_all();
    move_generator.move_list.prune_illegal_moves();
    int n_moves = move_generator.move_list.list_size();
    if (depth == 1) {
        return n_moves;
    } else if (depth <= 0) {
        return 1;
    }
    int64_t nodes_enumearated = 0;
    for (int j = 0; j < n_moves; ++j) {
        SMove move = move_generator.move_list.get_next();
        assert(move_in_range(move));
        board.move_maker.make_move(move);
        nodes_enumearated += perft(depth - 1);
        board.move_maker.unmake_move();
    }
    return nodes_enumearated;
}

int64_t CTestPerft::perft(const int depth, const std::string fen_position) {
    SILENT_EXPECT(board.set_fen_position(fen_position));
    return perft(depth);
}

