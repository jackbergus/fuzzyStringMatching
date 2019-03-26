//
// Created by giacomo on 29/12/18.
//

#ifndef INCONSISTENCY_FIXED_BIMAP_H
#define INCONSISTENCY_FIXED_BIMAP_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <functional>
#include <sstream>

/**
 * A fixed bimap will help to store a bijection as a map of hash keys
 * @tparam K
 * @tparam V
 */
template <typename K, typename V> class fixed_bimap {
    /**
     * This maps each key or value hash into the vector offset where they are stored in the vector.
     * By doing so, each element should be represented once, that is the offset where they appear.
     */
    std::unordered_map<std::string, size_t> map;
    std::vector<std::pair<K, V>> elements;

    size_t size = 0;

public:
    /**
     * Always assumes that the key and the value are always with a bimap.
     * This method is implemented to reduce the amounts of checks for a boolean variable.
     *
     * @param key
     * @param value
     */
    void put(K key, V value) {
        elements.push_back(std::make_pair(key, value));
        std::ostringstream oss{}, vos{};
        oss << "k_" << key;
        vos << "v_" << value;
        map[oss.str()] = size;
        map[vos.str()] = size;
        size++;
    }

    /**
     * Updates the bimap iff. there was no previously set key with another value
     * @param key
     * @param value
     * @return          Either the new value, or the previously associated one.
     */
    V putWithKeyCheck(K key, V value) {
        std::ostringstream oss{}, vos{};
        oss << "k_" << key;
        std::string keyS = oss.str();
        std::unordered_map<std::string, size_t>::iterator it = map.find(keyS);
        if ( it != map.cend()) { // =>
            elements.push_back(std::make_pair(key, value));
            vos << "v_" << value;
            map[keyS] = size;
            map[vos.str()] = size;
            size++;
        }
    }

    V getValue(K key) {
        std::ostringstream oss{};
        oss << "k_" << key;
        return elements[map[oss.str()]].second;
    }

    K getKey(V value) {
        std::ostringstream vos{};
        vos << "v_" << value;
        return elements[map[vos.str()]].first;
    }

};

#endif //INCONSISTENCY_FIXED_BIMAP_H
