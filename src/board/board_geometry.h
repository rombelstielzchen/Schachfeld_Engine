// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board_constants.h"

class CBoardGeometry {
  public:
    static bool on_same_diagonal(const SSquare a, const SSquare b);
    static bool on_same_anti_diagonal(const SSquare a, const SSquare b);
  public:
    // May return a file of the garden-fence
    static TFile central_neighbour_file(TFile file);
    static TFile excentric_neighbour_file(TFile file);
};

