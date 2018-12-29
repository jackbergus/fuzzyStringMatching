//
// Created by giacomo on 11/12/18.
//

#include "PhoenixTime.h"

void PhoenixTime::load(CSVIterator &it) {
    story_date = *it; it++;
    year = *it; it++;
    month = *it; it++;
    day = *it; it++;
}
