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


/**
 * Performs the fuzzy match over the binary indices optimizing the fuzzy matching access. Requires that the indices
 * are stored in primary memory and are with a non-mutable representation.
 */
class FuzzyMatch {

    bool loaded;
    std::string baseDir;
    std::unordered_map<std::string, FuzzyMatch_FDContainer> map;
    void openDimension(std::string& dimension);
    void closeDimension(std::string& dimension) {
        map.erase(dimension);
    }

public:
    /**
     * Straightforwardly associates the directory name at the creation process
     * @param directory
     */
    explicit FuzzyMatch(std::string directory);

    /**
     * Delaying the
     * @return
     */
    FuzzyMatch() = default;


    void load(std::string directory);

    /**
     * Performs the fuzzy matching of a term on top of a hierarchy. No fuzzy match will be performed if the object is
     * not associated to a folder.
     *
     * @param dimension
     * @param threshold
     * @param topk
     * @param objectString
     * @param result
     */
    void fuzzyMatch(std::string& dimension, double threshold, int topk, String& objectString,
                    TreeMultimap<double, LONG_NUMERIC> &result);

    void containsExactTerm(std::string& dimension, std::string& term, ArrayList<LONG_NUMERIC>& result);

    ~FuzzyMatch();

};


#endif //EDGEINDEXING_FUZZYMATCH_H
