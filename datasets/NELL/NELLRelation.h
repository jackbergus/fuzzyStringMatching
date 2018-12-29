//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_NELLRELATION_H
#define INCONSISTENCY_NELLRELATION_H

#include <string>
#include "../../merging/SplitStringIterator.h"

struct NELLRelation {
    std::string type;
    double probability;
    void load(SplitStringIterator& ref);
};


#endif //INCONSISTENCY_NELLRELATION_H
