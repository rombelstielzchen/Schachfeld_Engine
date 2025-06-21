// Project: Schachfeld_Engine
// Author: Rombelstielzchen
//
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "data_book.h"
#include "../technical_functions/string_functions.h"

constexpr size_t VARIATION_NOT_FOUND = std::string::npos;

CDataBook::CDataBook(const TSortedVariationCollection &sorted_variation_collection) : sorted_variation_collection(sorted_variation_collection) {
    last_looked_up_moves_from_startpos = "";
    last_lookup_successful = true;
}

std::string CDataBook::get_move(const std::string &moves_from_startpos_in_uci_format) {
    size_t index = random_matching_index(sorted_variation_collection, moves_from_startpos_in_uci_format);
    if (index == VARIATION_NOT_FOUND) {
        last_lookup_successful = false;
        return NULL_MOVE_AS_TEXT;
    }
   assert(sorted_variation_collection[index].length() > moves_from_startpos_in_uci_format.length());
   size_t first_char = 0;
   if (moves_from_startpos_in_uci_format != "") {
       first_char = moves_from_startpos_in_uci_format.length() + 1;
   }
   std::string next_move = sorted_variation_collection[index].substr(first_char, length_of_text_move);
   const std::string bokelmann_gambit_for_testability = "x2x1";
   if (next_move == bokelmann_gambit_for_testability) {
        return "e2e4";
   }
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
    size_t last_element = book.size() - 1;
    for (int j = last_element; j >= 0; --j) {
         if (is_prefix_of(moves_from_startpos_in_uci_format, book[j], true)) {
            return j;
         }
    }
    return VARIATION_NOT_FOUND;
}

size_t CDataBook::random_matching_index(const TSortedVariationCollection &book, const std::string &moves_from_startpos_in_uci_format) const {
    size_t first_index = first_matching_index(book, moves_from_startpos_in_uci_format);
    if (first_index == VARIATION_NOT_FOUND) {
        return VARIATION_NOT_FOUND;
    }
    size_t last_index = last_matching_index(book, moves_from_startpos_in_uci_format);
    assert(last_index != VARIATION_NOT_FOUND);
    assert(last_index >= first_index);
    // rand() would be good ebough, Undortunately it did not work with Gcc,
    // (only with Visual Studio) despite prorper srand(time(NULL)),
    // always returning 41 (rhe 42th positive number!).
    // So we go for an overkill random-number-generatir.
    std::random_device random_seed;
    std::mt19937 mersenne_twister(random_seed());
    std::uniform_int_distribution<> int_distribution(first_index, last_index);
    size_t random_index = int_distribution(mersenne_twister);
    assert(random_index >= first_index);
    assert(random_index <= last_index);
    return random_index;
}

