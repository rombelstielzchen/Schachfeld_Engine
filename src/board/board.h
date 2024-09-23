#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Board representation of the Schachfeld_Engine for playing standard chess,
// Using a two-dimensional, piece-centric "mailbox"-approach with 8x8 slots
// representing empty squares and pieces. 

#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

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
// We switched from enums to simple constants, because order and values matter
// and we sometimes need numerical operators.
constexpr int FILE_GARDEN_FENCE_LEFT_1 = 0;
constexpr int FILE_GARDEN_FENCE_LEFT_2 = 1;
constexpr int FILE_A = 2;
constexpr int FILE_B = 3;
constexpr int FILE_C = 4;
constexpr int FILE_D = 5;
constexpr int FILE_E = 6;
constexpr int FILE_F = 7;
constexpr int FILE_G = 8;
constexpr int FILE_H = 9;
constexpr int FILE_GARDEN_FENCE_RIGHT_1 = 10;
constexpr int FILE_GARDEN_FENCE_RIGHT_2 = 11;
constexpr int FILE_LAST = FILE_GARDEN_FENCE_RIGHT_2;

constexpr int RANK_GARDEN_FENCE_BOTTOM_1 = 0;
constexpr int  RANK_GARDEN_FENCE_BOTTOM_2 = 1;
constexpr int  RANK_1 = 2;
constexpr int  RANK_2 = 3;
constexpr int  RANK_3 = 4;
constexpr int  RANK_4 = 5;
constexpr int  RANK_5 = 6;
constexpr int  RANK_6 = 7;
constexpr int  RANK_7 = 8;
constexpr int  RANK_8 = 9;
constexpr int  RANK_GARDEN_FENCE_TOP_1 = 10;
constexpr int  RANK_GARDEN_FENCE_TOP_2 = 11;
constexpr int  RANK_NEWLINE_CHARACTER = 12;

// Eng-passeng gets stored as file of the opponents pawn
constexpr int NO_ENG_PASSENG_POSSIBLE = FILE_GARDEN_FENCE_LEFT_1;

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

// Modelling side-to-move as booleans for easy flipping
constexpr bool WHITE_TO_MOVE = true;
constexpr bool BLACK_TO_MOVEE = false;

const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class CBoard {
    friend class CFenParser;
  public:
    CBoard();
  public:
    void set_start_position();
    bool set_fen_position(const std::string &position);
    std::string get_fen_position() const;
    const char* const as_is() const;
  public:
    bool make_move(const SMove move);
    bool make_move(const std::string &long_algebraic_uci_move);
    void unmake_move();
  public:
    bool get_side_to_move() const;
    int get_eng_passeng_file() const;
    int get_move_counter() const;
    int get_100_ply_draw_counter() const;
    TSquare get_square(const int file, const int rank) const;
    bool square_is_empty(const int file, const int rank) const;
  private:
    void init_garden_fence();
    void clear();
  private:
    // Using std::array instead of old-style C arrays.
    // Advantages:
    //   * std::arrays know their size and check memory-access in debug-mode
    //   * in production they work exactly the same. Same speed!
    std::array<TBoardColumn, BOARDSIZE_X> squares;
    bool side_to_move;
    int eng_passeng_file;
    int move_counter;
    int _100_ply_draw_counter;
};

// Global board, as "everybody" needs easy access to it
extern CBoard board;

