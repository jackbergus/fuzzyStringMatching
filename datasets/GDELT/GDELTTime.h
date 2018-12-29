//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_GDELTTIME_H
#define INCONSISTENCY_GDELTTIME_H

#include <string>
#include "../../merging/SplitStringIterator.h"

struct GDELTTime {
    std::string SQLSTRING;
    std::string month_year;
    std::string year;
    std::string frac_date;

    void load(SplitStringIterator& ref);
};


#endif //INCONSISTENCY_GDELTTIME_H
