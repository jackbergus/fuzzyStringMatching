//
// Created by giacomo on 11/11/17.
//

#include "GraphCollectionMapper.h"

GraphCollectionMapper::GraphCollectionMapper(char *operandPath) {
    boost::filesystem::path baseOperandPath{operandPath};
    boost::filesystem::path primary = baseOperandPath / "primary.bin";
    boost::filesystem::path values = baseOperandPath / "values.bin";
    index = (struct primary_index*)mmapFile(primary.string(), &primary_index_size, &primary_index_fd);
    containment = (header*)mmapFile(values.string(), &containment_size, &containment_fd);
}

GraphCollectionMapper::~GraphCollectionMapper() {
    if (containment) {
        munmap(containment,containment_size);
        close(containment_fd);
    }
    if (index) {
        munmap(index,primary_index_size);
        close(primary_index_fd);
    }
}

LONG_NUMERIC GraphCollectionMapper::vertexSetSize() {
    return 0;
}
