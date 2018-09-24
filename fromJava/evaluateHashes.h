//
// Created by Giacomo Bergami on 16/08/16.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned int doHash(char *line, int *pos);
void evaluateHashes(char *file, int *pos);
unsigned int hashCode(char* string);
unsigned int hashCodeArray(char** arrayToHash);
#ifdef __cplusplus
}
#endif
