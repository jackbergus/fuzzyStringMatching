//
// Created by giacomo on 26/09/18.
//

#ifndef EDGEINDEXING_POLLMAP_H
#define EDGEINDEXING_POLLMAP_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits>

/**
 *
 *
 * @tparam K  Score associated to the element
 * @tparam V  Value which may have multiple score. For each element, we select the highest score
 */
template <typename K, typename V> class PollMap {
    std::map<K, std::set<V>> poll;
    std::unordered_map<V, K> valueScore;
    bool sanitize = false;
    int topK;

    void addKeyValue(K key, V value) {
        sanitize = false;
        typename std::unordered_map<V, K>::iterator ptr = valueScore.find(value);
        if (ptr != valueScore.end() && ptr->second < key) {
            valueScore[value] = key;
            typename std::map<K, std::set<V>>::iterator pf = poll.find(key);
            if (pf != poll.cend()) {
                auto toErase = pf->second.find(value);
                if (toErase != pf->second.cend())
                    pf->second.erase(toErase);
                if (pf->second.empty()) {
                    poll.erase(pf);
                }
            }
        }
        typename std::map<K, std::set<V>>::iterator kfind = poll.find(key);
        if (kfind == poll.cend()) {
            typename std::set<V> newSet;
            newSet.insert(value);
            poll.emplace(key, newSet);
            valueScore[value] = key;
        } else {
            poll[key].insert(value);
            valueScore[value] = key;
        }
    }

public:
    /**
     * TopK map initialization.
     * @param topK  If the integer is negative, then we preserve all the possible results
     */
    PollMap(int topK) {
        topK = topK <= 0 ? std::numeric_limits<int>::max() : topK;
    }

    void add(K key, V value) {
        if (poll.size() <= this->topK) {
            addKeyValue(key, value);
        } else {
            typename std::map<K, std::set<V>>::iterator cmpPtr = poll.begin();
            if (cmpPtr->first < key) {
                poll.erase(cmpPtr);
                addKeyValue(key, value);
            }
        }
    }

    // Please note that the multimap won't be in reversed order, and therefore we have to reversely scan it
    void getPoll(std::multimap<K, V>& toretMap) {
        if (!sanitize) {
            valueScore.clear();
            std::multimap<K, V> map{};
            typename std::map<K, std::set<V>>::iterator it;
            for ( it = poll.begin(); it != poll.end(); it++ ) {
                for (V value : it->second) {
                    map.emplace(it->first, value);
                }
            }
            poll.clear();
            typename std::multimap<K, V>::reverse_iterator it2;
            // value sanitizing process
            for (it2 = map.rbegin(); it2 != map.rend(); it2++) {
                if (valueScore.find(it2->second) == valueScore.end()) {
                    valueScore[it2->second] = it2->first;
                    typename std::map<K, std::set<V>>::iterator pf = poll.find(it2->first);
                    if (pf == poll.cend()) {
                        std::set<V> values{};
                        values.insert(it2->second);
                        poll.emplace(it2->first, values);
                    } else {
                        poll[it2->first].insert(it2->second);
                    }
                }
            }
            sanitize = true;
        }
        toretMap.clear();
        typename std::map<K, std::set<V>>::iterator it;
        for ( it = poll.begin(); it != poll.end(); it++ ) {
            for (V value : it->second) {
                toretMap.emplace(it->first, value);
            }
        }
    }
};

/*
 *
 * PollMap example
 *
 *
 *   int main(void) {
    PollMap<int, std::string> mapTest{2};
    mapTest.add(0, "elemento4");
    mapTest.add(0, "elemento1");
    mapTest.add(1, "elemento5");
    mapTest.add(1, "elemento1");
    mapTest.add(2, "elemento3");
    mapTest.add(2, "elemento2");
    mapTest.add(2, "elemento1");
    mapTest.add(2, "elemento");

    std::multimap<int, std::string> mm;
    mapTest.getPoll(mm);
    for (auto it = mm.rbegin(); it != mm.rend(); it++) {
        std::cout << std::to_string(it->first) << " --> "<< it->second << std::endl;
    }
}
 */

#endif //EDGEINDEXING_POLLMAP_H
