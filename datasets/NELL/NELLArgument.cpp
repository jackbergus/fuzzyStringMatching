//
// Created by giacomo on 11/12/18.
//

#include "NELLArgument.h"
#include "NELL.h"

std::ostream &operator<<(std::ostream &os, const NELLArgument &argument) {
    os << /*"ontology_name: " << argument.ontology_name << " best_string: " << argument.best_string << " literalStrings: "
       << argument.literalStrings << " hasCategory: " << argument.hasCategory*/ argument.best_string;
    return os;
}

void NELLArgument::updateWith(NELLArgument &cp) {
    if (cp.ontology_name == ontology_name && cp.best_string == best_string) {
        if (!cp.literalStrings.empty()) {
            std::unordered_set<std::string> s;
            for (std::string &x : literalStrings)
                s.insert(x);
            for (std::string &x : cp.literalStrings)
                s.insert(x);
            literalStrings.assign(s.begin(), s.end());
        }

        if (!cp.hasCategory.empty()) {
            std::unordered_set<std::string> s;
            for (std::string &x : hasCategory)
                s.insert(x);
            for (std::string &x : cp.hasCategory)
                s.insert(x);
            hasCategory.assign(s.begin(), s.end());
        }
    }
}
