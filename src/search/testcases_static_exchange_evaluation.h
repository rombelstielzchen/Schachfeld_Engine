// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_search.h"

inline const std::vector<STestcaseStaticExchangeEvaluation> testcases_static_exchange_evaluation = {
    // White to move
    { "/ w", A8, false },
    { "1R w", A8, false },
    { "1r w", A8, false },
    { "rR w", A8, true },
{ "rR b", B8, true },
    { "rRr w", A8, false },
    { "8/5ppp/5n/8/8/8/2B/1Q w", H7, true },
    { "8/5ppp/5n/8/8/8/2Q/1B w", H7, false },
    { "8/5ppp/5n/5B2////7R w", H7, true },
    { "8/8/5ppp/5n///7R/7R w", H7, false },
    { "8/5ppp/5n/5B2////7Q w", H7, true },
    { "8/5ppp/5n/5B1Q w", H7, true },
    { "rRrRrRrR w", A8, true },
    { "rRrRrRr w", A8, false },
    { "rRrrRRR w", A8, false },
    { "rRrRrRrR/r/R/r/R/r/R w", A8, true },
    { "rRrRrRrR/r/R/r/R/r/R/r w", A8, false  },
    // Black to move
    { "/ b", A8, false },
    { "1R b", A8, false },
    { "1r b", A8, false },
    { "rR b", B8, true },
    { "rRr b", B8, true },
    { "3q/3Q/3q/4Q/3q b", D7, true },
    // King in check, can capture
    { "K5Rk b", G8, true },
    // King in check, can not capture
    { "KR4Rk b", G8, false },
};

