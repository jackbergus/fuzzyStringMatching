/*
 * csv_serializer.cpp
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
// Created by giacomo on 24/09/18.
//


#include <serializers/commons/structure.h>
#include "versions/v0.1/libfuzzymatch.h"
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>

#include <csv.h>
#include "versions/v0.1/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.h"

void serializeStringLongHMM(std::string csv) {
    std::string vector = csv + "_vector.bin";
    std::string values = csv + "_values.bin";
    FILE* idx = fopen(vector.c_str(), "w");
    FILE* val = fopen(values.c_str(), "w");
    io::CSVReader<2, io::trim_chars<' '>, io::no_quote_escape<'\t'>> gtofnCSV(csv);
    std::string string; LONG_NUMERIC lval;
    SLHM_Primary idxex{};
    while(gtofnCSV.read_row(string, lval)){
        idxex.store(string, lval);
    }
    idxex.serialize(idx, val);
}

void serializeLongStringHMM(std::string csv) {
    std::string vector = csv + "_vector.bin";
    std::string values = csv + "_values.bin";
    FILE* idx = fopen(vector.c_str(), "w");
    FILE* val = fopen(values.c_str(), "w");
    io::CSVReader<2, io::trim_chars<' '>, io::no_quote_escape<'\t'>> gtofnCSV(csv);
    std::string string; LONG_NUMERIC lval;
    LongStringValueMultimapIndexer_Primary idxex{};
    while(gtofnCSV.read_row(lval, string)){
        idxex.store(lval, string);
    }
    idxex.serialize(idx, val);
}

void serializeStringTwoGramsSize(std::string csv) {
    std::string vector = csv + "_vector.bin";
    std::string values = csv + "_values.bin";
    FILE* idx = fopen(vector.c_str(), "w");
    FILE* val = fopen(values.c_str(), "w");
    io::CSVReader<3, io::trim_chars<' '>, io::no_quote_escape<'\t'>> gtofnCSV(csv);
    std::string string; std::string twogram; LONG_NUMERIC lval;
    StringToTwoGramSizeHashMultimapIndexer idxex{};
    while(gtofnCSV.read_row(string, twogram, lval)){
        idxex.store(string, twogram, lval);
    }
    idxex.serialize(idx, val);
}

/**
 * @param folder Folder containing the csv files that should be converted into a binary format
 */
void serializeCSVInFolder(std::string& folder) {
    std::string gramToObjectsFileName = folder + "/gramToObjects.csv";
    std::cout << gramToObjectsFileName << "... ";
    std::cout.flush();
    serializeStringLongHMM(gramToObjectsFileName);
    std::cout << "done" << std::endl;

    std::string objectGramSizeFileName = folder + "/objectGramSize.csv";
    std::cout << objectGramSizeFileName << "... ";
    std::cout.flush();
    serializeStringLongHMM(objectGramSizeFileName);
    std::cout << "done" << std::endl;

    std::string termToObjectsFileName = folder + "/termToObjects.csv";
    std::cout << termToObjectsFileName << "... ";
    std::cout.flush();
    serializeStringLongHMM(termToObjectsFileName);
    std::cout << "done" << std::endl;

    std::string objectToMultipleStringsFileName = folder + "/objectToMultipleStrings.csv";
    std::cout << objectToMultipleStringsFileName << "... ";
    std::cout.flush();
    serializeLongStringHMM(objectToMultipleStringsFileName);
    std::cout << "done" << std::endl;

    std::string serializeStringTwoGramsSizeFileName = folder + "/twogramAndStringToMultiplicity.csv";
    std::cout << serializeStringTwoGramsSizeFileName << "... ";
    std::cout.flush();
    serializeStringTwoGramsSize(serializeStringTwoGramsSizeFileName);
    std::cout << "done" << std::endl;
}

#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>

extern "C" {
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
}

#define CURRENT_FOLDER  "/media/giacomo/Biggus/project_dir/data/hierarchies"

int main(void) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(CURRENT_FOLDER)))
        exit(0);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, CURRENT_FOLDER) == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", CURRENT_FOLDER, entry->d_name);
            std::cout << path << std::endl;
            std::string stringa{path};
            serializeCSVInFolder(stringa);
            //printf("%*s[%s]\n", CURRENT_FOLDER, "", entry->d_name);
            //listdir(path, CURRENT_FOLDER + 2);
        } else {
            //printf("%*s- %s\n", CURRENT_FOLDER, "", entry->d_name);
        }
    }
    closedir(dir);

    //std::string stringa = "Weapon_csvDir";
    //std::string test1 = stringa + "/objectToMultipleStrings.csv";

    //serializeCSVInFolder(stringa);
    // --> How to search for longs

    /*
    // Loading the file associated to the hierarchy
    LSVM_Secondary file{test1};

    // Check if the offset exists
    char* offset = file.searchForId(524519L);
    if (offset != nullptr) {
        // getting the number of strings associated
        LONG_NUMERIC n = UNSAFE_ID_NSTIRNGS(offset);
        // Iterating over each stored string
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::cout << UNSAGE_ID_ITH_STRING(offset, i) << std::endl;
        }
    }
    file.clos();
    */

    /*
    std::string test2 = stringa + "/gramToObjects.csv";
    SLHM_Secondary file2{test2};
    std::string argument = "ar";
    void *ls = file2.searchForId(argument);
    if (ls != nullptr) {
        LONG_NUMERIC    n = LONG_ARRAY_SIZE(ls);
        LONG_NUMERIC* ptr = LONG_ARRAY_ELEMENT(ls);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::cout << std::to_string(ptr[i]) << std::endl;
        }
    }
    */


  /*  std::string test3 = stringa + "/twogramAndStringToMultiplicity.csv";
    SLHM_Secondary file3;
    file3.open(test3);
    std::string argument = "missile";*/
    /*// Example: recreating the csv. Extreme debugging
    for (LONG_NUMERIC i = 0; i<file3.primarySize; i++) {
        std::cout << "bucket = " << std::to_string(file3.pimarySparseIndex[i].id) << std::endl;
        char* offset = file3.element+file3.pimarySparseIndex[i].offset;
        // TODO: std::cout << "\t string = " << STRING(offset) << std::endl;
        LONG_NUMERIC    n = CHARLONG_ARRAY_SIZE(offset);
        struct internalMap* ptr = CHARLONG_ARRAY_ELEMENT(offset);
        for (LONG_NUMERIC j = 0; j<n; j++) {
            char element[3];
            memset(element, 0, 3);
            memcpy(element, ptr[j].map, 2);
            std::cout << "\t\t" << element << " -> " << std::to_string(ptr[j].value) << std::endl;
        }
    }
    file3.clos();*/

/*
    void *ls = file3.searchForId(argument);
    if (ls != nullptr) {
        LONG_NUMERIC    n = CHARLONG_ARRAY_SIZE(ls);
        struct internalMap* ptr = CHARLONG_ARRAY_ELEMENT(ls);
        for (LONG_NUMERIC i = 0; i<n; i++) {
            std::wstring ws(ptr[i].map, 2);
            std::string str(ws.begin(), ws.end());
            std::cout << str << " -> " << std::to_string(ptr[i].value) << std::endl;
        }
    }
    file3.clos();*/
}
