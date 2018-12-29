//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_PHOENIXTIME_H
#define INCONSISTENCY_PHOENIXTIME_H

#include <string>
#include "../../merging/SplitStringIterator.h"
#include "../../merging/CSVIterator.h"

struct PhoenixTime {
    std::string story_date, year, month, day;

    void load(CSVIterator &it);
};


#endif //INCONSISTENCY_PHOENIXTIME_H
