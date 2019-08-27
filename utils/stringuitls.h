//
// Created by giacomo on 26/08/19.
//

#ifndef INCONSISTENCY_STRINGUITLS_H
#define INCONSISTENCY_STRINGUITLS_H

#include <cstring>

/**
 * Compares two strings having different lengths
 *
 * @param value
 * @param len1
 * @param other
 * @param len2
 * @return
 */
int strnmcmp(char* value, size_t len1, char * other, size_t len2);

#endif //INCONSISTENCY_STRINGUITLS_H
