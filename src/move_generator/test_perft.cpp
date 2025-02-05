// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_perft.h"
#include "../board/board.h"
#include "../technical_functions/testing.h"

bool CTestPerft::test_everything() {
    BEGIN_TESTSUITE("CTestPerft");
    EXPECT(test_basic());
    return true;
}

bool CTestPerft::test_basic() {
    TEST_FUNCTION();
    board.set_start_position();
    EXPECT(perft(2) == 400);
    return true;
}

int64_t CTestPerft::perft(const int depth) {
    return 11;
}

int64_t CTestPerft::perft(const int depth, const std::string fen_position) {
    SILENT_EXPECT(board.set_fen_position(fen_position));
    return perft(depth);
}

