//
// Created by giacomo on 10/12/18.
//

#ifndef INCONSISTENCY_NELL_H
#define INCONSISTENCY_NELL_H

#include "../../serializers/commons/structure.h"

#include "NELLArgument.h"
#include "NELLRelation.h"

struct NELL {
    LONG_NUMERIC id;
    NELLArgument src;
    NELLArgument value;
    NELLRelation relation;
    NELL (LONG_NUMERIC id, std::string& line);
    friend std::ostream &operator<<(std::ostream &os, const NELL &nell);
    void updateWith(NELL nell);
    void getEdge(std::ofstream& file);
    void getAdditionalElements(std::ofstream& file);
};

#endif //INCONSISTENCY_NELL_H
