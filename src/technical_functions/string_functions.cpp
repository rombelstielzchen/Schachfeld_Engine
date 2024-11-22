// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "string_functions.h"
#include "standard_headers.h"

void replace_tabs_by_spaces(std::string &in_out_string) {
    std::replace(in_out_string.begin(), in_out_string.end(), '\t', ' ');
}

void trim_left(std::string &in_out_string) {
    // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    in_out_string.erase(in_out_string.begin(), std::find_if(in_out_string.begin(), in_out_string.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void trim_right(std::string &in_out_string) {
    // https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
    in_out_string.erase(std::find_if(in_out_string.rbegin(), in_out_string.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), in_out_string.end());
}
    
void trim(std::string &in_out_string) {
    trim_right(in_out_string);
    trim_left(in_out_string);
}

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
    DEBUG_METHOD();
    size_t pattern_size = pattern.length();
    if (long_string.find(pattern) != 0) {
        return false;
    }
    if (true_prefix && (pattern_size == long_string.length())) {
        return false;
    }
    return true;
}

