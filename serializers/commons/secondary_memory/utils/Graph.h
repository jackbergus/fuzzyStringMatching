//
// Created by giacomo on 05/11/17.
//

#ifndef NESTING_GRAPH_H
#define NESTING_GRAPH_H

#include <set>
#include <dirent.h>
#include "../header.h"
#include "../../../utils/mmapFile.h"
#include "../primary_index.h"

#include "../../../../lib/rapidjson/include/rapidjson/reader.h"

class GraphQueryIterator;

/**
 * Container for the whole graph entry point descriptors
 */
class Graph {
    unsigned long size = 0;
    unsigned long sizei = 0;
    int fd = 0;
    int fdED = 0;
    int fdEV = 0;
    int fdi = 0;
    unsigned long sizeEP;
    unsigned long sizeEV;
    std::string handle;

public:
    header* begin = nullptr;
    header* end = nullptr;
    struct primary_index* index = nullptr;
    LONG_NUMERIC* edgePointer = nullptr;
    char* edgeValues = nullptr;
    rapidjson::Reader reader;


    Graph();

    /**
     * This function provides the iterator over which we can perform a graph query. By doing so I'm allocating no
     * memory
     *
     * @param node          Vertex from which starting the enumeration
     * @param ingoing       Whether the traversal is done over the ingoing or the outgoing vertices
     * @param relBitMap     Bitmap allowing to select the edges to traverse
     * @return
     */
    std::pair<GraphQueryIterator,GraphQueryIterator> query(LONG_NUMERIC node, bool ingoing, unsigned long relBitMap);

    unsigned long nVertices();
    bool open();
    bool clos();
    ~Graph();
    char *resolveEdgeValue(LONG_NUMERIC i);

    unsigned long nEdges();
};


#endif //NESTING_GRAPH_H
