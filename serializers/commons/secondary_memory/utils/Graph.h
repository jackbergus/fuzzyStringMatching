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

    Graph();

    unsigned long nVertices();

    bool open();

    bool clos();

    ~Graph();

    char *resolveEdgeValue(LONG_NUMERIC i);

    unsigned long nEdges();
};


#endif //NESTING_GRAPH_H
