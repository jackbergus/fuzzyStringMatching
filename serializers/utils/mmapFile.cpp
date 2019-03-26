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