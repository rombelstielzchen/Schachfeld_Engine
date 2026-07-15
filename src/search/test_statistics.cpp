// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_statistics.h"
#include "hash_table.h"
#include "search_statistics.h"
#include "iterative_deepening.h"
#include "../board/board.h"
#include "../move_generator/move_generator.h"
#include "../technical_functions/testing.h"
#include "../universal_chess_interface/command_interface.h"

bool CTestStatistics::test_everything() {
    BEGIN_TESTSUITE("CTestStatistics");
    EXPECT(test_basic_stats());
    EXPECT(test_anti_adjudication_score());
    EXPECT(test_expected_branching_factor());
    EXPECT(test_principal_variation());
    search_statistics.reset_all();
    return true;
}

bool CTestStatistics::test_basic_stats() {
   TEST_FUNCTION(); 
    EXPECT(CSearchStatistics::anti_adjudication_score(600) == " score cp 599 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(598) == " score cp 598 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(12) == " score cp 12 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(3) == " score cp 7 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-600) == " score cp -599 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-598) == " score cp -598 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-12) == " score cp -12 ");
    EXPECT(CSearchStatistics::anti_adjudication_score(-3) == " score cp 7 ");
    return true;
}

bool CTestStatistics::test_anti_adjudication_score() {
   TEST_FUNCTION(); 
    return true;
}

bool CTestStatistics:: test_expected_branching_factor() {
   TEST_FUNCTION(); 
    return true;
 }

bool CTestStatistics::test_principal_variation() {
    TEST_FUNCTION();
    // TODO: make this test work. ATM the statistic requires its own threaded board,
    // does not work single-threaded
    return true;
    SILENT_EXPECT(board.set_fen_position("4r1k/5pb/5qQ/////1B4KR w"));
    DOBB_DOBB_DOBB_the_gui_wants_us_to_stop_stop_stop = false;
    hash_table.set_size(500); /// R!
    CIterativeDeepening searcher;
    SMove best_move = searcher.search_depth(4);
    EXPECT(best_move == "h1h8");
    std::cerr << search_statistics.principal_variation() << "\n";
    EXPECT(search_statistics.principal_variation() == "h1h8 g8h8 g6h7 h8h7 b1h7");
    return false;
}

