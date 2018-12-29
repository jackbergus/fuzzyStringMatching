//
// Created by giacomo on 10/12/18.
//

#ifndef INCONSISTENCY_ICEWSARGUMENT_H
#define INCONSISTENCY_ICEWSARGUMENT_H

#include <string>
#include <ostream>
#include <vector>
#include "../../merging/SplitStringIterator.h"

struct ICEWSArgument {
    std::string name, country;
    std::vector<std::string> sectors;
    bool src;
    std::string srcName;
    void load(bool  isSource, SplitStringIterator& it);
    friend std::ostream &operator<<(std::ostream &os, const ICEWSArgument &argument);
};


#endif //INCONSISTENCY_ICEWSARGUMENT_H
