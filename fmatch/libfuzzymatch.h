//
// Created by giacomo on 25/09/18.
//

#ifndef EDGEINDEXING_FMATCH_H
#define EDGEINDEXING_FMATCH_H

#include <cstdio>
#include <unistd.h>
#include <string>

#include "../fromJava/classes.h"
#include "../numeric/compares.h"
#include "../serializers/commons/structure.h"
#include "../rbtree/rbtree.h"
#include "../serializers/commons/structure.h"
#include "../serializers/utils/mmapFile.h"
#include "../algorithms/binsearch.h"
#include "PollMap.h"

/**
 * Data structure used for comparing pairs in primary memory where the fist element is a string. Please note that
 * only the fist parameter (the string) will be compared.
 *
 * @tparam T    Type of the data ignored during the comparison
 */
template <typename T> struct less_than_stringKey
{
    inline bool operator() (const std::pair<std::string, T>& struct1, const std::pair<std::string, T>& struct2)
    {
        return (struct1.first < struct2.first);
    }
};

/**
 * Pimary indexing data structure
 */
struct long_index_file {
    /**
     * Id of the element or bucket's hash
     */
    LONG_NUMERIC id;

    /**
     * Offset to the current bucket or element id
     */
    LONG_NUMERIC offset;
};

#include "LongStringValueMultimapIndexer/LSVM_Primary.h"
#include "StringLongHashMultimapIndexer/SLHM_Primary.h"
#include "StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.h"
#include "LongStringValueMultimapIndexer/LSVM_Secondary.h"
#include "StringLongHashMultimapIndexer/SLHM_Secondary.h"
#include "StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Secondary.h"

#include "FuzzyMatch_FDContainer.h"

#endif //EDGEINDEXING_FMATCH_H
