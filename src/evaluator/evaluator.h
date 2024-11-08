#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby
 
class CEvaluator {
  public:
    int evaluate() const;
  public:
    // For testing purposes
    bool evaluates_approximately_to(const int score) const;
  private:
    // Temp function to get some minimal positional understanding
    int positional_bonus(const int file, const int rank) const;
};

