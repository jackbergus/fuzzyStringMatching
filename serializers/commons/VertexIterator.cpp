//
// Created by giacomo on 28/07/17.
//

#include "VertexIterator.h"

VertexIterator::VertexIterator(header *begin, header *end)
        : start(begin), stop(end)
{ }

bool VertexIterator::operator!=(const VertexIterator &other) const {
    return start != other.start;
}

header *VertexIterator::operator*() const {
    return start;
}

const VertexIterator &VertexIterator::operator++() {
    start = (header*)(((char*)start) + start->length);
    return *this;
}

VertexIterator VertexIterator::begin() const {
    return VertexIterator(start, stop);
}

VertexIterator VertexIterator::end() const {
    return VertexIterator(stop, stop);
}
