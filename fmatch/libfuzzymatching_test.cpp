//
// Created by giacomo on 27/09/18.
//

#include "libfuzzymatch.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <unordered_set>

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