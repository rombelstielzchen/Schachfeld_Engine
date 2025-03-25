// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_technical_functions.h"
#include "testing.h"
#include "standard_headers.h"
#include "string_functions.h"
#include "string_tokenizer.h"

/* static */ bool CTestTechnicalFunctions::test_everything() {
    // Tests "everything"m except debug_log and engine_test
        BEGIN_TESTSUITE("CTestTechnicalFunctions");
    EXPECT(test_string_functions());
    EXPECT(test_string_tokenizer());
    return true;
}

/* static */ bool CTestTechnicalFunctions::test_string_functions() {
        TEST_FUNCTION();
    std::string initial = "\t \t\t \tHello   ,   \t\t\t   world !   \t\t";
    CTEST << "Testing replace_tabs_by_spaces()" << std::endl;
    replace_tabs_by_spaces(initial);
    EXPECT(initial == "      Hello   ,         world !     ");
    CTEST << "Testing trim()" << std::endl;
    trim(initial);
    EXPECT(initial == "Hello   ,         world !");
    // is_prefix_of
    EXPECT(is_prefix_of("bob","bobby") == true);
    EXPECT(is_prefix_of("bobby","bobby") == true);
    EXPECT(is_prefix_of("bobby","bobby", true) == false);
    EXPECT(is_prefix_of("bobby","tolya") == false);
    // replace and remove
    initial = "Hello, world!";
    EXPECT(replace_substring(initial, "ello", "uhu", true) == 1);
    EXPECT(initial == "Huhu, world!");
    replace_all_substrings(initial, "u", "o", true);
    EXPECT(initial == "Hoho, world!");
    remove_all_substrings(initial, ", world");
    EXPECT(initial == "Hoho!");
    return true;
}

bool CTestTechnicalFunctions::test_string_tokenizer() {
    TEST_FUNCTION();
    std::string long_text = "hello world greetings from the moon";
    CStringTokenizer tokenizer(long_text);
    EXPECT(tokenizer.next_token() == "hello");
    EXPECT(tokenizer.next_token() == "world");
    tokenizer.push_back("moon");
    EXPECT(tokenizer.next_token() == "moon");
    // Extra space at the end, as "the rest" gets re-constructed from tokens
    EXPECT(tokenizer.get_the_rest() == "greetings from the moon ");
    tokenizer.set_input("34  asdf -5");
    EXPECT(tokenizer.get_integer_token(0) == 34);
    EXPECT(tokenizer.get_integer_token(3) == 3);
    EXPECT(tokenizer.get_integer_token(-2) == -2);
    tokenizer.set_input("a omega");
    EXPECT(tokenizer.next_token_is_one_of("b", "c", "d") == false);
    EXPECT(tokenizer.next_token_is("a"));
    EXPECT(tokenizer.next_token_is("omega"));
    return true;
}

