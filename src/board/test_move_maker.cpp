// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_maker.h"
#include "board.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/testing.h"
#include "../technical_functions/standard_headers.h"

bool CTestMoveMaker::test_everything() {
    BEGIN_TESTSUITE("CTestMoveMaker");
    EXPECT(test_make_unmake_combinations());
    EXPECT(test_algebraic_game());
    return true;
}

bool CTestMoveMaker::test_make_unmake_combinations() {
    const std::string all_in_one_position = "r3k2r/p6R/1p6/8/5pPp/8/1p3P2/N1Nb2qn b kq g3 0 1";
    board.set_fen_position(all_in_one_position);
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.move_list.list_size();
    CTEST << n_moves << " to est" << std::endl;
   for (int j = 0; j < n_moves; ++j) {
        SMove move = move_generator.move_list.get_random();
        CTEST << "Make / unmake " << move_as_text(move) << "...\n";
        // TODO: get_next
        board.move_maker.make_move(move);
        board.move_maker.unmake_move();
        SILENT_EXPECT(board.get_fen_position() == all_in_one_position);
   }
    return true;
}

bool CTestMoveMaker::test_algebraic_game() {
    // TODO
    return true;
}

