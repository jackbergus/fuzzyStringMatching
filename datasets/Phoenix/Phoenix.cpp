//
// Created by giacomo on 11/12/18.
//

#include "Phoenix.h"

void Phoenix::load(CSVIterator &it) {
    eid = *it; it++;
    time.load(it);
    src.load(it);
    dst.load(it);
    event_type = *it; it++;
    it++; it++; it++;
    joined_issues = *it; it++;
    place.load(it);
}

std::ostream &operator<<(std::ostream &os, const Phoenix &icews) {
    os << "Phoenix\n\t<" << icews.src.agent << ">--[label=" << icews.event_type
       << ", p=1.0]-><" << icews.dst.agent << ">\t@[T=" << icews.time.story_date << "; PLC=" << icews.place.city_region_country << "]";
    return os;
}