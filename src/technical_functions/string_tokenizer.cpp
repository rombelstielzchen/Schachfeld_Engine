// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "string_tokenizer.h"

CStringTokenizer::CStringTokenizer(const std::string &input) {
     set_input(input);
}

void CStringTokenizer::set_input(const std::string &input) {
    input_stream.clear();
    input_stream.str(input);
}
 
std::string CStringTokenizer::next_token() {
    std::string result;
    result.clear();
    input_stream >> std::skipws >> result;
    return result;
}

int CStringTokenizer::get_integer_token(int minimum_and_default) {
    int result = 0;
    try {
        result = stoi(next_token());
    }
    catch (...) {
        return minimum_and_default;
    }
    result = std::max(result, minimum_and_default);
    return result;
}

std::string CStringTokenizer::get_the_rest() {
    std::string result = "";
    std::string next = next_token();
    while (next != "") {
        result += next;
        result += " ";
        next = next_token();
    }
    return result;
}

bool is_prefix_of(const std::string &pattern, const std::string &long_string, bool true_prefix) {
    size_t pattern_size = pattern.length();
    if (long_string.find(pattern) != 0) {
        return false;
    }
    if (true_prefix && (pattern_size == long_string.length())) {
        return false;
    }
    return true;
}
 
bool CStringTokenizer::next_token_is(const std::string &token) {
    return false;
}

bool CStringTokenizer::next_token_is_one_of(const std::string &token1, const std::string &token2) {
    return false;
}

bool CStringTokenizer::next_token_is_one_of(const std::string &token1, const std::string &token2, const std::string &token3) {
    return false;
}

void CStringTokenizer::push_nack(const std::string &token) {
    assert(pushed_back_token == "");
    pushed_back_token = token;
}

