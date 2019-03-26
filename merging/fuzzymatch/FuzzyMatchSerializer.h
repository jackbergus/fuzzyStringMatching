//
// Created by giacomo on 25/03/19.
//

#ifndef INCONSISTENCY_FUZZYMATCHSERIALIZER_H
#define INCONSISTENCY_FUZZYMATCHSERIALIZER_H


#include "../../serializers/commons/structure.h"
#include "../../fmatch/StringLongHashMultimapIndexer/SLHM_Primary.h"
#include "../../fmatch/LongStringValueMultimapIndexer/LSVM_Primary.h"
#include "../../fmatch/StringToTwoGramSizeHashMultimapIndexer/STTGSHM_Primary.h"
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

void compareStringHashmap1(std::string& str, std::unordered_map<std::string,LONG_NUMERIC>& map, std::vector<LONG_NUMERIC>& vec);

void compareStringHashmap2(std::string& string, std::unordered_map<std::string,LONG_NUMERIC>& map, std::vector<LONG_NUMERIC>& vec);

/**
 * This class creates the fuzzy string matching indices in primary memory, so that they might be later on serialized
 * in secondary memory. Even though such indices might fit per se in primary memory, it is impossible to load all the
 * data in primary memory. Therefore, this indexing part only copes with some data part.
 *
 * The serialized data should be accessed and queried using the FuzzyMatch class.
 */
class FuzzyMatchSerializer {

    /**
     * This method creates all the indices in primary memory
     *
     * @param string                        Preferred string associated to the object
     * @param id                            Object id (eg. an offset)
     * @param associatedOtherStrings        Other secondary strings associated to the preferred object
     */
    void addGramsToMap(std::string& string, LONG_NUMERIC id, std::vector<std::string>& associatedOtherStrings) {
        if (string.empty()) return;

        termObject.store(string, id);
        objectMultipleStirngs.store(id, string);
        for (std::string& x : associatedOtherStrings)
            objectMultipleStirngs.store(id, x);

        std::unordered_map<std::string,LONG_NUMERIC> cp;
        std::vector<LONG_NUMERIC> vec;

        compareStringHashmap2(string, cp, vec);
        LONG_NUMERIC sum = 0;
        for (LONG_NUMERIC& j : vec) {
            sum += j;
        }
        objectGramSize.store(string, sum);

        for (std::unordered_map<std::string,LONG_NUMERIC>::iterator begin = cp.begin(), end = cp.end(); begin!=end; begin++) {
            std::string x = begin->first;
            twogramAndStringMultiplicity.store(string, x, begin->second);
            gramToObject.store(x, id);
        }
    }

    /**
     * This method serializes the indices as several secondary memory files.
     * If it is a file, it will try to delete the file first.
     * If the current path does not exists, it will try to create the folder (mkdirs)
     *
     * @param path
     */
    void serialize(std::string path);

private:
    SLHM_Primary gramToObject, objectGramSize, termObject;
    LongStringValueMultimapIndexer_Primary objectMultipleStirngs;
    StringToTwoGramSizeHashMultimapIndexer twogramAndStringMultiplicity;

};


#endif //INCONSISTENCY_FUZZYMATCHSERIALIZER_H
