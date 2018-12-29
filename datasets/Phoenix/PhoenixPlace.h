//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_PHOENIXPLACE_H
#define INCONSISTENCY_PHOENIXPLACE_H

#include <string>
#include "../../merging/CSVIterator.h"

struct PhoenixPlace {
    long double latitude, longitude;
    std::string city_region_country;
    std::string state;
    std::string country;

    void load(CSVIterator& it);
};


#endif //INCONSISTENCY_PHOENIXPLACE_H
