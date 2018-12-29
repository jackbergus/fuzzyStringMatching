//
// Created by giacomo on 11/12/18.
//

#include "GDELTArgument.h"

void GDELTArgument::load(SplitStringIterator &ref) {
    code = *ref; ref++;
    name = *ref; ref++;
    cameo_country_code = *ref; ref++;
    known_group_code = *ref; ref++;
    ethnic_code = *ref; ref++;
    religion1_code = *ref; ref++;
    religion2_code = *ref; ref++;
    type1 = *ref; ref++;
    type2 = *ref; ref++;
    type3 = *ref; ref++;
}

void GDELTArgument::loadPlace(SplitStringIterator &ref, bool isOldFormat) {
    place.load(ref, isOldFormat);
}
