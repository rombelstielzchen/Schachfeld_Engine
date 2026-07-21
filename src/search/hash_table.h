#pragma once

// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "../move_generator/move.h"
#include <vector>

constexpr int64_t minimum_hash_MB = 1;
constexpr int64_t maximum_hash_MB = 1024;

constexpr int64_t ONE_EGABYTE = 1000000;
static_assert(ONE_EGABYTE < (1 << 20));
static_assert(ONE_EGABYTE > (1 << 19));

typedef size_t THashKey; 

typedef struct {
    THashKey hash_key;
    int distance_to_root;
    SMove best_move;
} SHashEntry;

class CHashTable {
    friend class CTestHashTable;
  public:
    CHashTable();
    ~CHashTable();
  public:
    void reset();
    void store_best_move(const SMove &best_move, const THashKey hash_key, const int distance_to_root);
    SMove get_best_move(THashKey hash_key) const;
    void set_size(int64_t n_mega_bytes);
    void show_hash(const THashKey hash_key) const;
  private:
    size_t n_possible_entries(int64_t size_in_bytes) const;
    size_t n_current_entries() const;
    size_t hash_index(const THashKey key) const;
    size_t last_index() const { return data.size() - 1; }
  private:
    bool may_overwrite(const THashKey new_hash_key, int new_distance_to_root, const SHashEntry &existing_entry_entry) const;
  private:
    std::vector<SHashEntry> data;
};

inline CHashTable hash_table;

