//
// Created by giacomo on 11/12/18.
//

#include "NELLRelation.h"

void NELLRelation::load(SplitStringIterator &ref) {
    type = *ref; ref++;
    probability = std::stod(*ref); ref++;
}
