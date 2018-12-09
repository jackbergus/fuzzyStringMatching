//
// Created by giacomo on 09/11/17.
//

#include "collection_consts.h.h"
#include "GraphCollectionSerializeSteps.h"
#include "../../random/RandomGMarkFile.h"
#include "../commons/secondary_memory/primary_index.h"
#include "../commons/primary_memory/entity_relationship.h"
#include "../commons/Serialize.h"

LONG_NUMERIC serializeGraphCollectionEntryPoint(FILE* values, FILE* primary_index, LONG_NUMERIC offset, int coll_size) {
    ERvertex v;
    v.id = COLLECTION_ID;
    v.hash = GRAPH_COLLECTION_HASH;
    for (LONG_NUMERIC i = COLLECTION_ELEMENT_ID(0); i<COLLECTION_ELEMENT_ID(coll_size); i++) {
        v.vertex_containment.emplace_back(i);
    }
    LONG_NUMERIC size = serialize(&v, values);
    struct primary_index pi{v.id, v.hash, offset};
    fwrite(&pi, sizeof(struct primary_index), 1, primary_index);
    return size+offset;
}


LONG_NUMERIC serializeGraphEntryPoint(FILE* values, FILE* primary_index, LONG_NUMERIC offset, ERvertex& v) {
    LONG_NUMERIC size = serialize(&v, values);
    struct primary_index pi{v.id, v.hash, offset};
    fwrite(&pi, sizeof(struct primary_index), 1, primary_index);
    return size+offset;
}