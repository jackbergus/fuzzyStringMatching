//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_GDELTARGUMENT_H
#define INCONSISTENCY_GDELTARGUMENT_H

#include <string>
#include "GDELTPlace.h"
#include "../../merging/SplitStringIterator.h"

struct GDELTArgument {
    std::string code, name, cameo_country_code, known_group_code, ethnic_code, religion1_code, religion2_code, type1, type2, type3;
    GDELTPlace place;

    void load(SplitStringIterator& ref);
    void loadPlace(SplitStringIterator& ref, bool isOldFormat);
};


#endif //INCONSISTENCY_GDELTARGUMENT_H
