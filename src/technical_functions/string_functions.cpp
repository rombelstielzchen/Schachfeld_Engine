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

size_t find_substring(const std::string &text, const std::string substring, bool case_insensitive) {
    // TODO: insensitive + test
    return text.find(substring);
}

size_t replace_substring(std::string &source, const std::string &substring, const std::string &by_what, bool case_insensitive) {
    size_t pos = find_substring(source, substring);
    if (pos != std::string::npos) {
        source.replace(pos, substring.length(), by_what);
    }
    return pos;
}

void replace_all_substrings(std::string &source, const std::string &substring, const std::string &by_what, bool case_insensitive) {
    if ((substring == "") || (substring == by_what)) {
        return;
    }
    // TODO: replace naive implementation, searching N times from the beginning
    size_t pos = 0;
    while (pos != std::string::npos) {
        pos = replace_substring(source, substring, by_what, case_insensitive);
    }
}

void remove_all_substrings(std::string &source, const std::string &substring, bool case_insensitive) {
    replace_all_substrings(source, substring, "", case_insensitive);
}

