//
// Created by giacomo on 08/12/18.
//

#ifndef INCONSISTENCY_CONCEPTNET5DUMPS_H
#define INCONSISTENCY_CONCEPTNET5DUMPS_H

#include <istream>
#include <string>
#include <map>

#include "../../relationships/RelationshipTypes.h"
#include "../../serializers/commons/structure.h"
#include "../../serializers/commons/secondary_memory/utils/Graph.h"
#include "../graph_conceptnet/GraphQueryIterator.h"

class GraphQueryIterator;

class ConceptNet5Dumps {

    std::map<std::string, LONG_NUMERIC> idToOffset;
    std::map<LONG_NUMERIC, std::string> offsetToId;
    std::map<std::string, std::vector<std::string>> clangToSeed;
    Graph ep;
    GraphQueryIterator eit;
    std::pair<GraphQueryIterator,GraphQueryIterator> ecp;


public:

    ConceptNet5Dumps();

    void loadIdToOffset(std::istream& linestream);
    void loadclandToSeed(std::istream& linestream);

    /**
     * Default method for streaming for both ingoing and outgoing edges. Use the macros ingoingRelDefaultEn and  outgoingRelDefaultEn
     * @param term          Term to find within ConceptNet
     * @param relMap        Map of the relationships that we want to visit
     * @param ingoing       whether we want to traverse the ingoing or the outgoing edges
     * @return
     */
    std::pair<GraphQueryIterator, GraphQueryIterator> relDefaultEn(std::string& term, LONG_NUMERIC relMap, bool ingoing);

};

#define ingoingRelDefaultEn(term, relmap)         relDefaultEn(term, relmap, true)
#define outgoingRelDefaultEn(term, relmap)        relDefaultEn(term, relmap, false)

/**
 * This macro provides which are the similar elements that are allowed to be traversed
 */
#define SIMILAR_TO_TRAVERSE_MAP                   (CHT_SIMILAR & isSuitableForHierarchyTraversing_MAP)

#endif //INCONSISTENCY_CONCEPTNET5DUMPS_H
