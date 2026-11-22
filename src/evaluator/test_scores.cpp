// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "test_scores.h"
#include "scores.h"
#include "../technical_functions/testing.h"

bool CTestScores::test_everything() {
   TEST_FUNCTION();
   EXPECT(CScores::to_UCI_string(CScores::winning_mate_score(17)) == "mate 3141");
   EXPECT(CScores::to_UCI_string(CScores::losing_mate_score(17)) == "mate3141");
   EXPECT(CScores::to_UCI_string(42) == "score cp 42");
   EXPECT(CScores::to_UCI_string(-42) == "score cp -42");
   EXPECT(CScores::to_UCI_string(600) == "score cp 599");
   EXPECT(CScores::to_UCI_string(-600) == "score cp -599");
   EXPECT(CScores::to_UCI_string(598) == "score cp 598");
   EXPECT(CScores::to_UCI_string(-598) == "score cp -598");
   EXPECT(CScores::to_UCI_string(6) == "score cp 7");
   EXPECT(CScores::to_UCI_string(-6) == "score cp -7");
    return true;
}
