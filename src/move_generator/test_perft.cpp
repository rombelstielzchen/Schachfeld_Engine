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
    // Working
//   { "startpos", { 1, 20, 400, 8902, 197281, 4865609, 119060324 }},
     // Failed
//    { "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ", { 1, 48, 2039, 97862, 4085603, 193690690, 8031647685 }},
    // Working
//+    { "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ", { 1, 14, 191, 2812,  43238, 674624, 11030083 }},
    // Failed
//    { "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", { 1, 6, 264, 9467, 422333, 15833292, 706045033 }},
    // Failed
//    { "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8  ", { 1, 44, 1486, 62379, 2103487, 89941194, 0 }},
    { "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10 ", { 1, 46, 2079, 89890, 3894594, 164075551, 6923051137 }},
};

bool CTestPerft::test_everything() {
    BEGIN_TESTSUITE("CTestPerft");
    EXPECT(test_shallow_depth());
    return true;
}

bool CTestPerft::test_shallow_depth() {
    TEST_FUNCTION();
    constexpr unsigned int shallow_depth =6 ;
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
            constexpr bool display_move_statistics = true;
            int64_t true_result = perft(testcase.fen_position, j, display_move_statistics);
            CTEST << "Result: " << true_result << "\n";
            SILENT_EXPECT(expeted_result == true_result);
        }
   }
   return true;
}

int64_t CTestPerft::perft(const std::string &fen_position, const unsigned int depth,bool display_moves) {
     SILENT_EXPECT(board.set_fen_position(fen_position));
     return perft(depth, display_moves);
}

int64_t CTestPerft::perft(const unsigned int depth, bool display_moves) {
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
        int64_t new_nodes = perft(depth - 1);
        nodes_enumearated += new_nodes;
        board.move_maker.unmake_move();
        if (display_moves) {
            CTEST << move << ": " << new_nodes << "\n";
        }
    }
    return nodes_enumearated;
}

