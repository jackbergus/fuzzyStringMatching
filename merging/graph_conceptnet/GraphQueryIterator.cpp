//
// Created by giacomo on 07/12/18.
//

#include "GraphQueryIterator.h"

#include "../../serializers/commons/secondary_memory/utils/Graph.h"

GraphQueryIterator::GraphQueryIterator(Graph *graph, LONG_NUMERIC node, bool ingoing, unsigned long relBitMap) {
    this->v = vertex_offset(graph->begin, node);
    this->g = graph;
    this->n = ingoing ? vertex_ingoing_edges_len(v) : vertex_outgoing_edges_len(v);
    this->vec = ingoing ? vertex_ingoing_edges_vec(v) : vertex_outgoing_edges_vec(v);
    this->bitmap = relBitMap;
    this->i = 0;
    while (i<n && (!(vec[i].edgeHash & bitmap))) i++;
}

GraphQueryIterator::GraphQueryIterator(Graph *graph, LONG_NUMERIC node, bool ingoing) {
    vec =     nullptr;
    g =       nullptr;
    n =       0;
    bitmap  = 0;
    v =       vertex_offset(graph->begin, node);
    i =       ingoing ? vertex_ingoing_edges_len(v) : vertex_outgoing_edges_len(v);
}

bool GraphQueryIterator::operator!=(const GraphQueryIterator &other) const {
    /*for (LONG_NUMERIC i = 0; i<n; i++) {
        if (vec[i].edgeHash & relBitMap) {
            std::string str{graph.resolveEdgeValue(vec[i].edgeId)};
            toRet.push_back(str);
        }
    }*/
    return i != other.i;
}

const GraphQueryIterator &GraphQueryIterator::operator++() {
    // Do increment the I until a good match is not found, or I read the end the adjacency vector
    while (i<n && (!(vec[i].edgeHash & bitmap))) i++;
    return *this;
}

/*std::string GraphQueryIterator::operator*() const {
    return g->resolveEdgeValue(vec[i].edgeId);
}*/

conceptnet_edge_deserialization GraphQueryIterator::operator*() const {
    conceptnet_edge_deserialization returned;
    returned.readFromChars(g->resolveEdgeValue(vec[i].edgeId), g->reader);
    return returned;
}