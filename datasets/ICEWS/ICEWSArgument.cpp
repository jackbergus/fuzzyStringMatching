//
// Created by giacomo on 10/12/18.
//

#include "ICEWSArgument.h"
#include "../../serializers/Streamers.h"

void ICEWSArgument::load(bool isSource, SplitStringIterator &it) {
    name = *it; it++;
    std::string tmp = *it; it++;
    for (SplitStringIterator it{tmp, "\t"}, end{}; it != end; it++) {
        sectors.push_back(*it);
    }
    country = *it; it++;
    src = isSource;
    srcName = src ? "Source" : "Target";
}

std::ostream &operator<<(std::ostream &os, const ICEWSArgument &argument) {
    os << "{" << argument.srcName << "Name: " << argument.name  << argument.srcName << "Sector: " << argument.sectors << argument.srcName << "Country: " << argument.country;
    return os;
}
