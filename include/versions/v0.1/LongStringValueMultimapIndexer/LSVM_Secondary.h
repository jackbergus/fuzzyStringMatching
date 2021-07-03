/*
 * LSVM_Secondary.h
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

#include "versions/v0.1/libfuzzymatch.h"
#include <serializers/commons/structure.h>
#include <serializers/utils/mmapFile.h>
#include <algorithms/binsearch.h>


#ifndef EDGEINDEXING_LSVMI_SECONDARY_H
#define EDGEINDEXING_LSVMI_SECONDARY_H

/**
 * Comparator for searching long values in the primary index
 * @param a
 * @param b
 * @param res
 */
void findLongIndexOffset(struct long_index_file* a, struct long_index_file* b, int* res);

class LSVM_Secondary {
    LONG_NUMERIC primarySize;
    int fdVector, fdValues;
    LONG_NUMERIC sizeVector, sizeValues;

public:
    char*  element          = nullptr;
    struct long_index_file* pimarySparseIndex = nullptr;

    void open(std::string csvFile);

/**
     * Performs a binary search over the sparse primary index to search for the offset of the associated id.
     * @param toSearch      element to be searched within the index
     * @return              the pointer to the strings associated to the id. If toSearch was not found, a null pointer is
     *                      returned instead
     */
    char* searchForId(LONG_NUMERIC toSearch);

    void clos();
};

/**
 * Checks whether the data structure g contains the id ll
 */
#define ID_OFFSET(g, ll)                            ((g).searchForId(ll)))

/**
 * Checks whether the data structure g contains the id ll
 */
#define CONTAINS_ID(g, ll)                          ((ID_OFFSET(g, ll))>0)

/**
 * Returns the number of the associated strings
 * ALERT: in order to use this macro, you have to be sure that there are any elements
 */
#define UNSAFE_ID_NSTIRNGS(idoffset)             (*((LONG_NUMERIC*) (idoffset)))

/**
 * Returns the offset of the i-th string
 * ALERT: in order to use this macro, you have to be sure that there are any elements
 */
#define UNSAFE_ID_ITH_STRINGOFFSET(idoffset, i)  (*((LONG_NUMERIC*)((((char*)idoffset) + sizeof(LONG_NUMERIC) * ((i)+1)))))


#define UNSAGE_ID_ITH_STRING(idoffset, i)        ((char*)((((char*)idoffset)) + UNSAFE_ID_ITH_STRINGOFFSET(idoffset, i)))

#endif //EDGEINDEXING_LSVM_SECONDARY_H
