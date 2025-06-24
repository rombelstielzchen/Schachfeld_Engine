// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "math_functions.h"
#include "standard_headers.h"

bool approximately_equal(const double a, const double b) {
    constexpr double epsilon = 0.0001;
    double absolute_error = b - a;
    if (fabs(absolute_error) < epsilon) {
        return true;
    }
    if (fabs(a) < 1) {
        // Near 1: absolute_error and relative_error are of same magnitude,
        // already handled above.
        // Near 0: div0, precision problems.
        return false;
    }
    double relative_error = 1 - b / a;
    return (fabs(relative_error) < epsilon);
}

double root(const double radikant, const double exponent) {
   if (radikant < 0) {
        assert(NOT_YET_IMPLEMENTED);
       return -1;
   }
   if (approximately_equal(exponent, 0)) {
        return std::numeric_limits<double>::infinity();
   }
    return exp(log(radikant) / exponent);
}

