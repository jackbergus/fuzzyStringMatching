//
// Created by giacomo on 25/09/18.
//

#include "../libfuzzymatch.h"
#include <locale>
#include <codecvt>
#include <string>


#ifndef EDGEINDEXING_STTGSHMI_PRIMARY_H
#define EDGEINDEXING_STTGSHMI_PRIMARY_H

class StringToTwoGramSizeHashMultimapIndexer {
    std::hash<std::string> hfunc;
    RBTree<LONG_NUMERIC, std::pair<std::string, std::vector<std::pair<std::string, LONG_NUMERIC>>>> ordered_multimap;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
public:
    StringToTwoGramSizeHashMultimapIndexer();
    void store(std::string& elem, std::string& twogram, LONG_NUMERIC value);
    void serialize(FILE* hashing, FILE* values);
};

#endif //EDGEINDEXING_STTGSHMI_PRIMARY_H
