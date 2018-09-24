//
// Created by giacomo on 28/07/17.
//

#ifndef PROJECT_VERTEXITERATOR_H
#define PROJECT_VERTEXITERATOR_H

#include "secondary_memory/header.h"

class VertexIterator {
public:
    VertexIterator (header* begin, header* end);

    bool operator!= (const VertexIterator& other) const;

    header* operator*() const;

    const VertexIterator& operator++ ();

    VertexIterator begin () const;

    VertexIterator end () const;



private:
    header* start;
    header* stop;
};


#endif //PROJECT_VERTEXITERATOR_H
