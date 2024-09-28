// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_opening_book.h"
#include "opening_book.h"
#include "book_data/gm_book.h"

 bool CTestOpeningBook::test_everything() {
     std::cerr << "CTestOpeningBook::test_everything() ..." << std::endl;
     bool result = test_book_data(gm_book, "gm_book")
        && test_move_lookup();
    return result;
 }

 bool CTestOpeningBook::test_book_data(const TSortedVariationCollection &variation_collection, const std::string &book_name) {
    std::cerr << "CTestOpeningBook::test_book_data [" << book_name << "]" << std::endl;
     bool result = test_formatting(variation_collection)
        && test_sortedness(variation_collection)
        && test_playability(variation_collection);
    return result;
 }

 bool CTestOpeningBook::test_formatting(const TSortedVariationCollection &variation_collection) {
     std::cerr << "CTestOpeningBook::test_formatting() ..." << std::endl;
     bool result = true;
     for (const std::string &variation : variation_collection) {
        // Checking for extra spaces
        result &= (variation[0] != ' ')
        && (variation.back() != ' ')
        && (variation.find("  ") >= 0);
        // Checking the length for plausibility
        int length_plus_one = variation.length() + 1;
        constexpr int move_plus_separator = 5;
        result &= (length_plus_one % move_plus_separator == 0);
        if (!result) {
            std::cerr << "ERROR: Malformed variation: " << variation << std::endl;
            break;
        }
     }
    return result;
 }

 bool CTestOpeningBook::test_sortedness(const TSortedVariationCollection &variation_collection) {
    std::cerr << "CTestOpeningBook::test_sortedness() ..." << std::endl;
     int second_last = variation_collection.size() - 2;
     for (int i = 0; i <= second_last; ++i) {
        if (variation_collection[i].compare(variation_collection[i + 1]) >= 0) {
            std::cerr << "ERROR: bad sorting: " << variation_collection[i] << std::endl;
            break;
        }
     }
    return true;
 }

 bool CTestOpeningBook::test_playability(const TSortedVariationCollection &variation_collection) {
     // TODO
    return true;
 }

 bool CTestOpeningBook::test_move_lookup() {
     std::cerr << "CTestOpeningBook::test_move_lookup() ..." << std::endl;
     bool result = lookup_returns_any_move("")
        && lookup_returns_any_move("e2e4")
        && lookup_returns_any_move("e2e4 c7c5")
        && lookup_returns_any_move("d2d4 g8f6 c2c4 g7g6 b1c3 d7d5")
        && lookup_returns_null_move("g1h3 b8a6")
        && lookup_returns_null_move("e2e4 b8a6")
        && lookup_returns_exact_move("x2x1", "e7e5")
        && lookup_returns_exact_move("x2x1 e7e5", "e2e4")
        && lookup_returns_exact_move("x2x1 e7e5 e2e4", "f7f5");
    return result;
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
    COpeningBook opening_book;
    std::string move = opening_book.get_move(variation);
    std::cerr << "[" << variation << "] -> [" << move << "]" << std::endl;
    return move; 
}

