//
// Created by giacomo on 09/11/17.
//

#ifndef GRAPHSAMPLER_SERIALIZEGRAPHCOLLECTION_H
#define GRAPHSAMPLER_SERIALIZEGRAPHCOLLECTION_H

#include <stdio.h>
#include "../commons/structure.h"
#include "../commons/primary_memory/entity_relationship.h"

/**
 * Serializes the entry point to the graph collection
 * @param values            file where to serialize the list of all the elements
 * @param primary_index     Primary index where to memorize the fast element access by id.
 * @param offset            Offset at which the element is starting to write
 * @param coll_size         Size of the overall collection
 * @return
 */
LONG_NUMERIC serializeGraphCollectionEntryPoint(FILE* values, FILE* primary_index, LONG_NUMERIC offset, int coll_size);
LONG_NUMERIC serializeGraphEntryPoint(FILE* values, FILE* primary_index, LONG_NUMERIC offset, ERvertex& coll_size);


#endif //GRAPHSAMPLER_SERIALIZEGRAPHCOLLECTION_H
