//
// Created by giacomo on 25/09/18.
//

#include "../libfuzzymatch.h"

#ifndef EDGEINDEXING_SLHM_SECONDARY_H
#define EDGEINDEXING_SLHM_SECONDARY_H

/**
 * Performs a comparison between the two keys
 * @param a
 * @param b
 * @param res
 */
void findStringndexOffset(char* a, char* b, int* res);

class SLHM_Secondary {
    int fdVector, fdValues;
    LONG_NUMERIC sizeVector, sizeValues;
    std::hash<std::string> hashf;

public:
    char*  element          = nullptr;
    struct long_index_file* pimarySparseIndex = nullptr;
    LONG_NUMERIC primarySize;

    void open(std::string csvFile);

    /**
     * Performs a binary search over the bucket index to search for the offset of the associated string
     * @param toSearch      element to be searched within the index
     * @return              pointer to the
     */
    void* searchForId(std::string& toSearch);

    void clos();
};

#define OFFSET_STRING_SIZE(offset)  (*((LONG_NUMERIC*)(offset)))

#define STRING(offset)              ((char*)offset)+(sizeof(LONG_NUMERIC))

#define LONG_ARRAY_START(offset)    ((offset == nullptr) ? nullptr : ((char*)(STRING(offset)+OFFSET_STRING_SIZE(offset))))

#define LONG_ARRAY_SIZE(offset)          ((offset == nullptr) ? 0 : OFFSET_STRING_SIZE((offset)))

#define LONG_ARRAY_ELEMENT(offset)       ((LONG_NUMERIC*)((offset == nullptr) ? nullptr : ((LONG_NUMERIC*)(((char*)(offset))+sizeof(LONG_NUMERIC)))))

#endif //EDGEINDEXING_SLHM_SECONDARY_H
