//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_CSVITERATOR_H
#define INCONSISTENCY_CSVITERATOR_H

#include <string>
#include "csv_istream.h"
#include "../serializers/commons/structure.h"

struct CSVIterator {
    csv_istream it;
    std::string current;
    LONG_NUMERIC pos;

    CSVIterator(std::istream& line) : it{line}, pos{0} {
        if (!it)
            pos = std::string::npos;
        else
            it >> current;
    }
    CSVIterator() : pos{std::string::npos} {

    }
    bool operator!= (const CSVIterator& other) const;
    std::string operator* () const {
        return current;
    }
    const CSVIterator& operator++ (int i) {
        if (!it) {
            pos = std::string::npos;
            current = "#ERROR";
        } else {
            it >> current;
        }
    }
};


#endif //INCONSISTENCY_CSVITERATOR_H
