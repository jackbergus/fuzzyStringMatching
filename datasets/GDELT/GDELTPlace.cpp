//
// Created by giacomo on 11/12/18.
//

#include "GDELTPlace.h"
#include "../../fromJava/trimmers.h"

void GDELTPlace::load(SplitStringIterator &ref, bool isOldFormat) {
    type = *ref; ref++;
    fullname = *ref; ref++;
    country_code = *ref; ref++;
    adm1_code = *ref; ref++;
    if (!isOldFormat) {
        adm2_code = *ref; ref++;
    }
    std::string x = trim(*ref);
    latitude = x.empty() ? 0.0 : std::stod(x); ref++;
    x = *ref;
    longitude = x.empty() ? 0.0 : std::stod(x); ref++;
    GNS_GNIS_feature_id = *ref; ref++;
}
