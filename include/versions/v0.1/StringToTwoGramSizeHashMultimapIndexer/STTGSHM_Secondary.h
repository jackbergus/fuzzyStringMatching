/*
 * STTGSHM_Secondary.h
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2018 - Giacomo Bergami
 *
 * fuzzyStringMatching is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * fuzzyStringMatching is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fuzzyStringMatching. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 26/09/18.
//

#include "versions/v0.1/libfuzzymatch.h"

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
