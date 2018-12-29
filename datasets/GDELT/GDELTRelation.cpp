//
// Created by giacomo on 11/12/18.
//

#include "GDELTRelation.h"

void GDELTRelation::load(SplitStringIterator &ref) {
    root_event = *ref; ref++;
    event_code = *ref; ref++;
    event_basecode = *ref; ref++;
    event_rootcode = *ref; ref++;
    ref++; ref++; ref++; ref++; ref++; ref++;
}
