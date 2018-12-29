//
// Created by giacomo on 07/12/18.
//

#ifndef EDGEINDEXING_GRAPHQUERYITERATOR_H
#define EDGEINDEXING_GRAPHQUERYITERATOR_H

class Graph;

#include "../../serializers/utils/mmapFile.h"
#include "../../serializers/commons/secondary_memory/primary_index.h"
#include "../../merging/conceptnet/deserialization/conceptnet_edge_deserialization.h"

//This adapter increments the Vector::const_iterator, and returns only the field named `value`
//in order to hide the whiole `struct elem`
class GraphQueryIterator
{
    header *v;
    LONG_NUMERIC n;
    edges_in_vertices* vec;
    LONG_NUMERIC i;
    Graph* g;
    unsigned long bitmap;

public:
    conceptnet_edge_deserialization handler;

    /**
     * Starting pointer for the query iterator.
     * @param graph         Graph over which perform the adjacency list iteration over the edge hashing
     * @param node          Vertex from which traverse the graph
     * @param ingoing       Select whether we want to perform an ingoing or an outgoing traversal
     * @param relBitMap     Bitmap setting the edges that I am interested to return
     */
    GraphQueryIterator (Graph* graph, LONG_NUMERIC node, bool ingoing, unsigned long relBitMap);

    /**
     * Empty pointer for the given element
     * @param graph 
     * @param node 
     * @param ingoing 
     */
    GraphQueryIterator(Graph* graph, LONG_NUMERIC node, bool ingoing);

    GraphQueryIterator(const GraphQueryIterator& x);

    bool operator!= (const GraphQueryIterator& other) const;

    //std::string operator* () const;
    conceptnet_edge_deserialization operator* () const;

    const GraphQueryIterator& operator++ ();

};


#endif //EDGEINDEXING_GRAPHQUERYITERATOR_H
