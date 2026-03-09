#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board_constants.h"
#include "game_saver.h"
#include "move_maker.h"
#include "../evaluator/evaluator.h"
#include "../move_generator/move.h"
#include "../technical_functions/standard_headers.h"

// Board representation of the Schachfeld_Engine for playing standard chess,
// Using a two-dimensional, piece-centric "mailbox"-approach with 8x8 slots
// representing empty squares and pieces. 

// The board represents pieces as characters.
// Advantages:
//    * easy conversion of FEN-strings when receiving position-commands
//    * printing the board as_is() for debugging
//    * using the board as_is() as a hash-key, at least for rapid prototyping
typedef std::array<TSquare, BOARDSIZE_Y> TBoardColumn;

constexpr int N_CASTLING_DIRECTIONS_LS_ls = 4;

#pragma pack(push)
#pragma pack(1)

typedef struct {
    // Using std::array instead of old-style C arrays.
    // Advantages:
    //   * std::arrays know their size and check memory-access in debug-mode
    //   * in production they work exactly the same. Same speed!
    std::array<TBoardColumn, BOARDSIZE_X> squares;
    // The engine works with the data in the CBoard-class.
    // If we want to print or hash the position, we have to clone some non-textual info first.
    // Not included here are move_counter and _100_ply_draw_counter;
    // they must not affect the decision whether two positions are equal.
    char side_to_move;
    char empty_1;
    char castling_rights[N_CASTLING_DIRECTIONS_LS_ls];
    char empty_2;
    char eng_passeng_file;
    char final_newline;
    char terminating_null;
} SPrintableBoardState;

#pragma pack(pop)

class CBoard {
    friend class CFenParser;
    friend class CMoveMaker;
  public:
    CBoard();
  public:
    void set_start_position();
    bool set_fen_position(const std::string &position);
    std::string get_fen_position() const;
    std::string get_initial_position_before_moves() const { return initial_position_before_moves; }
    bool initial_position_was_startpos() const { return (get_initial_position_before_moves() == START_POSITION); };
    std::string moves_from_startpos() const;
     const char* as_is();
  public:
    inline void flip_side_to_move() { side_to_move = !side_to_move; }
    void clear_square(const SSquare square);
    void put_piece(const SSquare square, char piece);
  public:
    inline bool get_side_to_move() const { return side_to_move; }
    int get_eng_passeng_file() const;
    inline bool eng_passeng_possible() const { return (eng_passeng_file != NO_ENG_PASSENG_POSSIBLE); }
    int get_move_counter() const;
    int get_100_ply_draw_counter() const;
    TSquare get_square(const int file, const int rank) const;
    inline TSquare get_square(const SSquare square) const {
        ///assert(square_in_range(square)); 
        return get_square(square.file, square.rank); 
    }
    bool square_is_empty(const int file, const int rank) const;
    bool square_is_empty(const SSquare square) const;
  public:
    void clear_castling_rights();
    void set_castling_rights(const char move_type, bool yes_no);
    bool get_castling_rights(char move_type) const;
  public:
    size_t get_hash();
  public:
    CEvaluator evaluator;
    CGameSaver game_saver;
    CMoveMaker move_maker;
  private:
    void clear_board_squares();
    void init_garden_fence();
    void fill_up_printable_game_state();
  private:
    // All board-state gets set by the FEN-parser
    SPrintableBoardState board_state;
    bool side_to_move;
    int eng_passeng_file;
    int move_counter;
    int _100_ply_draw_counter;
    // Some over-size supports easy access via MOVE_TYPE (char)
    std::array<bool, MOVE_TYPE_BLACK_SHORT_CASTLING + 1> castling_rights;
  private:
    std::string initial_position_before_moves;
};

// Global board, as "everybody" needs easy access to it
inline CBoard board;

