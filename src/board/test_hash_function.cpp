// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_hash_function.h"
#include "board.h"
#include "../technical_functions/testing.h"

bool CTestHashFunction::test_everything() {
    BEGIN_TESTSUITE("CTestHashFunction");
    EXPECT(hash_position(START_POSITION) != 0);
    EXPECT(hash_position(START_POSITION) != hash_position("k1K w"));
    EXPECT(hash_position("k1K b") != hash_position("k1K w"));
    EXPECT(hash_position("k1K b KQ") != hash_position("k1K b kq"));
    EXPECT(hash_position("k1K b KQ c6") != hash_position("k1K b KQ e6"));
    EXPECT(hash_position("k1K b KQ c6 3") == hash_position("k1K b KQ c6 7"));
    EXPECT(hash_position("k1K b KQ c6 3 11") == hash_position("k1K b KQ c6 7 37"));
    // Testing for a broad range, few positions may fall low
    EXPECT(hash_position(START_POSITION) > 1234567);
    EXPECT(hash_position("k1k w") > 1234567);
    EXPECT(hash_position("K/1P/2P/3P/4p/5p/6p/7k w") > 1234567);
    return true;
}

size_t CTestHashFunction::hash_position(const std::string fen_position) {
   bool is_valid_position = board.set_fen_position(fen_position);
   assert(is_valid_position);
    return board.get_hash();
}

