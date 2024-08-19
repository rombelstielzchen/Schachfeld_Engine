#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <array>
#include <string>

// Board representation of the Schachfeld_Engine for playing standard chess,
// Using a two-dimensional, piece-centric "mailbox"-approach with 8x8 slots
// representing empty squares and pieces. 

// Size of the board used for calculation:
//    * 8 squarres in both directions
//    * 2 squares garden-fence at all borders to detect out-of-board moves
//    * 1 newline-character at each column(!) to print the board as_is(),
//        as the memory-layout of our board is column after column.
constexpr int BOARDSIZE_X = 12;
constexpr int BOARDSIZE_Y = 13;

// Constants for ranks and files on the board.
// Always use named constants! 
// Rank "1" and file "a" have index 2 at a board with double garden fencees.
// We switched from enums to simpe constants, because order and values matter
// and we sometimes need numerical operators.
constexpr int FILE_FGARDEN_FENCE_LEFT_1 = 0;
constexpr int FILE_FGARDEN_FENCE_LEFT_2 = 1;
constexpr int FILE_A = 2;
constexpr int FILE_B = 3;
constexpr int FILE_C = 4;
constexpr int FILE_D = 5;
constexpr int FILE_E = 6;
constexpr int FILE_F = 7;
constexpr int FILE_G = 8;
constexpr int FILE_H = 9;
constexpr int FILE_FGARDEN_FENCE_RIGHT_1 = 10;
constexpr int FILE_FGARDEN_FENCE_RIGHT_2 = 11;
constexpr int FILE_LAST = FILE_FGARDEN_FENCE_RIGHT_2;

constexpr int RANK_FGARDEN_FENCE_BOTTOM_1 = 0;
constexpr int  RANK_FGARDEN_FENCE_BOTTOM_2 = 1;
constexpr int  RANK_1 = 2;
constexpr int  RANK_2 = 3;
constexpr int  RANK_3 = 4;
constexpr int  RANK_4 = 5;
constexpr int  RANK_5 = 6;
constexpr int  RANK_6 = 7;
constexpr int  RANK_7 = 8;
constexpr int  RANK_8 = 9;
constexpr int  RANK_FGARDEN_FENCE_TOP_1 = 10;
constexpr int  RANK_FGARDEN_FENCE_TOP_2 = 11;
constexpr int  RANK_NEWLINE_CHARACTER = 12;

// The board represents pieces as characters.
// Advantages:
//    * easy conversion of FEN-strings when receiving position-commands
//    * printing the board as_is() for debugging
//    * using the board as_is() as a hash-key, at least for rapid prototyping
typedef char TSquare;

enum ESquareContent : TSquare {
    EMPTY_SQUARE = '_',
    GARDEN_FENCE = '#',
    WHITE_KING = 'K',
    WHITE_QUEEN = 'Q',
    WHITE_ROOK = 'R',
    WHITE_BISHOP = 'B',
    WHITE_KNIGHT = 'N',
    WHITE_POWER = 'P',
    BLACK_KING = 'k',
    BLACK_QUEEN = 'q',
    BLACK_ROOK = 'r',
    BLACK_BISHOP = 'b',
    BLACK_KNIGHT = 'n',
    BLACK_POWER = 'p',
};

typedef std::array<TSquare, BOARDSIZE_Y> TBoardColumn;

class CBoard {
    friend class CFenParser;
  public:
    CBoard();
  public:
    bool set_fen_position(const std::string &position);
    const std::string get_fen_position();
    const char* const as_is() const;
    const TSquare get_square(const int x, const int y);
  private:
    void init_garden_fence();
    void clear();
  private:
    // Using std::array instead of old-style C arrays.
    // Advantages:
    //   * std::arrays know their size and check memory-access in debug-mode
    //   * in production they work exactly the same. Same speed!
    std::array<TBoardColumn, BOARDSIZE_X> squares;
};
