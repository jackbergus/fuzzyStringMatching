/*
 * LSVM_Secondary.cpp
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

#include "versions/v0.1/LongStringValueMultimapIndexer/LSVM_Secondary.h"

void findLongIndexOffset(struct long_index_file* a, struct long_index_file* b, int* res) {
    if (a->id < b->id) *res = -1;
    else if (a->id > b->id) *res = 1;
    else *res=0;
}

void LSVM_Secondary::open(std::string csvFile) {
    std::string vector = csvFile + "_vector.bin";
    std::string values = csvFile + "_values.bin";
    ///media/giacomo/OutputBlank/cout_exe/Weapon_csvDir/objectToMultipleStrings.csv_vector.bin

    pimarySparseIndex = (struct long_index_file*)(((char*) yaucl::fs::mmapFile(vector, &this->sizeVector, &fdVector)));
    primarySize = sizeVector / sizeof(struct long_index_file);

    element = ((char*) yaucl::fs::mmapFile(values, &this->sizeValues, &fdValues));
}

char* LSVM_Secondary::searchForId(LONG_NUMERIC toSearch) {
    struct long_index_file toSearchVehicle{};
    toSearchVehicle.id = toSearch;
    struct long_index_file* ptr = binVectorFixedSizeArray<struct long_index_file>(pimarySparseIndex, primarySize, &toSearchVehicle, &findLongIndexOffset);
    return ptr == nullptr ? nullptr : this->element + ptr->offset;
}

void LSVM_Secondary::clos() {
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
