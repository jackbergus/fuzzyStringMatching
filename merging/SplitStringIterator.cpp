//
// Created by giacomo on 09/12/18.
//

#include "SplitStringIterator.h"

SplitStringIterator::SplitStringIterator(std::string &s, std::string delimiter) : dem{delimiter}, ss{s} {
    len  = dem.length();
    beginning = true;
    next = ss.find(dem, pos);
    if (next == std::string::npos) {
        next = 0;
        justOneElement = true;
    } else {
        justOneElement = false;
    }
}

SplitStringIterator::SplitStringIterator() {
    next = std::string::npos;
}

bool SplitStringIterator::operator!=(const SplitStringIterator &other) const {
    return next != other.next;
}

std::string SplitStringIterator::operator*() const {
    size_t posToSet = beginning ? pos : pos+1;
    size_t c = (ss.find(dem, posToSet));
    bool finalIsNotEnd = c != std::string::npos;
    bool begIsNotEnd = pos != std::string::npos;
    return next == ss.length() ? "" :
           ss.substr((begIsNotEnd ? posToSet : prev+len),(finalIsNotEnd && begIsNotEnd ? (beginning ? c : c-pos-1) : ss.length()));
}

const SplitStringIterator &SplitStringIterator::operator++(int i) {
    count++;
    if (justOneElement) {
        next = std::string::npos;
    } else {
        prev = pos;
        pos = ss.find(dem, beginning ? next : next+len);
        if (!beginning) {
            next = ss.find(dem, pos);
        }
    }
    beginning = false;
}

SplitStringIterator &SplitStringIterator::operator>>(std::string &obj) {
    std::cin >> obj;
    return *this;
}
