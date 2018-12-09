//
// Created by giacomo on 17/10/18.
//

#include "FuzzyMatch.h"

extern std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> fmatch_converter;

FuzzyMatch::FuzzyMatch(std::string directory) : baseDir{directory} {
    if (baseDir[baseDir.size()-1] != '/') {
        baseDir += "/";
    }
}

void FuzzyMatch::openDimension(std::string &dimension) {
    map[dimension].open(baseDir+dimension+"_csvDir");
}
