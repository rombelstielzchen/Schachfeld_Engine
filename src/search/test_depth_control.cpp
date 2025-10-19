// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_depth_control.h"
#include "depth_control.h"
#include "../technical_functions/testing.h"

bool CTestDepthControl::test_everything() {
    BEGIN_TESTSUITE("CTestDepthControl");
    EXPECT(test_depth());
    EXPECT(test_depth_adaption_for_better_mates());
    return true;
}

bool CTestDepthControl::test_depth() {
    TEST_FUNCTION();
    CDepthControl depth_control;
    depth_control.set_depth(3);
    EXPECT(depth_control.go_deeper(1));
    EXPECT(depth_control.go_deeper(2));
    EXPECT(depth_control.go_deeper(3) == false);
    EXPECT(depth_control.go_deeper(4) == false);
    return true;
}

bool CTestDepthControl::test_depth_adaption_for_better_mates() {
    TEST_FUNCTION();
    // TODO: test_depth_adaption_for_better_mates
    return true;
}

