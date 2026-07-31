#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "board_constants.h"
#include "board_logic.h"
#include "distances.h"

#include "game_saver.h"
#include "move_maker.h"
#include "../evaluator/evaluator.h"
#include <cassert>

// Board representation of the Schachfeld_Engine for playing standard chess,
// Using a two-dimensional, piece-centric "mailbox"-approach with 8x8 slots
// representing empty squares and pieces. 

// The board represents pieces as characters.
// Advantages:
//    * easy conversion of FEN-strings when receiving position-commands
//    * printing the board as_is() for debugging
//    * using the board as_is() as a hash-key, at least for rapid prototyping
typedef char TPiece;
typedef std::array<TPiece, BOARDSIZE_Y> TBoardColumn;

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

typedef size_t THashKey; 

class CBoard {
    friend class CFenParser;
    friend class CMoveMaker;
  public:
    CBoard();
    void clone_from_global_reference_board();
    void clone_to_global_reference_board();
  public:
    void set_start_position();
    bool set_fen_position(const std::string &position);
    std::string get_fen_position()/* const*/;
    inline std::string get_initial_position_before_moves() const { return initial_position_before_moves; }
    inline bool initial_position_was_startpos() const { return (get_initial_position_before_moves() == START_POSITION); };
    std::string moves_from_startpos() const;
     const char* as_is(); // TODO: inline including fill_up_printable_game_state?
  public:
     // flip_side_to_move() only flips, it does not care about eng-passeng.
     // Use CMoveMaker::make_null_move() if that is nedded.
    inline void flip_side_to_move() { side_to_move = !side_to_move; }
    void clear_square(const SSquare square);
    void put_piece(const SSquare square, TPiece piece);
  public:
    inline TPlayerColour get_side_to_move() const { return side_to_move; }
    TFile get_eng_passeng_file() const; 
    inline bool eng_passeng_possible() const { return (eng_passeng_file != NO_ENG_PASSENG_POSSIBLE); }
    int get_move_counter() const;
    int get_100_ply_draw_counter() const;
    TPiece get_square(const TFile file, const TRank rank) const;
    inline TPiece get_square(const SSquare square) const { return get_square(square.file, square.rank); }
    bool square_is_empty(const TFile file, const TRank rank) const;
    bool square_is_empty(const SSquare square) const;
    TSquareColour square_colour(const SSquare square) const;
  public:
    void clear_castling_rights();
    void set_castling_rights(const TPiece move_type, bool yes_no);
    bool get_castling_rights(TPiece move_type) const;
  public:
    THashKey get_hash();
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
    TPlayerColour side_to_move;
    TFile eng_passeng_file;
    int move_counter;
    int _100_ply_draw_counter;
    // Some over-size supports easy access via MOVE_TYPE (char)
    std::array<TPlayerColour, MOVE_TYPE_BLACK_SHORT_CASTLING + 1> castling_rights;
  private:
    std::string initial_position_before_moves;
};

inline void CBoard::clear_square(const SSquare square) {
    assert(square_in_range(square));
    evaluator.incremental_clear_square(square);
    board_state.squares[square.file][square.rank] = EMPTY_SQUARE;
}

inline void CBoard::put_piece(const SSquare square, char piece) {
    assert(square_in_range(square));
   assert(is_any_piece(piece) || (piece == EMPTY_SQUARE));
    evaluator.incremental_clear_square(square);
    board_state.squares[square.file][square.rank] = piece;
    evaluator.incremental_add(square);
}

inline TFile CBoard::get_eng_passeng_file() const {
    assert((eng_passeng_file == NO_ENG_PASSENG_POSSIBLE) || file_in_range(eng_passeng_file));
    return eng_passeng_file;
}

inline bool CBoard::square_is_empty(const TFile file, const TRank rank) const {
///    assert(file_in_range(file));
///    assert(rank_in_range(rank));
    return (get_square(file, rank) == EMPTY_SQUARE);
}

inline bool CBoard::square_is_empty(const SSquare square) const {
    assert(square_in_range(square));
    return square_is_empty(square.file, square.rank);
}

// Global board, as "everybody" needs easy access to it
inline thread_local CBoard board;
inline CBoard global_reference_board;

