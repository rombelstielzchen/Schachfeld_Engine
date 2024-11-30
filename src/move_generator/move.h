#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

// Data-containers for squares (coordinates) and moves, 
// modelled as structs, not objects, because:
//    * they are simple, stupid containers
//    * they get used a lot, performance matters (a bit)
//    * we want to return moves as rvalue and store them in space-limited hash-tables.

#include "../technical_functions/standard_headers.h"

// Flags for special moves,
// modelled as chars, as a flag may also describe a promotion-piece
constexpr char MOVE_TYPE_WHITE_LONG_CASTLING = 'L';
constexpr char MOVE_TYPE_WHITE_SHORT_CASTLING = 'S';
constexpr char MOVE_TYPE_BLACK_LONG_CASTLING = 'l';
constexpr char MOVE_TYPE_BLACK_SHORT_CASTLING = 's';
constexpr char MOVE_TYPE_ENG_PASSENG = 'e';
constexpr char MOVE_TYPE_DOUBLE_JUMP = 'j';
constexpr char MOVE_TYPE_CAPTURE = 'x';
constexpr char MOVE_TYPE_NORMAL = '\0';

#pragma pack(push)
#pragma pack(1)

typedef struct {
   uint8_t file;
   uint8_t rank;
} SSquare;

typedef struct {
    SSquare source;
    SSquare target;
   char move_type;
   char captured_piece;
} SMove;

static_assert(sizeof(SSquare) <= sizeof(int));
static_assert(sizeof(SMove) <= sizeof(int64_t));

#pragma pack(pop)

// Internal encoding of "none", "finished", "end of list"
constexpr SMove NULL_MOVE = {{0, 0}, 
    {0, 0}, 
    MOVE_TYPE_NORMAL
};

// Textual encoding according to the UCI-standard, 4 zeroes
inline const std::string NULL_MOVE_AS_TEXT = "0000";

// Error value for ranks and files, when converting from bad textual input
constexpr uint8_t ERROR_INVALID_COORDINATE = -1;

 bool file_in_range(const int file);
bool rank_in_range(const int rank);
bool square_in_range(const SSquare square);
bool move_in_range(const SMove move);
bool is_null_move(const SMove move);
bool is_any_capture(const SMove &move);
bool is_any_piece(char square_or_move_type);

char file_as_text(const int file);
char rank_as_text(const int file);
std::string square_as_text(const SSquare square);
std::string move_as_text(const SMove move);

uint8_t text_to_file(const char file_character);
uint8_t text_to_rank(const char rank_character);
// text_to_basic_move does not know the finer details (castling, eng-passeng, ...).
// Use this function only as a tool in smarter functions and for verifications
SMove text_to_basic_move(const std::string &text);

bool move_coords_are_equal(const SMove &a, const SMove &b);
bool operator == (const SSquare a, const SSquare b);
bool operator ==(const SMove a, const SMove b);
bool operator ==(const SMove a, const std::string &b);

