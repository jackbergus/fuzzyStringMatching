/*
 * structure.h
 * This file is part of graphSampler
 *
 * Copyright (C) 2017 - Giacomo Bergami
 *
 * graphSampler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * graphSampler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with graphSampler. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 17/07/17.
//

#ifndef JINGOLOBA_STRUCTURE_H
#define JINGOLOBA_STRUCTURE_H

//#define PRINTDEBUG

#include <stdint-gcc.h>

typedef uint_fast64_t
        LONG_NUMERIC;

typedef uint_fast32_t
        UINT;

#define NUMERIC_MEMORY_OCCUPATION  \
        (sizeof(LONG_NUMERIC))

#include <vector>
typedef std::vector<LONG_NUMERIC>
        NUMERIC_VECTOR;

typedef std::vector<std::pair<LONG_NUMERIC, LONG_NUMERIC>>
        PAIR_NUMERIC_VECTOR;

#define VECTOR_SIZE(v) \
        ((v).size())

#define VECTOR_MEMORY_OCCUPATION(v)\
        (((VECTOR_SIZE(v))+1)*(NUMERIC_MEMORY_OCCUPATION))

#define VERTEX_OFFSET \
        (sizeof(header))

#include "secondary_memory/header.h"

bool binsearch_edges_in_vertices(struct edges_in_vertices* e, LONG_NUMERIC h_e, LONG_NUMERIC h_v, LONG_NUMERIC size,
                                 LONG_NUMERIC* left_limit, LONG_NUMERIC* right_limit);

//#define EDGE_ID     0
#define EDGE_HASH   1
#define VERTEX_ID   2
#define VERTEX_HASH 3

#define get_field_from(part,casus, val) switch (casus) {\
        case EDGE_ID:  val = part.edgeId; break;\
        case EDGE_HASH:  val = part.edgeHash; break;\
        case VERTEX_ID:  val = part.vertexId; break;\
        default: val = part.vertexHash; break;\
    }


#endif //JINGOLOBA_STRUCTURE_H
