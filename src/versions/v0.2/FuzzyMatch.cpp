/*
 * FuzzyMatch.cpp
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

 
#include <utility>

//
// Created by giacomo on 17/10/18.
//

#include "versions/v0.2/FuzzyMatch.h"

extern std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> fmatch_converter;

FuzzyMatch::FuzzyMatch(std::string directory) : baseDir{std::move(directory)} {
    if (baseDir[baseDir.size()-1] != '/') {
        baseDir += "/";
    }
    loaded = true;
}

void FuzzyMatch::load(std::string directory) {
    // Prevents from opening multiple indices and file descriptors using the same element.
    if (loaded) {
        map.clear();
        loaded = false;
    }
    baseDir = std::move(directory);
    if (baseDir[baseDir.size()-1] != '/') {
        baseDir += "/";
    }
    loaded = true;
}

void FuzzyMatch::openDimension(std::string &dimension) {
    map[dimension].open(baseDir+dimension+"_csvDir");
}

void FuzzyMatch::fuzzyMatch(std::string &dimension, double threshold, int topk, String &objectString,
                            TreeMultimap<double, LONG_NUMERIC> &result) {
    if (!loaded) {
        result.clear();
        return;
    }
    if (map.find(dimension) == map.cend())
        openDimension(dimension);
    map[dimension].fuzzyMatch(threshold, topk, objectString, result);
}

void FuzzyMatch::containsExactTerm(std::string &dimension, std::string &term, ArrayList<LONG_NUMERIC> &result) {
    if (map.find(dimension) == map.cend())
        openDimension(dimension);
    map[dimension].containsExactTerm(term, result);
}

FuzzyMatch::~FuzzyMatch() {
    // Explicitely clearing the map
    map.clear();
}
