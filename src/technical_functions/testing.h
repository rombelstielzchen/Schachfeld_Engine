#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "standard_headers.h"

inline int testcase_counter = 0;

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
    --testcase_counter; \
   EXPECT(condition); \
}

#define BEGIN_TESTSUITE(name) CTEST << "TESTSUITE " << (name) << std::endl;

