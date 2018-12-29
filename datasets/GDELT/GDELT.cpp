//
// Created by giacomo on 11/12/18.
//

#include "GDELT.h"

void GDELT::load(SplitStringIterator &ref, bool isOldFormat) {
    id = *ref; ref++;
    time.load(ref);
    src.load(ref);
    dst.load(ref);
    relation.load(ref);
    src.loadPlace(ref, isOldFormat);
    dst.loadPlace(ref, isOldFormat);
    place.load(ref, isOldFormat);
}


std::ostream &operator<<(std::ostream &os, const GDELT &icews) {
    os << "GDELT\n\t<" << icews.src.name << ">--[label=" << icews.relation.event_name
       << ", p=1.0]-><" << icews.dst.name << ">\t@[T=" << icews.time.SQLSTRING << "; PLC=" << icews.place.fullname << "]";
    return os;
}