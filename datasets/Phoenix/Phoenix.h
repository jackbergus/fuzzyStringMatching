//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_PHOENIX_H
#define INCONSISTENCY_PHOENIX_H

#include <string>

#include "PhoenixArgument.h"
#include "PhoenixTime.h"
#include "PhoenixPlace.h"
#include "../../merging/CSVIterator.h"

struct Phoenix {
    std::string eid;
    PhoenixTime time;
    PhoenixArgument src, dst;
    std::string event_type;
    //std::string event_root_type, quadclass, goldstein;
    std::string joined_issues;
    PhoenixPlace place;

    void load(CSVIterator& it);


    friend std::ostream &operator<<(std::ostream &os, const Phoenix &icews);

};


#endif //INCONSISTENCY_PHOENIX_H
