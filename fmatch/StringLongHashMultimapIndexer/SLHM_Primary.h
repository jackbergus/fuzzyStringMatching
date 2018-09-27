//
// Created by giacomo on 25/09/18.
//

#include "../libfuzzymatch.h"

#ifndef EDGEINDEXING_SLHMI_PRIMARY_H
#define EDGEINDEXING_SLHMI_PRIMARY_H

/**
 * This class allows to serialize a HashMultimap<std::string, long> as two indices: a primary index for the hashes
 * associated to the keys (the strings), and each bucket is string ordered, and contains an array of pairs of string
 * (the actual key) and values.
 */
class SLHM_Primary {
    std::hash<std::string> hfunc;
    RBTree<LONG_NUMERIC, std::pair<std::string, std::vector<LONG_NUMERIC>>> ordered_multimap;

public:
    SLHM_Primary();

    void store(std::string& elem, LONG_NUMERIC value);

    void serialize(FILE* hashing, FILE* values);
};
//// </class>


#endif //EDGEINDEXING_SLHMI_PRIMARY_H
