// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_technical_functions.h"
#include "standard_headers.h"
#include "string_functions.h"

/* static */ bool CTestTechnicalFunctions::test_everything() {
    // Tests "everything"m except debug_log and engine_test
        std::cerr << "CTestTechnicalFunctions::test_everything() ..." << std::endl;
    bool result = test_string_functions();
    if (result) {
        std::cerr << "CTestTechnicalFunctions:test_everything(): success" << std::endl;
    } else {
        std::cerr << "CTestTechnicalFunctions::test_everything(): failed" << std::endl;
    }
    return result;
}

/* static */ bool CTestTechnicalFunctions::test_string_functions() {
    std::cerr << "CTestTechnicalFunctions::test_string_functions() ..." << std::endl;
    std::string initial = "\t \t\t \tHello   ,   \t\t\t   world !   \t\t";
    std::cerr << "Testing replace_tabs_by_spaces()" << std::endl;
    replace_tabs_by_spaces(initial);
    if (initial != "      Hello   ,         world !     ") {
        return false;
    }
    std::cerr << "Testing trim()" << std::endl;
    trim(initial);
    if (initial != "Hello   ,         world !") {
        return false;
    }
    std::cerr << "Testing CStringTokenizer" << std::endl;
    std::string long_text = "hello world greetings from the moon";
    CStringTokenizer tokenizer(long_text);
    if (tokenizer.next_token() != "hello") {
        return false;
    }
    if (tokenizer.next_token() != "world") {
        return false;
    }
    // Extra space at the end, as "the rest" gets re-constructed from tokens
    if (tokenizer.get_the_rest() != "greetings from the moon ") {
        return false;
    }
    return true;
}

