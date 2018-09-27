//
// Created by giacomo on 26/09/18.
//

#ifndef EDGEINDEXING_CLASSES_H
#define EDGEINDEXING_CLASSES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>

/**
 * Easing the java rewriting
 */
typedef  std::string                    String;
template <typename N> using ArrayList = std::vector<N>;
template <typename N> using HashSet = std::unordered_set<N>;
template <typename K, typename V> using HashMap = std::unordered_map<K, V>;
template <typename K, typename V> using TreeMultimap = std::multimap<K, V>;
template <typename K, typename V> using HashMultimap = std::unordered_multimap<K, V>;


#endif //EDGEINDEXING_CLASSES_H
