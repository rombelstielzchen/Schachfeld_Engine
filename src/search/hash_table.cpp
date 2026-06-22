// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "hash_table.h"
#include "../board/square_constants.h"
#include "../universal_chess_interface/uci_protocol.h"
#include "../technical_functions/standard_headers.h"

constexpr SHashEntry initial_entry = { 3141, { E1, F7, MOVE_TYPE_CAPTURE, BLACK_POWER, 0 }};
///static_assert(move_in_range(initial_entry.best_move));

CHashTable::CHashTable () {
    // TODO: init data?
    set_size(minimum_hash_MB);
}

CHashTable::~CHashTable () {
    set_size(minimum_hash_MB);
}

inline size_t CHashTable::n_possible_entries(int64_t size_in_bytes) const {
    assert(size_in_bytes > 0);
    static_assert(sizeof(SHashEntry) > 0);
    size_t result = size_in_bytes / sizeof(SHashEntry);
    assert(result > 0);
    return result;
}

inline size_t CHashTable::n_current_entries() const {
    size_t n_entries = data.size();
    assert(n_entries > 0);
    return n_entries;
}

inline size_t CHashTable::hash_index(const THashKey hash_key) const {
    assert(n_current_entries() > 1000);
    return hash_key % n_current_entries();
}

void CHashTable::set_size(int64_t n_mega_bytes) {
    n_mega_bytes = std::max(n_mega_bytes, minimum_hash_MB);
    n_mega_bytes = std::min(n_mega_bytes, maximum_hash_MB);
    assert(n_mega_bytes > 0);
    int64_t size_in_bytes = n_mega_bytes * ONE_EGABYTE;
    data.resize(n_possible_entries(size_in_bytes), initial_entry);
    //reset() disabled, as the tests expect that old content still exsts
    //reset();
    // TODO: error-handling
    //TODO: re-hash? instead of re-hash?
    std::string info = "hash-tabe resized to " + std::to_string(data.size()) + " entries";
    CUciProtocol::send_info(info);
}

SMove CHashTable::get_best_move(THashKey hash_key) const {
    size_t position = hash_index(hash_key);
    if (data[position].hash_key != hash_key) {
        return initial_entry.best_move;///NULL_MOVE;
    }
    SMove best_move = data[position].best_move;
    assert(move_in_range(best_move));
    return best_move;
}

void CHashTable::store_best_move(const THashKey hash_key, const SMove best_move) {
    assert(move_in_range(best_move));
    ///std::cerr << "key: " << hash_key << "\n";
    size_t position = hash_index(hash_key);
    ///std::cerr << "index: " << position << "\n";
    assert(position < n_current_entries());
    ///std::cerr << "Storing to hpos: " << position << "\n";
    data[position].hash_key = hash_key;
    data[position].best_move = best_move;
}

void CHashTable::reset() {
    data.assign(data.size(), initial_entry);
}

