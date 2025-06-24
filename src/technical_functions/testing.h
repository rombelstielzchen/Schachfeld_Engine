#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "standard_headers.h"

inline int testcase_counter = 0;
static std::string classname_testsuite = "noname";

#define CTEST std::cerr

#define ACCUMULATE(pointer_to_bool, additional_condition) pointer_to_bool &= (additional_condition)
 
#define EXPECT(condition) \
++testcase_counter; \
if ((condition)) { \
    CTEST << "[OK] " << #condition << std::endl; \
} else { \
    CTEST << "[ERROR] ID " << testcase_counter << ": " << #condition << std::endl; \
    return false; \
}
 
#define SILENT_EXPECT(condition) \
++testcase_counter; \
if ((condition) == false) { \
    /* Do not naively call EXPECT here(). This would execute the condition again. */ \
    CTEST << "[ERROR] ID " << testcase_counter << ": " << #condition << std::endl; \
    return false; \
}

#define BEGIN_TESTSUITE(name)\
    classname_testsuite = name; \
    CTEST << "TESTSUITE " << classname_testsuite << std::endl;

#define TEST_FUNCTION() \
    CTEST << classname_testsuite << "::" <<  __func__ << "() ...\n";

