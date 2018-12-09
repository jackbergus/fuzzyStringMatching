//
// Created by giacomo on 18/07/17.
//
#include "fwrite.h"

#ifdef DEBUG
size_t my_fwrite(const void *src, size_t size, size_t nmemb, void *file) {
    size_t toret = memcpy(*((void**)file), src, size * nmemb) == *((void**)file) ? size : 0;
    *((char**)file) += size;
    return toret;
}
#endif