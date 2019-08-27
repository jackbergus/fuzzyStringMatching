//
// Created by giacomo on 27/08/19.
//

#ifndef INCONSISTENCY_LINKEDHASHMULTIMAP_H
#define INCONSISTENCY_LINKEDHASHMULTIMAP_H

#include <vector>
#include <map>

template <typename K, typename V>
struct LinkedHashMultimap {
    std::vector<K> data;
    std::map<K, std::vector<V>> map;
    void put(K key, V value) {
        if (map.find(key) == map.end()) {
            data.emplace_back(key);
        }
        map[key].emplace(value);
    }

    void clear() {
        data.clear();
        map.clear();
    }

};


#endif //INCONSISTENCY_LINKEDHASHMULTIMAP_H
