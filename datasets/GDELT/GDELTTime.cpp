//
// Created by giacomo on 11/12/18.
//

#include "GDELTTime.h"

void GDELTTime::load(SplitStringIterator &ref) {
    SQLSTRING = *ref; ref++;
    month_year = *ref; ref++;
    year = *ref; ref++;
    frac_date = *ref; ref++;
}
