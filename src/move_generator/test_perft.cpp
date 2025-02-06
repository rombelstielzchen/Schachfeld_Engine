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

typedef struct {
    std::string fen_position;
    std::vector<int64_t>positions_vy_depth;
} STestcase;

typedef std::vector<STestcase> VTestcaseCollection;

const VTestcaseCollection testcase_collection = {
    { "startpos", { 1, 20, 400, 8902, 197281, 4865609, 119060324 } },
    { "", { 1, 0, 0, 0, 0, 0, 0 } },
};

bool CTestPerft::test_everything() {
    BEGIN_TESTSUITE("CTestPerft");
    EXPECT(test_shallow_depth());
    return true;
}

bool CTestPerft::test_shallow_depth() {
    TEST_FUNCTION();
    constexpr unsigned int shallow_depth = 3;
    EXPECT(test_up_to_depth(shallow_depth));
    return true;
}

bool CTestPerft::test_up_to_depth(const unsigned int depth) {
    TEST_FUNCTION();
   for (unsigned int j = 0; j <= depth; ++j) {
        for (const STestcase &testcase : testcase_collection) {
            int64_t expeted_result = testcase.positions_vy_depth[j];
            if (expeted_result <= 0) {
                continue;
            }
            CTEST << "Testcase: " << testcase.fen_position << "\n";
            CTEST << "Depth: " << j << "\n";
            CTEST << "Expected: " <<expeted_result << "\n";
            int64_t true_result = perft(testcase.fen_position, j);
            SILENT_EXPECT(expeted_result == true_result);
        }
   }
   return true;
}

int64_t CTestPerft::perft( const std::string &fen_position, const unsigned int depth) {
     SILENT_EXPECT(board.set_fen_position(fen_position));
     return perft(depth);
}

int64_t CTestPerft::perft(const unsigned int depth) {
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

