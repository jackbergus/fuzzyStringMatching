/*
 * libfuzzymatching_test.cpp
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
// Created by giacomo on 27/09/18.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_set>
#include <unordered_map>
#include "FuzzyMatch_FDContainer.h"
#include "../serializers/commons/structure.h"

std::string baseDir;
std::unordered_map<std::string, FuzzyMatch_FDContainer> map;

void openDirectory(char* bd) {
    baseDir = std::string{bd};
    if (baseDir[baseDir.size()-1] != '/') {
        baseDir += "/";
    }
}

// private
void openDimension(std::string& dim) {
    map[dim].open(baseDir+dim+"_csvDir");
}

void fuzzyMatch(std::string& dim, double threshold, int topk, std::string& objectStrings) {
    openDimension(dim);
    //std::string objectStrings{term};
    map[dim].fuzzyMatch(threshold, topk, objectStrings);
}

bool hasCurrent(char* dim) {
    std::string dimension{dim};
    return map[dimension].hasCurrent();
}

void closeDimensioN(char* dim) {
    std::string dimension{dim};
    map.erase(dimension);
}

double getCurrentKey(char* dim) {
    std::string dimension{dim};
    return map[dimension].getCurrentKey();
}

LONG_NUMERIC getCurrentValue(char* dim) {
    std::string dimension{dim};
    return map[dimension].getCurrentValue();
}

bool next(char* dim) {
    std::string dimension{dim};
    return map[dimension].next();
}

void closeDirectory() {
    map.clear();
}

int main() {
#define WEAPON "Weapon"
    openDirectory("/media/giacomo/Biggus/project_dir/data/hierarchies");
    std::string weap{WEAPON};
    std::string stam{"surface to air missile"};
    openDimension(weap);
    /*void* ls = map[weap].termToObjects.searchForId(stam);
    if (ls != nullptr) {
        LONG_NUMERIC    n = LONG_ARRAY_SIZE(ls);
        LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(ls);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::cout << std::to_string(ptr[i]) << std::endl;
        }
    }*/
    fuzzyMatch(weap, 0.6, 1, stam);
    double prevScore = 1;
    int counter = 1;
    while (hasCurrent(WEAPON)) {
        prevScore = getCurrentKey(WEAPON);
        if (prevScore < 1) break;
        LONG_NUMERIC element = getCurrentValue(WEAPON);
        std::cout << prevScore << " @ " << element;
        next(WEAPON);
    }
    closeDimensioN(WEAPON);
    closeDirectory();
}
