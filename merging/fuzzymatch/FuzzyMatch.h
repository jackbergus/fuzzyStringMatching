//
// Created by giacomo on 17/10/18.
//

#ifndef EDGEINDEXING_FUZZYMATCH_H
#define EDGEINDEXING_FUZZYMATCH_H

#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_set>
#include "../../fmatch/FuzzyMatch_FDContainer.h"


class FuzzyMatch {


    std::string baseDir;
    std::unordered_map<std::string, FuzzyMatch_FDContainer> map;
    void openDimension(std::string& dimension);
    void closeDimension(std::string& dimension) {
        map.erase(dimension);
    }

public:
    /**
     * Performs the fuzzy match over the binary indices optimizing the fuzzy matching access
     * @param directory
     */
    FuzzyMatch(std::string directory);

    /**
     * Performs the fuzzy matching of a term on top of a hierarchy
     * @param dimension
     * @param threshold
     * @param topk
     * @param objectString
     * @param result
     */
    void fuzzyMatch(std::string& dimension, double threshold, int topk, String& objectString,
                    TreeMultimap<double, LONG_NUMERIC> &result) {
        if (map.find(dimension) == map.cend())
            openDimension(dimension);
        map[dimension].fuzzyMatch(threshold, topk, objectString, result);
    }

    void containsExactTerm(std::string& dimension, std::string& term, ArrayList<LONG_NUMERIC>& result) {
        if (map.find(dimension) == map.cend())
            openDimension(dimension);
        map[dimension].containsExactTerm(term, result);
    }

    ~FuzzyMatch() {
        // Explicitely clearing the map
        map.clear();
    }

};


#endif //EDGEINDEXING_FUZZYMATCH_H
