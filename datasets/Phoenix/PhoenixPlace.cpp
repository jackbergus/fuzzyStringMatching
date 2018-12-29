//
// Created by giacomo on 11/12/18.
//

#include "PhoenixPlace.h"

void PhoenixPlace::load(CSVIterator &it) {
    std::string x = *it;
    latitude = x.empty() ? 0.0 : std::stold(x); it++;
    x = *it;
    longitude = x.empty() ? 0.0 : std::stold(x); it++;
    city_region_country = *it; it++;
    state = *it; it++;
    country = *it; it++;
}
