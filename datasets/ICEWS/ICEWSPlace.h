//
// Created by giacomo on 10/12/18.
//

#ifndef INCONSISTENCY_ICEWSPLACE_H
#define INCONSISTENCY_ICEWSPLACE_H

#include <string>
#include <ostream>
#include "../../merging/SplitStringIterator.h"

struct ICEWSPlace {
    std::string city, district, province, country;
    long double latitude, longitude;
    void load(SplitStringIterator& it);
    friend std::ostream &operator<<(std::ostream &os, const ICEWSPlace &place);
};


#endif //INCONSISTENCY_ICEWSPLACE_H
