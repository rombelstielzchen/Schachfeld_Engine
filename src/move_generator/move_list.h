#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "move.h"
#include "../technical_functions/standard_headers.h"

constexpr unsigned int MOVE_NOT_ON_LIST = INT_MAX;

// https://www.talkchess.com/forum/viewtopic.php?t=39332
constexpr int MAX_MOVES_IN_CHESS_POSITION = 218;
// Captures: probably 74. We use conservative 80.
// https://chess.stackexchange.com/questions/8323/maximum-number-of-captures-in-a-position
constexpr unsigned int MAX_CAPTURES_IN_CHESS_POSITION = 80;
// Our move-list is bidirectional; left part for captures, right part for silent moves.
constexpr unsigned int LIST_SIZE = MAX_MOVES_IN_CHESS_POSITION + MAX_CAPTURES_IN_CHESS_POSITION;
constexpr unsigned int LIST_ORIGIN = MAX_CAPTURES_IN_CHESS_POSITION;

class CMoveList {
    friend class CTestMoveGenerator;
    friend class CTestMoveList;
  public:
    CMoveList();
    int list_size() const;
    // TODO: is_empty()
    SMove get_random() const;
    SMove get_next__best_capture();
    SMove get_next();
    SMove get_next__capture_killer_silent(int dis);
    SMove get_least_valuable_aggressor() const;
    SMove lookup_move(const std::string &text_move) const;
  public:
    void store_castling(const char move_type);
    void store_eng_passeng(const int source_file, const int source_rank, const int target_file, const int target_rank);
    // Special method for pawns, creating four moves on promotion
    void store_pawn_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_pawn_move(const int source_file, const int source_rank, const int target_file, const int target_rank);
  public:
    void store_silent_move(const int source_file, const int source_rank, const int target_file, const int target_rank, const char move_type = MOVE_TYPE_NORMAL);
    void store_capture(const int source_file, const int source_rank, const int target_file, const int target_rank);
  public:
    void prune_silent_moves();
    void unprune_silent_moves();
    void filter_captures_by_target_square(const SSquare &target_square);
  public:
    // For the root-node, in order to avoid greedy captures when getting mated
    void prune_illegal_moves();
  public:
    // For root-node ordering
    // This function "ruins" the pre-sortedness of the list,
    // therefore to be used at the root-node only,  where we analyze all moves
    // and don't depend on a separation of captures and silent moves.
    void shift_current_move_to_top();
    void reuse_list();
  public:
    void integrate_killer(int distance_to_root); 
  public:
    std::string as_text() const;
  private:
    void clear();
  private:
    void store_white_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank);
    void store_black_promotions(const int source_file, const int source_rank, const int target_file, const int target_rank);
  private:
    void store_silent_move(const SMove &move);
    inline void store_capture(const SMove &move);
  private:
    inline unsigned int last_move_index() const { return next_empty_slot - 1; }
    unsigned int get_index(const SMove basic_move) const;
    bool move_on_list(const std::string &move_text) const;
  private:
    // Use remove() only on unused_list(), no get_next()
    void remove(const SMove move);
    void remove(const std::string &move_text);
    void remove(unsigned int position);
    void remove_capture(unsigned int position);
    void remove_silent_move(unsigned int position);
    void prune_illegal_castlings();
  private:
    bool valid_list_origin() const;
    bool valid_consumer_position() const;
    bool valid_list() const;
    bool unused_list() const;
  private:
    // Using array instead of vector due to its known size and for better performance
    std::array<SMove,LIST_SIZE> bidirectional_move_list;
    unsigned int first_capture;
    unsigned int next_empty_slot;
    unsigned int next_empty_slot_before_pruning_silent_moves;
    unsigned int consumer_position;
};
 
