// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "data_book.h"
#include "../technical_functions/string_functions.h"

constexpr size_t VARIATION_NOT_FOUND = std::string::npos;

CDataBook::CDataBook(const TSortedVariationCollection &sorted_variation_collection) : sorted_variation_collection(sorted_variation_collection) {
    assert(sorted_variation_collection.size() <= INT_MAX);
    assert(sorted_variation_collection.size() >= minimum_book_size_for_lookups_and_test_of_sortedness);
    last_looked_up_moves_from_startpos = "";
    last_lookup_successful = true;
}

std::string CDataBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    // moves_from_startpos_in_uci_format usually ends with a space;
    // The space might be missing in case of test-cases and human input
    constexpr int length_of_text_move_plus_space = length_of_text_move + 1;
    assert((moves_from_startpos_in_uci_format.length() % length_of_text_move_plus_space == 0) || (moves_from_startpos_in_uci_format.length() % length_of_text_move_plus_space == length_of_text_move));
     assert(((moves_from_startpos_in_uci_format.length() == 0) || moves_from_startpos_in_uci_format.back() == ' ') || isdigit(moves_from_startpos_in_uci_format.back()));
    size_t index = random_matching_index(sorted_variation_collection, moves_from_startpos_in_uci_format);
    if (index == VARIATION_NOT_FOUND) {
        last_lookup_successful = false;
        return NULL_MOVE_AS_TEXT;
    }
   assert(sorted_variation_collection[index].length() > moves_from_startpos_in_uci_format.length());
    size_t first_char_pos = moves_from_startpos_in_uci_format.length();
    if (isdigit(moves_from_startpos_in_uci_format.back())) {
        ++first_char_pos;
    }
    assert(first_char_pos % length_of_text_move_plus_space == 0);
   std::string next_move = sorted_variation_collection[index].substr(first_char_pos, length_of_text_move);
   assert(isalpha(next_move[0]));
   assert(isdigit(next_move.back()));
   const std::string bokelmann_gambit_for_testability = "x2x1";
   if (next_move == bokelmann_gambit_for_testability) {
        return "e2e4";
   }
   assert(move_in_range(text_to_basic_move(next_move)));
    return next_move;
}

size_t CDataBook::first_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    size_t size = book.size(); 
    for (size_t j = 0; j < size; ++j) {
         if (is_prefix_of(moves_from_startpos_in_uci_format, book[j], true)) {
            return j;
        }
    }
    return VARIATION_NOT_FOUND;
}

size_t CDataBook::last_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    assert(book.size() >= 1);
    size_t last_element_size_t = book.size() - 1;
    assert(last_element_size_t <= INT_MAX);
    int last_element = static_cast<int>(last_element_size_t);
    for (int j = last_element; j >= 0; --j) {
         if (is_prefix_of(moves_from_startpos_in_uci_format, book[j], true)) {
            return j;
         }
    }
    return VARIATION_NOT_FOUND;
}

size_t CDataBook::random_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    size_t st_first_index = first_matching_index(book, moves_from_startpos_in_uci_format);
    if (st_first_index == VARIATION_NOT_FOUND) {
        return VARIATION_NOT_FOUND;
    }
    size_t st_last_index = last_matching_index(book, moves_from_startpos_in_uci_format);
    assert(st_last_index != VARIATION_NOT_FOUND);
    assert(st_last_index >= st_first_index);
    assert(st_last_index < book.size());
    assert(st_last_index <= INT_MAX);
    int first_index = static_cast<int>(st_first_index);
    int last_index = static_cast<int>(st_last_index);
    // rand() would be good enough, Unfortunately it did not work with Gcc,
    // (only with Visual Studio) despite prorper srand(time(NULL)),
    // always returning 41 (rhe 42th positive number!).
    // So we go for an overkill random-number-generator.
    std::random_device random_seed;
    std::mt19937 mersenne_twister(random_seed());
    std::uniform_int_distribution<> int_distribution(first_index, last_index);
    int random_index = int_distribution(mersenne_twister);
    assert(random_index >= first_index);
    assert(random_index <= last_index);
    return random_index;
}

