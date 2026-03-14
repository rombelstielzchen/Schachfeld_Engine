// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_hash_table.h"
#include "hash_table.h"
#include "../board/square_constants.h"
#include "../technical_functions/testing.h"

bool CTestHashTable::test_everything() {
    BEGIN_TESTSUITE("CTestHashTable");
    EXPECT(test_sizes());
    EXPECT(test_resizing());
    EXPECT(test_lookup());
    EXPECT(test_lookup_after_resizing());
    return true;
}

bool CTestHashTable::test_sizes() {
    TEST_FUNCTION();
    EXPECT(hash_table.n_possible_entries(100) > 1);
    EXPECT(hash_table.n_possible_entries(100) <= 12);
    EXPECT(hash_table.n_current_entries() > 10000);
    return true;
}

bool CTestHashTable::test_resizing() {
    TEST_FUNCTION();
    size_t n_entrie = hash_table.n_current_entries();
    hash_table.set_size(2);
    EXPECT(hash_table.n_current_entries() > n_entrie);
    hash_table.set_size(1);
    EXPECT(hash_table.n_current_entries() == n_entrie);
    return true;
}

bool CTestHashTable::test_lookup() {
    TEST_FUNCTION();
    constexpr  SMove g1f3 = { G1, F3, MOVE_TYPE_NORMAL, '\0', 0 };
    constexpr int64_t index = 3141;
    EXPECT(hash_table.get_best_move(index) != g1f3);
    hash_table.store_best_move(index, g1f3);
    EXPECT(hash_table.get_best_move(index) == g1f3);
    return true;
}

bool CTestHashTable::test_lookup_after_resizing() {
    TEST_FUNCTION();
    constexpr  SMove g1h3 = { G1, H3, MOVE_TYPE_NORMAL, '\0', 0 };
    constexpr int64_t index1 = 3141;
    constexpr int64_t index2 = 3141592653;
    EXPECT(hash_table.get_best_move(index1) != g1h3);
    EXPECT(hash_table.get_best_move(index2) != g1h3);
    hash_table.store_best_move(index1, g1h3);
    hash_table.store_best_move(index2, g1h3);
    EXPECT(hash_table.get_best_move(index1) == g1h3);
    EXPECT(hash_table.get_best_move(index2) == g1h3);
    hash_table.set_size(2);
    // Small keys go to the same index, large keys to a different one after resizing
    EXPECT(hash_table.get_best_move(index1) == g1h3);
    EXPECT(hash_table.get_best_move(index2) != g1h3);
    return true;
}

