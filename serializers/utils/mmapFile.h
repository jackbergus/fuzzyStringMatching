/*
 * mmapFile.h
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

#ifndef PROJECT_MMAPFILE_H
#define PROJECT_MMAPFILE_H

#include <string>
#include <fstream>

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
}

void* mmapFile(std::string file, unsigned long* size, int* fd);

#define UNSAFE_FILE_SIZE(file, val) { \
    std::ifstream in((file), std::ifstream::ate | std::ifstream::binary);\
    (val) = in.tellg();\
}

#endif //PROJECT_MMAPFILE_H
