//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_HELPERS_H
#define INCONSISTENCY_HELPERS_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include "../../merging/SplitStringIterator.h"
#include "../../fromJava/trimmers.h"

struct Helpers {
    std::unordered_map<std::string, std::string> cameo_event_code_to_representation;

    void loadCameoEventCode(std::string& filename);
};


#endif //INCONSISTENCY_HELPERS_H
