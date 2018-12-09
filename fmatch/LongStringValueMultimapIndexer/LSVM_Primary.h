//
// Created by giacomo on 25/09/18.
//

#include "../libfuzzymatch.h"

#ifndef EDGEINDEXING_LSVM_PRIMARY_H
#define EDGEINDEXING_LSVM_PRIMARY_H


/**
 * This class indicizes an HashMultimap<Long, std::string> into secondary memory, where the primary index is an array
 * from 0 to max_long, and the values file is just an array of array of strings.
 */
class LongStringValueMultimapIndexer_Primary {
    LONG_NUMERIC maxLong = 0;
    RBTree<LONG_NUMERIC, std::string> ordered_multimap;

public:
    LongStringValueMultimapIndexer_Primary();
    void store(LONG_NUMERIC id, std::string& element);
    void serialize(FILE* primaryIndex, FILE* values);
};

#endif //EDGEINDEXING_LSVM_PRIMARY_H
