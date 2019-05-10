/*
 * FuzzyMatch_FDContainer.cpp
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

#include "FuzzyMatch_FDContainer.h"
#include <sstream>
#include <cstdio>

//Credits to http://www.catalysoft.com/articles/StrikeAMatch.html
void compareString_letterPairs(String& str, ArrayList<String>& pairs) {
    unsigned long numPairs = str.length()-1;
    if (!numPairs) {
        pairs.emplace_back(str);
    }
    if (numPairs < 0)
        numPairs = 0;
    for (unsigned long i = 0; i<numPairs; i++) {
        pairs.emplace_back(str.substr(i, 2));
    }
}


std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> fmatch_converter;

//Credits to http://www.catalysoft.com/articles/StrikeAMatch.html
ArrayList<String> compareString_wordLetterPairs(String& strMixed) {
    std::wstring wide = fmatch_converter.from_bytes(strMixed.c_str());
    std::transform(wide.begin(), wide.end(), wide.begin(), std::towlower);
    std::string str = fmatch_converter.to_bytes(wide);
    std::istringstream iss(str);
    ArrayList<String> allPairs{};
    for(std::string s; iss >> s; )
        compareString_letterPairs(s, allPairs);
    return allPairs;
}

void compareStringHashMap_Internal(String& str, HashMap<String, LONG_NUMERIC >& retMap, ArrayList<LONG_NUMERIC>& retList) {
    unsigned long numPairs = str.size() - 1;
    if (numPairs == 0) {
        retMap[str] = 0;
        retList.emplace_back(1);
    } else {
        if (numPairs < 0)
            numPairs = 0;
        int singleGrams = 0;
        for (unsigned long i= 0; i< numPairs; i++) {
            String s = str.substr(i, 2);
            auto pos = retMap.find(s);
            if (pos == retMap.cend()) {
                retMap[s] = singleGrams++;
                retList.emplace_back(1);
            } else {
                retList[pos->second]++;
            }
        }
    }
}

void compareStringHashMap(String& strMixed, HashMap<String, LONG_NUMERIC>& retMap, ArrayList<LONG_NUMERIC>& retList) {
    std::wstring wide = fmatch_converter.from_bytes(strMixed.c_str());
    std::transform(wide.begin(), wide.end(), wide.begin(), std::towlower);
    std::string str = fmatch_converter.to_bytes(wide);
    std::istringstream iss(str);
    for(std::string s; iss >> s; )
        compareStringHashMap_Internal(s, retMap, retList);
    // Sanitizing
    for (auto it = retMap.begin(); it != retMap.cend(); it++) {
        it->second = retList[it->second];
    }
}

void compareStringHashMap(String& str, HashMap<String, LONG_NUMERIC>& retMap) {
    ArrayList<LONG_NUMERIC> retList{};
    compareStringHashMap(str, retMap, retList);
}


void FuzzyMatch_FDContainer::getTwoGramAndString(std::string &argument, HashMap<String, LONG_NUMERIC> &map) {
    void *ls = twogramAndStringToMultiplicity.searchForId(argument);
    if (ls != nullptr) {
        // if the value is stored, then I use the hashmap
        LONG_NUMERIC    n = CHARLONG_ARRAY_SIZE(ls);
        struct internalMap* ptr = CHARLONG_ARRAY_ELEMENT(ls);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::wstring ws(ptr[i].map, 2);
            std::string str(ws.begin(), ws.end());
            map[str] = ptr[i].value;
        }
    } else {
        // if not, recompute everything and put it in the map
        compareStringHashMap(argument, map);
    }
}

void FuzzyMatch_FDContainer::rankCollectionOf(HashSet<LONG_NUMERIC> &k, HashMap<String, LONG_NUMERIC> &m1,
                                              unsigned long size, double threshold,
                                              PollMap<double, LONG_NUMERIC> &pollMap) {
    for (LONG_NUMERIC element : k) {
        char* elementStringOffset = objectToMultipleStrings.searchForId(element);
        if (elementStringOffset != nullptr) {
            // getting the number of strings associated
            LONG_NUMERIC n = UNSAFE_ID_NSTIRNGS(elementStringOffset);
            // Iterating over each stored string
            for (LONG_NUMERIC i = 0; i<n; i++) {
                std::string associatedToElement{UNSAGE_ID_ITH_STRING(elementStringOffset, i)};
                HashMap<String, LONG_NUMERIC> m2;

                getTwoGramAndString(associatedToElement, m2);

                // Set intersection of the keys. Intersection while iterating
                double score = 0;
                double e = 0;
                HashMap<String, LONG_NUMERIC>* lesser = m1.size() < m2.size() ? &m1 : &m2;
                HashMap<String, LONG_NUMERIC>* greater = m1.size() < m2.size() ? &m2 : &m1;
                for (auto it = lesser->begin(); it != lesser->cend(); it++) {
                    auto it2 = greater->find(it->first);
                    if (it2 != greater->cend()) {
                        // key is in both elements
                        e += std::min(it->second, it2->second)*1.0;
                    }
                }
                // no memoization
                void *ls = objectGramSize.searchForId(associatedToElement);
                double leftCount = 0;
                if (ls == nullptr) {
                    HashMap<String, LONG_NUMERIC> retMap;
                    ArrayList<LONG_NUMERIC> retList;
                    compareStringHashMap(associatedToElement, retMap, retList);
                    for (LONG_NUMERIC& x : retList) leftCount+=x;
                    score = (e * 2.0) / ((leftCount + size)*1.0);
                } else {
                    LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(ls);
                    score = (e * 2.0) / ((ptr[0] + size)*1.0);
                }

                if (threshold >= 0 && score >= threshold) {
                    pollMap.add(score, element);
                }
            }
        }
    }
}

void FuzzyMatch_FDContainer::open(std::string rootDir) {
    if (opened) return; // not opening twice
    localTree.clear();
    iterator = localTree.rend();
    gramToObjects.open(rootDir+"/gramToObjects.csv");
    objectGramSize.open(rootDir+"/objectGramSize.csv");
    objectToMultipleStrings.open(rootDir+"/objectToMultipleStrings.csv");
    twogramAndStringToMultiplicity.open(rootDir+ "/twogramAndStringToMultiplicity.csv");
    termToObjects.open(rootDir+"/termToObjects.csv");
    opened = true;
}

void FuzzyMatch_FDContainer::fuzzyMatch(double threshold, int topk, String& objectString,
                                        TreeMultimap<double, LONG_NUMERIC> &result) {
    PollMap<double, LONG_NUMERIC> toReturnTop{topk};
    ArrayList<String> objectGrams = compareString_wordLetterPairs(objectString);
    HashSet<LONG_NUMERIC> candidates{};
    HashMap<String, LONG_NUMERIC> m1;

    // obtain all the objects that are assoicated to the gram that are within the current objectString in objectStrings
    for (String& gram : objectGrams) {
        void* gramPtr = gramToObjects.searchForId(gram);
        if (gramPtr != nullptr) {
            LONG_NUMERIC    n = LONG_ARRAY_SIZE(gramPtr);
            LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(gramPtr);
            for (LONG_NUMERIC i = 0; i<n; i++) {
                candidates.insert(ptr[i]);
            }
        }
    }

    // return the number of the occurences of the twoGrams within the current string
    compareStringHashMap(objectString, m1);
    LONG_NUMERIC ogSize = 0;
    for (auto it = m1.begin(); it != m1.cend(); it++) ogSize += it->second;

    // Rank the similarity between all the candidates
    rankCollectionOf(candidates, m1, ogSize, threshold, toReturnTop);

    // providing the final result
    toReturnTop.getPoll(result);
}

ArrayList<String> FuzzyMatch_FDContainer::printCandidateId(LONG_NUMERIC id) {
    char* offset = objectToMultipleStrings.searchForId(id);
    ArrayList<String> elements;
    if (offset != nullptr) {
        // getting the number of strings associated
        LONG_NUMERIC n = UNSAFE_ID_NSTIRNGS(offset);
        elements.reserve(n);
        // Iterating over each stored string
        for (LONG_NUMERIC i = 0; i<n; i++) {
            elements.push_back(UNSAGE_ID_ITH_STRING(offset, i));
        }
    }
    return elements;
}

FuzzyMatch_FDContainer::~FuzzyMatch_FDContainer() {
    this->objectGramSize.clos();
    this->twogramAndStringToMultiplicity.clos();
    this->objectToMultipleStrings.clos();
    this->gramToObjects.clos();
    this->termToObjects.clos();
    opened = false;
}

void FuzzyMatch_FDContainer::fuzzyMatch(double threshold, int topk, String objectStrings) {
    localTree.clear();
    fuzzyMatch(threshold, topk, objectStrings, localTree);
    iterator = localTree.rbegin();
}

void FuzzyMatch_FDContainer::containsExactTerm(std::string &term, ArrayList<LONG_NUMERIC> &elements) {
    void* gramPtr = gramToObjects.searchForId(term);
    if (gramPtr != nullptr) {
        LONG_NUMERIC    n = LONG_ARRAY_SIZE(gramPtr);
        LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(gramPtr);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            elements.emplace_back(ptr[i]);
        }
    } else {
        elements.clear();
    }
}

bool FuzzyMatch_FDContainer::hasCurrent() {
    return iterator != localTree.rend();
}

double FuzzyMatch_FDContainer::getCurrentKey() {
    return iterator == localTree.rend() ? -1 : iterator->first;
}

LONG_NUMERIC FuzzyMatch_FDContainer::getCurrentValue() {
    return iterator == localTree.rend() ? 0 : iterator->second;
}

bool FuzzyMatch_FDContainer::next() {
    return ++iterator != localTree.rend();
}

FuzzyMatch_FDContainer::FuzzyMatch_FDContainer() {
    this->opened = false;
}
