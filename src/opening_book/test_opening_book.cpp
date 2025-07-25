// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_opening_book.h"
#include "master_book.h"
#include "book_data/gm_book.h"
#include "book_data/tabijas.h"
#include "../board/board.h"
#include "../board/move_maker.h"
#include "../technical_functions/testing.h"

 bool CTestOpeningBook::test_everything() {
    BEGIN_TESTSUITE("CTestOpeningBook");
    EXPECT(test_move_lookup());
    EXPECT(test_book_randomization());
     EXPECT(test_book_data(sorted_variation_collection_gm_book, "gm_book"));
     EXPECT(test_book_data(sorted_variation_collection_tabijas, "tabijas"));
    return true;
 }

 bool CTestOpeningBook::test_book_data(const TSortedVariationCollection &variation_collection, const std::string &book_name) {
    CTEST << "CTestOpeningBook::test_book_data (" << book_name << ")" << std::endl;
     EXPECT(test_formatting(variation_collection));
    EXPECT(test_sortedness(variation_collection));
    EXPECT(test_playability(variation_collection));
    return true;
 }

 bool CTestOpeningBook::test_formatting(const TSortedVariationCollection &variation_collection) {
     TEST_FUNCTION();
     for (const std::string &variation : variation_collection) {
         CTEST << "Format? " << variation << std::endl;
        // Checking for extra spaces
        SILENT_EXPECT(variation[0] != ' ');
        SILENT_EXPECT(variation.back() != ' ');
        SILENT_EXPECT(variation.find("  ") == std::string::npos);
        // Checking the length for plausibility
        size_t length_plus_one = variation.length() + 1;
        constexpr int move_plus_separator = 5;
        SILENT_EXPECT(length_plus_one % move_plus_separator == 0);
     }
    return true;
 }

 bool CTestOpeningBook::test_sortedness(const TSortedVariationCollection &variation_collection) {
     TEST_FUNCTION();
     size_t second_last = variation_collection.size() - 2;
     for (size_t j = 0; j <= second_last; ++j) {
        CTEST << "Sorted? " << variation_collection[j] << std::endl;
        SILENT_EXPECT(variation_collection[j].compare(variation_collection[j + 1]) < 0);
     }
    return true;
 }

 bool CTestOpeningBook::test_playability(const TSortedVariationCollection &variation_collection) {
     for (const std::string &variation : variation_collection) {
        if (variation[0] == 'x') {
            // Bokelmann-Gambit for deterministic testability, unplayable
            continue;
        }
        CTEST <<
     "Playable? " << variation << std::endl;
         board.set_start_position();
         SILENT_EXPECT(board.move_maker.play_variation(variation));
     }
    return true;
 }

 bool CTestOpeningBook::test_move_lookup() {
     TEST_FUNCTION();
     EXPECT(lookup_returns_null_move(NO_MOVES_FROM_STARTPOS));
    EXPECT(lookup_returns_any_move(""));
    EXPECT(lookup_returns_any_move("e2e4"));
    EXPECT(lookup_returns_any_move("e2e4 c7c5"));
    EXPECT(lookup_returns_any_move("d2d4 g8f6 c2c4 g7g6 b1c3 d7d5"));
    EXPECT(lookup_returns_null_move("g1h3 b8a6"));
    EXPECT(lookup_returns_null_move("e2e4 b8a6"));
    SILENT_EXPECT(lookup_returns_exact_move("x2x1", "e7e5"));
    SILENT_EXPECT(lookup_returns_exact_move("x2x1 e7e5", "e2e4"));
    SILENT_EXPECT(lookup_returns_exact_move("x2x1 e7e5 e2e4", "f7f5"));
    SILENT_EXPECT(lookup_returns_null_move("x2x1 e7e5 e2e4 f7f5"));
    return true;
 }

 bool CTestOpeningBook::lookup_returns_null_move(std::string variation) {
    return (verbose_move_lookup(variation) == NULL_MOVE_AS_TEXT);
 }

 bool CTestOpeningBook::lookup_returns_any_move(std::string variation) {
    return (lookup_returns_null_move(variation) == false);
 }

bool CTestOpeningBook::lookup_returns_exact_move(const std::string &variation, const std::string &text_move) {
    return (verbose_move_lookup(variation) == text_move);
}

std::string CTestOpeningBook::verbose_move_lookup(const std::string &variation) {
    CMasterBook master_book;
    std::string move = master_book.get_move(variation);
    assert(move.length() == length_of_text_move);
    assert((move == NULL_MOVE_AS_TEXT)  || (move_in_range(text_to_basic_move(move))));
    CTEST << "[" << variation << "] -> [" << move << "]" << std::endl;
    return move; 
}

bool CTestOpeningBook::test_book_randomization() {
    // Former problem with MiSoViStu: book always playing the same line,
    // despite working fine with gcc on Linux
    TEST_FUNCTION();
    EXPECT(rand() != rand());
    bool master_book_randomization_seen = false;
   const std::string moves_from_startpos = "e2e4"; 
   std::string first_lookup =verbose_move_lookup(moves_from_startpos);
    for (int j = 0; j < 50; ++j) {
            std::string another_try = verbose_move_lookup(moves_from_startpos);
        if (another_try != first_lookup) {
            master_book_randomization_seen = true;
            break;
        }
    }
    EXPECT(master_book_randomization_seen);
    return true;
}

