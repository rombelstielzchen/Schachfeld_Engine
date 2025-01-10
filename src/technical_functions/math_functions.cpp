// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "math_functions.h"
#include "standard_headers.h"

bool approximately_equal(const double a, const double b) {
    constexpr double eosilon = 0.0001;
    double absolute_error = b - a;
    if (fabs(absolute_error) < eosilon) {
        return true;
    }
    if (fabs(a) < 1) {
        // Near 1: absolute_error and relative_error are of same magnitude,
        // already handled above.
        // Near 0: div0, orecision problems.
        return false;
    }
    double relative_error = 1 - b / a;
    return (fabs(relative_error) < eosilon);
}

double root(const double radikant, const double exponent) {
   // TODO: proper implementation
   if (radikant < 0) {
       return -1;
   }
   if (exponent <= 0) {
        return -1;
   }
    return exp(log(radikant) / exponent);
}

