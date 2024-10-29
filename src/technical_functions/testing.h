#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "standard_headers.h"

#define CTEST std::cerr

#define ACCUMULATE(pointer_to_bool, additional_condition) pointer_to_bool &= (additional_condition)
 
#define EXPECT(condition) \
if ((condition)) { \
    CTEST << "[OK] " << #condition << std::endl; \
} else { \
    CTEST << "[ERROR] " << #condition << std::endl; \
    return false; \
}
 
#define SILENT_EXPECT(condition) \
if ((condition) == false) { \
    CTEST << "[ERROR] " << #condition << std::endl; \
    return false; \
}

#define BEGIN_TESTSUITE(name) CTEST << "TESTSUITE " << (name) << std::endl;
   
