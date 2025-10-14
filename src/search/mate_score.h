#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

class CMateScore {
  public:
    static int losing_mate_score(int distance_to_root_in_plies);
    static int winning_mate_score(int distance_to_root_in_plies);
};

