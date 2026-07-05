// Project: Schachfeld_Engine
// Author: Rombelstielzchen
// License: GPLv3
// Forum: https://www.schachfeld.de/threads/40956-einen-namen-fuer-das-baby

#include "hash_table.h"
#include "../board/square_constants.h"
#include "../technical_functions/standard_headers.h"
#include "../universal_chess_interface/uci_protocol.h"

constexpr THashKey initial_dummy_hash_key = 3141;
constexpr int initial_dummy_distance_to_root = 999;

constexpr SHashEntry initial_entry = { initial_dummy_hash_key, initial_dummy_distance_to_root, NULL_MOVE }; 

CHashTable::CHashTable () {
    set_size(minimum_hash_MB);
}

CHashTable::~CHashTable () {
    set_size(minimum_hash_MB);
}

inline size_t CHashTable::n_possible_entries(int64_t size_in_bytes) const {
    static_assert(sizeof(SHashEntry) > 0);
    ///assert(size_in_bytes > sizeof(SHashEntry));
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
    //TODO: reset() or re-hash, as old adreses lost their meaning
    std::string info = "hash-tabe resized to " + std::to_string(data.size()) + " entries";
    CUciProtocol::send_info(info);
}

SMove CHashTable::get_best_move(THashKey hash_key) const {
    size_t position = hash_index(hash_key);
    if (data[position].hash_key != hash_key) {
        return NULL_MOVE;
    }
    assert(data[position].distance_to_root >= 0);
    assert((data[position].distance_to_root < initial_dummy_distance_to_root) || (hash_key == initial_dummy_hash_key));
    SMove best_move = data[position].best_move;
    assert(move_in_range(best_move) || (best_move == NULL_MOVE));
    return best_move;
}

void CHashTable::reset() {
    data.assign(data.size(), initial_entry);
}

void CHashTable::store_best_move(const SMove &best_move, const THashKey hash_key, const int distance_to_root) {
    assert(move_in_range(best_move));
    assert(distance_to_root >= 0);
    assert(distance_to_root < initial_dummy_distance_to_root);
    const size_t index = hash_index(hash_key);
    SHashEntry &existing_entry = data[index];
    if (may_overwrite(hash_key, distance_to_root, existing_entry)) {
        data[index].hash_key = hash_key;
        data[index].distance_to_root = distance_to_root;
        data[index].best_move = best_move;
    }
}

bool CHashTable::may_overwrite(const THashKey hash_key, int distance_to_root, const SHashEntry &existing_entry) const {
    if (distance_to_root > existing_entry.distance_to_root) {
        return false;
    }
    if (distance_to_root < existing_entry.distance_to_root) {
        return true;
    }
    assert(distance_to_root == existing_entry.distance_to_root);
    return (hash_key == existing_entry.hash_key); 
}

void CHashTable::show_hash(const THashKey hash_key) const {
    std::string info = "hash_key:         " + std::to_string(hash_key);
    CUciProtocol::send_info(info);
    size_t index = hash_index(hash_key);
    info = "index:            " + std::to_string(index);;
    CUciProtocol::send_info(info);
    info = "distance_to_root: " + std::to_string(data[index].distance_to_root);
    CUciProtocol::send_info(info);
    info = "best_move:        " + move_as_text(get_best_move(hash_key));
    CUciProtocol::send_info(info);
}

