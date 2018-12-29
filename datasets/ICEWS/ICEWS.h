//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_ICEWS_H
#define INCONSISTENCY_ICEWS_H

#include <ostream>
#include "../../serializers/commons/structure.h"
#include "ICEWSArgument.h"
#include "ICEWSPlace.h"

class ICEWS {
public:
    LONG_NUMERIC id;
    std::string time;
    ICEWSArgument src;
    std::string event;
    std::string event_type_id;
    std::string intensity; // part where we could extract the negation
    ICEWSArgument dst;
    ICEWSPlace place;

    ///
    bool isNegated;
    ICEWS(std::string& line);
    friend std::ostream &operator<<(std::ostream &os, const ICEWS &icews);
};


#endif //INCONSISTENCY_ICEWS_H
