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
    return true;
}

/* static */ bool CTestTechnicalFunctions::test_string_functions() {
    CTEST << "CTestTechnicalFunctions::test_string_functions() ..." << std::endl;
    std::string initial = "\t \t\t \tHello   ,   \t\t\t   world !   \t\t";
    CTEST << "Testing replace_tabs_by_spaces()" << std::endl;
    replace_tabs_by_spaces(initial);
    EXPECT(initial == "      Hello   ,         world !     ");
    CTEST << "Testing trim()" << std::endl;
    trim(initial);
    EXPECT(initial == "Hello   ,         world !");
    CTEST << "Testing CStringTokenizer" << std::endl;
    std::string long_text = "hello world greetings from the moon";
    CStringTokenizer tokenizer(long_text);
    EXPECT(tokenizer.next_token() == "hello");
    EXPECT(tokenizer.next_token() == "world");
    // Extra space at the end, as "the rest" gets re-constructed from tokens
    EXPECT(tokenizer.get_the_rest() == "greetings from the moon ");
    tokenizer.set_input("34  asdf -5");
    EXPECT(tokenizer.get_integer_token(0) == 34);
    EXPECT(tokenizer.get_integer_token(3) == 3);
    EXPECT(tokenizer.get_integer_token(-2) == -2);
    // is_prefix_of
    EXPECT(is_prefix_of("bob","bobby") == true);
    EXPECT(is_prefix_of("bobby","bobby") == true);
    EXPECT(is_prefix_of("bobby","bobby", true) == false);
    EXPECT(is_prefix_of("bobby","tolya") == false);
    return true;
}

