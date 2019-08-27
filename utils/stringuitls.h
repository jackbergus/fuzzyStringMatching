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


/**
 * Convert single character into lowercase
 * @param ch    UTF8 character
 * @return
 */
wchar_t lowcase(wchar_t ch);

/**
 * Converts to uppercase a string that might be in unicode
 * @param src   Unicode raw string
 * @return
 */
std::string utf8_tolower(const std::string &src);


#endif //INCONSISTENCY_STRINGUITLS_H
