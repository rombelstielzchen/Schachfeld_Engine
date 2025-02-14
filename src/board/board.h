#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Board representation of the Schachfeld_Engine for playing standard chess,
// Using a two-dimensional, piece-centric "mailbox"-approach with 8x8 slots
// representing empty squares and pieces. 
#include "move_maker.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

// Size of the board used for calculation:
//    * 8 squarres in both directions
//    * 2 squares garden-fence at all borders to detect out-of-board moves
//    * 1 newline-character at each column(!) to print the board as_is(),
//        as the memory-layout of our board is column after column.
constexpr int BOARDSIZE_X = 12;
constexpr int BOARDSIZE_Y = 13;
constexpr int N_SQUARES_ON_BOARD = 64;

// Constants for ranks and files on the board.
// Always use named constants! 
// Rank "1" and file "a" have index 2 at a board with double garden fencees.
typedef enum {
    FILE_GARDEN_FENCE_LEFT_1,
    FILE_GARDEN_FENCE_LEFT_2,
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_GARDEN_FENCE_RIGHT_1,
    FILE_GARDEN_FENCE_RIGHT_2,
    FILE_LAST = FILE_GARDEN_FENCE_RIGHT_2,
} TFile;

typedef enum {
    RANK_GARDEN_FENCE_BOTTOM_1,
     RANK_GARDEN_FENCE_BOTTOM_2,
     RANK_1,
     RANK_2,
     RANK_3,
     RANK_4,
     RANK_5,
     RANK_6,
     RANK_7,
     RANK_8,
     RANK_GARDEN_FENCE_TOP_1,
     RANK_GARDEN_FENCE_TOP_2,
     RANK_NEWLINE_CHARACTER,
} TRank;

static_assert(FILE_LAST == BOARDSIZE_X - 1);
static_assert(RANK_NEWLINE_CHARACTER == BOARDSIZE_Y - 1);
static_assert((FILE_H - FILE_A + 1) * (RANK_8 - RANK_1 + 1) == N_SQUARES_ON_BOARD);

// Eng-passeng gets stored as file of the opponents pawn
constexpr TFile NO_ENG_PASSENG_POSSIBLE = FILE_GARDEN_FENCE_LEFT_1;

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
constexpr bool BLACK_PLAYER = false;
constexpr bool WHITE_PLAYER = true;

inline const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class CBoard {
    friend class CFenParser;
    friend class CMoveMaker;
  public:
    CBoard();
  public:
    void set_start_position();
    bool set_fen_position(const std::string &position);
    std::string get_fen_position() const;
     const char* as_is() const;
  public:
    inline void flip_side_to_move() { side_to_move = !side_to_move; }
    void clear_square(const int file, const int rank);
    void put_piece(const int file, const int rank, char piece);
  public:
    inline bool get_side_to_move() const { return side_to_move; }
    int get_eng_passeng_file() const;
    inline bool eng_passeng_possible() const { return (eng_passeng_file != NO_ENG_PASSENG_POSSIBLE); }
    int get_move_counter() const;
    int get_100_ply_draw_counter() const;
    TSquare get_square(const int file, const int rank) const;
    bool square_is_empty(const int file, const int rank) const;
  public:
    void clear_castling_rights();
    void set_castling_rights(const char move_type, bool yes_no);
    bool get_castling_rights(char move_type) const;
    inline std::string get_moves_from_startpos() const { return moves_from_startpos; }
  public:
    CEvaluator evaluator;
    CMoveMaker move_maker;
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
    // Some over-size supports easy access via MOVE_TYPE (char)
    std::array<bool, MOVE_TYPE_BLACK_SHORT_CASTLING + 1> castling_rights;
    std::string moves_from_startpos;
};

// Global board, as "everybody" needs easy access to it
inline CBoard board;

