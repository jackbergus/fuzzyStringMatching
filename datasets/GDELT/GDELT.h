//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_GDELT_H
#define INCONSISTENCY_GDELT_H

#include <string>
#include "GDELTTime.h"
#include "GDELTArgument.h"
#include "GDELTRelation.h"

struct GDELT {
    std::string id;
    GDELTArgument src, dst;
    GDELTRelation relation;
    GDELTTime time;
    GDELTPlace place;

    void load(SplitStringIterator& ref, bool isOldFormat);

    friend std::ostream &operator<<(std::ostream &os, const GDELT &icews);
};


#endif //INCONSISTENCY_GDELT_H
