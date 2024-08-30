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

#pragma pack(1)

typedef struct {
   uint8_t file;
   uint8_t rank;
} SSquare;

typedef struct {
    SSquare source;
    SSquare target;
    // TODO: castling, promotion, eng-passeng
} SMove;

// Internal encoding of "none", "finished", "end of list"
constexpr SMove NULL_MOVE = {{0, 0}, {0, 0}};
// Textual encoding according to the UCI-standard, 4 zeroes
const std::string NULL_MOVE_AS_TEXT = "0000";

bool file_in_range(const int file);
bool rank_in_range(const int rank);
bool square_in_range(const SSquare square);
bool move_in_range(const SMove move);
bool is_null_move(const SMove move);

char file_as_text(const int file);
char rank_as_text(const int file);
std::string square_as_text(const SSquare square);
std::string move_as_text(const SMove move);

