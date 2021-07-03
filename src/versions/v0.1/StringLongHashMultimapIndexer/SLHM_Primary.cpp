/*
 * SLHM_Primary.cpp
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

#include "versions/v0.1/StringLongHashMultimapIndexer/SLHM_Primary.h"

SLHM_Primary::SLHM_Primary() : ordered_multimap{&compareUL_Int} {}

less_than_stringKey<std::vector<LONG_NUMERIC>>                   ltk1{};

struct secondary_memory_tmp {

};

void SLHM_Primary::store(std::string &elem, LONG_NUMERIC value) {
    Node<LONG_NUMERIC, std::pair<std::string, std::vector<LONG_NUMERIC>>> *hashKey = ordered_multimap.insertKey(hfunc(elem));
    if (hashKey->getSize() != 0) {
        for (std::pair<std::string, std::vector<LONG_NUMERIC>> &x : hashKey->overflowList) {
            if (x.first == elem) {
                x.second.emplace_back(value);
                return;
            }
        }
    }
    std::vector<LONG_NUMERIC> element;
    element.push_back(value);
    hashKey->add(elem, element);
}

void SLHM_Primary::serialize(FILE *hashing, FILE *values) {
    RBTree<LONG_NUMERIC, std::pair<std::string, std::vector<LONG_NUMERIC>>>::rbiterator it = ordered_multimap.iterator();
    LONG_NUMERIC offset = 0;
    while (it.hasNext()) {
        Node<LONG_NUMERIC, std::pair<std::string, std::vector<LONG_NUMERIC>>> *element = it.disposeWhileIterating();
        // A, Write Hashing for this bucket
        LONG_NUMERIC bucket = it.getCurrentK();
        fwrite(&bucket, sizeof(LONG_NUMERIC), 1, hashing);
        fwrite(&offset, sizeof(LONG_NUMERIC), 1, hashing);
        LONG_NUMERIC nElement = element->overflowList.size();

        // B. Sorting
        // Sorting the array by string elements, so that the strings may be searched in log time within the bucket
        std::sort(element->overflowList.begin(), element->overflowList.end(), ltk1);

        // Each element in the block is composed as so:
        // 1) number of strings associated to longs.
        //    the values are stored after the number of the elements...
        LONG_NUMERIC offsetsInBucketForKey = sizeof(LONG_NUMERIC);
        fwrite(&nElement, sizeof(LONG_NUMERIC), 1, values);

        // 2) offset of each string associated to long (see 3)
        ///   .., after the nElement offsets
        offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(nElement));

        // Then I serialize the values. Before doing that, I must evaluate which are the actual offsets that I have to use
        for (std::pair<std::string, std::vector<LONG_NUMERIC>>& keyValueAssociation : element->overflowList) {
            // For each pair, I write the current offset for the keyMultivalue association
            fwrite(&offsetsInBucketForKey, sizeof(LONG_NUMERIC), 1, values);
            offsetsInBucketForKey += (sizeof(LONG_NUMERIC)*(keyValueAssociation.second.size()+2)+keyValueAssociation.first.size()+1);
        }

        // 3) for each string, we have the size of the block associated to it
        //    such size is offsetToString + vecSize + [vector] + stirng.size+1
        for (std::pair<std::string, std::vector<LONG_NUMERIC>>& keyValueAssociation : element->overflowList) {
            LONG_NUMERIC stirngSize = keyValueAssociation.first.size()+1;

            // 1) string length
            fwrite(&stirngSize, sizeof(LONG_NUMERIC), 1, values);
            // 2) string
            fwrite(keyValueAssociation.first.c_str(), stirngSize, 1, values);

            // 3) vector size after string_length+sizeof(LONG_NUMERIC)
            LONG_NUMERIC size = keyValueAssociation.second.size();
            fwrite(&size, sizeof(LONG_NUMERIC), 1, values);

            // 4) vector
            // Writing the longs
            for (int i = 0; i<keyValueAssociation.second.size(); i++)
                fwrite(&keyValueAssociation.second[i], sizeof(LONG_NUMERIC), 1, values);

        }
        offset += offsetsInBucketForKey;

    }
    fclose(hashing);
    fclose(values);
}
