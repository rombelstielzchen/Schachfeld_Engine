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

// Enumerations for ranks and files on the board.
// Always use named constants! 
// Rank "1" and file "a" have index 2 at a board with double garden fencees.
enum EFiles {
    FILE_FGARDEN_FENCE_LEFT_1,
    FILE_FGARDEN_FENCE_LEFT_2,
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_FGARDEN_FENCE_RIGHT_1,
    FILE_FGARDEN_FENCE_RIGHT_2,
    FILE_LAST = FILE_FGARDEN_FENCE_RIGHT_2,
};

enum ERanks {
    RANK_FGARDEN_FENCE_BOTTOM_1,
    RANK_FGARDEN_FENCE_BOTTOM_2,
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_FGARDEN_FENCE_TOP_1,
    RANK_FGARDEN_FENCE_TOP_2,
    RANK_NEWLINE_CHARACTER,
};

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
    const TSquare get_square(const EFiles x, const ERanks y);
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
