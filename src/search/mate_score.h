#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

std::string const general_mate_score_for_engine_that_optimizes_material_not_distaance_to_mate = "mate 3141";

class CMateScore {
  public:
    static int losing_mate_score(int distance_to_root_in_plies);
    static int winning_mate_score(int distance_to_root_in_plies);
    static bool is_mate_score(int score__centi_wood_points);
    inline static std::string as_text([[maybe_unused]] int score_does_not_matter) { return general_mate_score_for_engine_that_optimizes_material_not_distaance_to_mate; }
};

