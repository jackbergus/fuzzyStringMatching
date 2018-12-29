//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_GDELTPLACE_H
#define INCONSISTENCY_GDELTPLACE_H

#include <string>
#include "../../merging/SplitStringIterator.h"

struct GDELTPlace {
    std::string type;
    std::string fullname;
    std::string country_code;
    std::string adm1_code;
    std::string adm2_code;
    double latitude, longitude;
    std::string GNS_GNIS_feature_id;

    void load(SplitStringIterator &ref, bool b);
};


#endif //INCONSISTENCY_GDELTPLACE_H
