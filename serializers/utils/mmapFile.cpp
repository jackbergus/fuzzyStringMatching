/*
 * mmapFile.cpp
 * This file is part of graphSampler
 *
 * Copyright (C) 2017 - Giacomo Bergami
 *
 * graphSampler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * graphSampler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with graphSampler. If not, see <http://www.gnu.org/licenses/>.
 */

 
//
// Created by giacomo on 04/08/17.
//

#include "mmapFile.h"
#include "../commons/structure.h"

void* mmapFile(std::string file, unsigned long* size, int* fd) {
    {
        std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
        *size = in.tellg();
    }
    char *full_path = realpath(file.data(), NULL);
    *fd = open(full_path,O_RDWR);
    free(full_path);
    void* addr = mmap(NULL,*size, PROT_READ, MAP_SHARED, *fd, 0 );
    return addr;
}
