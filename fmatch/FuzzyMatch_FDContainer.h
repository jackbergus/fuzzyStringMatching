/*
 * FuzzyMatch_FDContainer.h
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2018 - Giacomo Bergami
 *
 * fuzzyStringMatching is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * fuzzyStringMatching is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fuzzyStringMatching. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 26/09/18.
//

#ifndef EDGEINDEXING_FUZZYMATCH_FDCONTAINER_H
#define EDGEINDEXING_FUZZYMATCH_FDCONTAINER_H

#include "libfuzzymatch.h"

/**
 * This class contains all the secondary memory access points. Furthermore, by closing this class, all the
 * memory mapped areas will be disposed automatically
 */
class FuzzyMatch_FDContainer {
    SLHM_Secondary objectGramSize, twogramAndStringToMultiplicity, gramToObjects;
    LSVM_Secondary objectToMultipleStrings;
    TreeMultimap<double, LONG_NUMERIC> localTree;
    TreeMultimap<double, LONG_NUMERIC>::reverse_iterator iterator;
    bool opened = false;

    /**
     * This function either uses the pre-computed index to get the number of 2grams and their frequency, or
     * uses compareStringHashMap back
     *
     * @param associatedToElement  String to be associated to their 2grams and their frequency
     * @param map                  Map where the association between the twograms and their frequency is stored
     */
    void getTwoGramAndString(std::string& argument, HashMap<String, LONG_NUMERIC>& map);

    /**
     * Retrieves the elements from the fuzzy match by
     * @param k             Candidates to be scored
     * @param m1            Multiplicity values for each gram associated to the element to be computed
     * @param size          Gram size associated to the current term
     * @param threshold     If set to a negative value, it means that there is no threshold
     * @param pollMap       Map where to store the final results to be returned
     */
    void rankCollectionOf(HashSet<LONG_NUMERIC>& k, HashMap<String, LONG_NUMERIC>& m1,
                          unsigned long size, double threshold, PollMap<double, LONG_NUMERIC>& pollMap);

public:
    SLHM_Secondary termToObjects;

    FuzzyMatch_FDContainer();
    void open(std::string rootDir);
    void fuzzyMatch(double threshold, int topk, String& objectStriinternalMapngs, TreeMultimap<double, LONG_NUMERIC>& result);
    void fuzzyMatch(double threshold, int topk, String objectStrings);
    bool hasCurrent();
    double getCurrentKey();
    LONG_NUMERIC getCurrentValue();
    bool next();

    /**
     *
     * @param term
     * @param elements  ObjectId of the elements containing exactely term
     */
    void containsExactTerm(std::string& term, ArrayList<LONG_NUMERIC>& elements);

    /**
     * This function was created for debugging purposes
     * @param id
     * @return
     */
    ArrayList<String> printCandidateId(LONG_NUMERIC id);

    ~FuzzyMatch_FDContainer();
};


#endif //EDGEINDEXING_FUZZYMATCH_FDCONTAINER_H
