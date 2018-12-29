//
// Created by giacomo on 08/12/18.
//

#include "ConceptNet5Dumps.h"
#include "../SplitStringIterator.h"
#include "../graph_conceptnet/GraphQueryIterator.h"


void ConceptNet5Dumps::loadIdToOffset(std::istream &linestream) {
    std::string fst, snd;
    LONG_NUMERIC nummus;
    while (
        // 2 Read the second field (which is terminated by tab)
            (!std::getline(linestream, fst, '\t').fail()) &&
            // 3 Read the third field  (which is terminated by newline)
            (std::getline(linestream, snd))) {
        nummus = std::stoul(snd);
        idToOffset[fst] = nummus;
        offsetToId[nummus] = fst;
    }
}

void ConceptNet5Dumps::loadclandToSeed(std::istream &linestream) {
    std::string fst, snd;
    LONG_NUMERIC nummus;
    std::string toTabs{"\t"};
    while (
        // 2 Read the second field (which is terminated by tab)
            (!std::getline(linestream, fst, '\t').fail()) &&
            // 3 Read the third field  (which is terminated by newline)
            (std::getline(linestream, snd))) {
        for (SplitStringIterator i{snd, toTabs}, end{}; i != end; i++) {
            clangToSeed[fst].push_back(*i);
        }
    }
}


std::pair<GraphQueryIterator, GraphQueryIterator>
ConceptNet5Dumps::relDefaultEn(std::string &term, LONG_NUMERIC relMap, bool ingoing) {
    std::map<std::string, LONG_NUMERIC>::iterator tryFnd = idToOffset.find(term);
    if (tryFnd == idToOffset.cend()) {
        return ecp;
    } else {
        return ep.query(tryFnd->second, ingoing, relMap);
    }
}

ConceptNet5Dumps::ConceptNet5Dumps() : eit{&this->ep, 0, false}, ecp{{&this->ep, 0, false}, {&this->ep, 0, false}} {


}
