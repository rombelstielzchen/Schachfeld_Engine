#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include <string>

inline const std::string NO_MOVES_FROM_STARTPOS = "NO_MOVES_FROM_STARTPOS";

// Size of the board used for calculation:
//    * 8 squarres in both directions
//    * 2 squares garden-fence at all borders to detect out-of-board moves
//    * 1 newline-character at each column(!) to print the board as_is(),
//        as the memory-layout of our board is column after column.
constexpr int BOARDSIZE_X = 12;
constexpr int BOARDSIZE_Y = 13;
constexpr int N_SQUARES_ON_BOARD = 64;
constexpr int N_STONES_TOTAL = 32;

// Constants for ranks and files on the board.
// Always use named constants! 
// Rank "1" and file "a" have index 2 at a board with double garden fencees.
typedef enum : int8_t {
    ERROR_INVALID_FILE = -1,
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

typedef enum : int8_t {
    ERROR_INVALIDRANK = -1,
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

enum ESquareContent : char {
    EMPTY_SQUARE = '_',
    GARDEN_FENCE = '#',
    DUMMY_PIECE_FOR_TESTING = 'D',
    WHITE_BISHOP = 'B',
    WHITE_KING = 'K',
    WHITE_KNIGHT = 'N',
    WHITE_QUEEN = 'Q',
    WHITE_POWER = 'P',
    WHITE_ROOK = 'R',
    BLACK_BISHOP = 'b',
    BLACK_KING = 'k',
    BLACK_KNIGHT = 'n',
    BLACK_QUEEN = 'q',
    BLACK_POWER = 'p',
    BLACK_ROOK = 'r',
};

// Modelling side-to-move as booleans for easy indexing and flipping
typedef bool TPlayerColour;
constexpr TPlayerColour BLACK_PLAYER = false;
constexpr TPlayerColour WHITE_PLAYER = true;
// Modelling square-colour like player-colours to support confusion without harm
typedef TPlayerColour TSquareColour;
constexpr TSquareColour BLACK_SQUARE_COLOUR = BLACK_PLAYER;
constexpr TSquareColour WHITE_SQUARE_COLOUR = WHITE_PLAYER;

#pragma pack(push)
#pragma pack(1)

static_assert(sizeof(TFile) == 1);
static_assert(sizeof(TRank) == 1);

typedef struct {
   TFile file;
   TRank rank;
} SSquare;

static_assert(sizeof(SSquare) <= 2);

#pragma pack(pop)

inline const std::string START_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

inline constexpr TFile operator+(const TFile file, const int summand) {
    TFile result = static_cast<TFile>(static_cast<std::underlying_type_t<TFile>>(file) + summand);
    return result;
}

inline constexpr TFile operator-(const TFile file, const int subtrahend) {
    TFile result = file + -subtrahend;
    return result;
}

inline TFile& operator+=(TFile &file, const int summand) {
    file = file + summand;
    return file;
}

inline TFile& operator++(TFile &file) {
    file += 1;
    return file;
}

inline constexpr TRank operator+(const TRank rank, const int summand) {
    TRank result = static_cast<TRank>(static_cast<std::underlying_type_t<TRank>>(rank) + summand);
    return result;
}

inline constexpr TRank operator-(const TRank rank, const int subtrahend) {
    TRank result = rank + -subtrahend;
    return result;
}

inline TRank& operator+=(TRank &rank, const int summand) {
    rank = rank + summand;
    return rank;
}

inline TRank& operator++(TRank &rank) {
    rank += 1;
    return rank;
}

inline TRank& operator--(TRank &rank) {
    rank += - 1; 
    return rank;
}

