// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_move_maker.h"
#include "board.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/standard_headers.h"

bool CTestMoveMaker::test_everything() {
    std::cerr << "CTestMoveMaker::test_everything() ..."<< std::endl;
    bool result = test_make_unmake_combinations()
        && test_algebraic_game();
    if (result) {
        std::cerr << "CTestMoveMaker::test_everything() successful" << std::endl;
    } else {
        std::cerr << "ERROR: CTestMoveMaker::test_everything() failed" << std::endl;
    }
    return result;

}

bool CTestMoveMaker::test_make_unmake_combinations() {
    const std::string all_in_one_position = "r3k2r/p6R/1p6/8/5pPp/8/1p3P2/N1Nb2qn b kq g4";
    board.set_fen_position(all_in_one_position);
    CMoveGenerator move_generator;
    move_generator.generate_all();
    int n_moves = move_generator.list_size();
    std::cerr << n_moves << " to est" << std::endl;
   for (int j = 0; j < n_moves; ++j) {
        SMove move = move_generator.get_random();
        // TODO: get_next
        std::cerr << "Testing move: " << move_as_text(move) << std::endl;
        board.move_maker.make_move(move);
        board.move_maker.unmake_move();
        if (board.get_fen_position() != all_in_one_position) {
            std::cerr << "Failed\n";
            return false;
        }
   }
    return true;
}

bool CTestMoveMaker::test_algebraic_game() {
    // TODO
    return true;
}

