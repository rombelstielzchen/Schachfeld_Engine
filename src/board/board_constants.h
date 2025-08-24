#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

const std::string NO_MOVES_FROM_STARTPOS = "NO_MOVES_FROM_STARTPOS";

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

// Modelling side-to-move as booleans for easy flipping
constexpr bool BLACK_PLAYER = false;
constexpr bool WHITE_PLAYER = true;

inline const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

