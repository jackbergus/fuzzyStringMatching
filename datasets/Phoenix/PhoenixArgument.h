//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_PHOENIXARGUMENT_H
#define INCONSISTENCY_PHOENIXARGUMENT_H

#include <string>
#include "../../merging/SplitStringIterator.h"
#include "../../merging/CSVIterator.h"

struct PhoenixArgument {
    //std::string source;
    std::string root;
    std::string agent;
    std::string others;

    void load(CSVIterator &it);
};


#endif //INCONSISTENCY_NELLARGUMENT_H
