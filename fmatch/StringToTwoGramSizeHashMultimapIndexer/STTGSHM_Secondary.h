//
// Created by giacomo on 26/09/18.
//

#include "../libfuzzymatch.h"

#ifndef EDGEINDEXING_STTGSHM_SECONDARY_H
#define EDGEINDEXING_STTGSHM_SECONDARY_H

struct internalMap {
    wchar_t         map[2];
    LONG_NUMERIC    value;
};

// the secondary of reference is SLHM_Secondary. The only thing
// that changes are the way to access the elements.

#define CHARLONG_ARRAY_START(offset)    ((offset == nullptr) ? nullptr : ((char*)(STRING(offset)+OFFSET_STRING_SIZE(offset))))

#define CHARLONG_ARRAY_SIZE(offset)          ((offset == nullptr) ? 0 : OFFSET_STRING_SIZE((offset)))

#define CHARLONG_ARRAY_ELEMENT(offset)       ((struct internalMap*)((offset == nullptr) ? nullptr : ((struct internalMap*)(((char*)(offset))+sizeof(LONG_NUMERIC)))))

#endif //EDGEINDEXING_STTGSHM_SECONDARY_H
