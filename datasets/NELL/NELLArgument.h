//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_NELLARGUMENT_H
#define INCONSISTENCY_NELLARGUMENT_H

#include <unordered_set>
#include <vector>
#include <string>
#include <ostream>

struct NELLArgument {
    std::string ontology_name;
    std::string best_string;
    std::vector<std::string> literalStrings;
    std::vector<std::string> hasCategory;

    friend std::ostream &operator<<(std::ostream &os, const NELLArgument &argument);
    void updateWith(NELLArgument& cp);
};

#endif //INCONSISTENCY_NELLARGUMENT_H
