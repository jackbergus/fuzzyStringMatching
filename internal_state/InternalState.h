//
// Created by giacomo on 13/10/18.
//

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#ifndef INCONSISTENCY_INTERNALSTATE_H
#define INCONSISTENCY_INTERNALSTATE_H


/**
 * This class represents the main entrypoint that preserves the state of the current computation.
 */
class InternalState {
public:
    rapidjson::Document hypothesis;

    void getdocument() {
        rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> &sg = hypothesis["subgraphs"];
        sg.GetArray().Size();
    }
};

/**
 * This function allows to
 */
#define INTERNAL_STATE_READ_HYPOTHESIS_FROM_STRING(internalState, string)    ((internalState).hypothesis.Parse(string))

#endif //INCONSISTENCY_INTERNALSTATE_H
