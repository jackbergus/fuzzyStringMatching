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


#include <string>
#include "utils/trimmers.h"

extern  std::string slash;
std::string rectify(std::string& x);
std::string splitOnce(std::string& s, std::string& delimiter, int ith);
std::string unrectify(std::string& x);
std::string extract_basic_id(std::string& generic_id);

#endif //INCONSISTENCY_STRINGUITLS_H
