/*
 * SLHM_Secondary.cpp
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
// Created by giacomo on 25/09/18.
//

#include <cstring>
#include <cstdio>
#include <functional>
#include "SLHM_Secondary.h"
#include "../LongStringValueMultimapIndexer/LSVM_Secondary.h"


void findStringndexOffset(char* a, char* b, int* res) {
    int cmp = strcmp(a+ sizeof(LONG_NUMERIC), b+ sizeof(LONG_NUMERIC));
    *res = cmp;
}

void SLHM_Secondary::open(std::string csvFile) {
    std::string vector = csvFile + "_vector.bin";
    std::string values = csvFile + "_values.bin";
    //printf("%s && %s\n", vector.c_str(), values.c_str());
    ///media/giacomo/OutputBlank/cout_exe/Weapon_csvDir/objectToMultipleStrings.csv_vector.bin
    pimarySparseIndex = (struct long_index_file*)(((char*)mmapFile(vector, &this->sizeVector, &fdVector)));
    primarySize = sizeVector / sizeof(struct long_index_file);
    element = ((char*)mmapFile(values, &this->sizeValues, &fdValues));
}

void *SLHM_Secondary::searchForId(std::string &toSearch) {
    LONG_NUMERIC hash = hashf(toSearch);
    struct long_index_file toSearchVehicle{};
    toSearchVehicle.id = hash;
    struct long_index_file* ptr = binVectorFixedSizeArray<struct long_index_file>(pimarySparseIndex, primarySize, &toSearchVehicle, &findLongIndexOffset);
    if (ptr == nullptr) return nullptr;
    LONG_NUMERIC* offsets = (LONG_NUMERIC*)(this->element+ptr->offset);
    LONG_NUMERIC n               = offsets[0];
    const LONG_NUMERIC* offsetPointer  = &offsets[1];
    LONG_NUMERIC toSerialize = toSearch.size()+1+sizeof(LONG_NUMERIC);
    const char*         bucketElements = (char*)offsets;//((char*)offsets)+((n+1)* sizeof(LONG_NUMERIC));
    char* mall = (char*)malloc(toSerialize);
    memset(mall, 0, toSerialize);
    strcpy(mall+ sizeof(LONG_NUMERIC), toSearch.c_str());
    void* toret = binVectorMutableSizeArray<char>(bucketElements, offsetPointer, n, mall, findStringndexOffset);
    toret = LONG_ARRAY_START(toret);
    free(mall);
    return toret;
}

void SLHM_Secondary::clos() {
    if (pimarySparseIndex != nullptr) {
        munmap(pimarySparseIndex, sizeVector);
        pimarySparseIndex = nullptr;
        close(fdVector);
        sizeVector = fdVector = 0;
    }

    if (element != nullptr) {
        munmap(element, sizeValues);
        element = nullptr;
        close(fdValues);
        sizeValues = fdValues = 0;
    }
}
