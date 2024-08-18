// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#pragma one

#include <array>
#include <cstdint>
#include <string>

// https://www.chessprogramming.org/Chess_Position
constexpr int MAX_MOVES_IN_CHESS_POSITION = 218;

typedef uint64_t TMove;

class CMoveGenerator {
  public:
      CMoveGenerator();
  public:
    void generate_all();
    TMove get_random() const;
    int list_size() const;
  public:
    static constexpr std::string as_text(const TMove move);
  private:
    std::array<TMove, MAX_MOVES_IN_CHESS_POSITION> move_list;
    int number_of_moves;
}; 
