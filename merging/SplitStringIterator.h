//
// Created by giacomo on 09/12/18.
//

#ifndef INCONSISTENCY_SPLITSTRINGITERATOR_H
#define INCONSISTENCY_SPLITSTRINGITERATOR_H

#include <string>
#include <iostream>

/**
 * This class provides an iterator splitting the stirngs, without allocating any vector where to store any splitted part
 */
class SplitStringIterator {
    bool beginning, justOneElement;
    size_t next = 0, pos = 0, prev = 0, count = 0, c = 0;
    size_t len;
    std::string dem, ss;

public:
    SplitStringIterator (std::string& s, std::string delimiter);
    SplitStringIterator();
    bool operator!= (const SplitStringIterator& other) const;
    std::string operator* () const;
    const SplitStringIterator& operator++ (int i);
    SplitStringIterator& operator>>(std::string& obj);
};


#endif //INCONSISTENCY_SPLITSTRINGITERATOR_H
