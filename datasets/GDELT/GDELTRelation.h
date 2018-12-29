//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_GDELTRELATION_H
#define INCONSISTENCY_GDELTRELATION_H

#include <string>
#include "../../merging/SplitStringIterator.h"

struct GDELTRelation {
    std::string root_event, event_code, event_basecode, event_rootcode; // quad_class, goldestein
    // num mentions, num sources, num articles, tone
    std::string event_name;

    void load(SplitStringIterator& ref);
};


#endif //INCONSISTENCY_GDELTRELATION_H
