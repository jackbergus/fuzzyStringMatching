//
// Created by giacomo on 05/11/17.
//

#include "Graph.h"
extern "C" {
    #include <unistd.h>
}

#include "../../../../merging/graph_conceptnet/GraphQueryIterator.h"

//const char* VERTICES = "vertex_hashing.bin";
const char* SECONDARY = "vertex_values.bin";
const char* EDGE_PRIMARY = "edge_primary.bin";
const char* EDGE_VALUES  = "edge_values.bin";
//const boost::filesystem::path VERTICES{"values.bin"};
//const boost::filesystem::path PRIMARY{"secondary.bin"};

Graph::Graph() {
}

unsigned long Graph::nVertices() {
    return sizei / sizeof(struct primary_index);
}

unsigned long Graph::nEdges() {
    return sizeEP / sizeof(LONG_NUMERIC);
}

bool Graph::open() {
    if (begin == nullptr && index == nullptr) {
        begin = (header*)mmapFile(SECONDARY, &size, &fd);
        end = (header*)(((char*)begin) + size);
        //index = (struct primary_index*)mmapFile(SECONDARY, &sizei, &fdi);

        edgePointer = (LONG_NUMERIC*)mmapFile(EDGE_PRIMARY, &this->sizeEP, &fdED);
        edgeValues = (char*)mmapFile(EDGE_VALUES, &this->sizeEV, &fdEV);
        return true;
    } else return false;
}

bool Graph::clos() {
    bool clos = false;
    if (begin != nullptr) {
        munmap(begin, size);
        begin = nullptr;
        close(fd);
        fd = size = 0;
        clos = true;
    }

        /*munmap(index, sizei);
        index = nullptr;
        close(fdi);
        fdi = sizei = 0;*/

        if (edgePointer != nullptr) {
            munmap(edgePointer, sizeEP);
            edgePointer = nullptr;
            close(fdED);
            sizeEP = fdED = 0;
            clos = true;
        }

        if (edgeValues != nullptr) {
            munmap(edgeValues, sizeEV);
            edgeValues = nullptr;
            close(fdEV);
            sizeEV = fdEV = 0;
            clos = true;
        }

    return clos;
}

Graph::~Graph() {
    clos();
}

char* Graph::resolveEdgeValue(LONG_NUMERIC i) {
    if (i < this->nEdges()) {
        return this->edgeValues + this->edgePointer[i];
    } else
        return nullptr;
}

std::pair<GraphQueryIterator, GraphQueryIterator> Graph::query(LONG_NUMERIC node, bool ingoing, unsigned long relBitMap) {
    return std::make_pair<GraphQueryIterator,GraphQueryIterator>({this, node, ingoing, relBitMap}, {this, node, ingoing});
}
