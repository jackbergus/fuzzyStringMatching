//
// Created by giacomo on 11/12/18.
//

#include "PhoenixArgument.h"

void PhoenixArgument::load(CSVIterator &it) {
    it++;
    root = *it; it++;
    agent = *it; it++;
    others = *it; it++;
}
