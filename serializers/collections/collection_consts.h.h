//
// Created by giacomo on 09/11/17.
//

#ifndef GRAPHSAMPLER_COLLECTION_CONSTS_H_H
#define GRAPHSAMPLER_COLLECTION_CONSTS_H_H

#include "../utils/dovetailing.h"
#include "../commons/globals.h"

#define COLLECTION_ID                                   0
#define COLLECTION_ELEMENT_ID(x)                        ((x)+1)
#define COLLECTION_ELEMENT_CONTENT_ID(x,coll_size)      ((x)+(coll_size+1))

#endif //GRAPHSAMPLER_COLLECTION_CONSTS_H_H
