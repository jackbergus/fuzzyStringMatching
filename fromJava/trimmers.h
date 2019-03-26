//
// Created by giacomo on 11/12/18.
//

#ifndef INCONSISTENCY_TRIMMERS_H
#define INCONSISTENCY_TRIMMERS_H

#include <iostream>
#include <string>
#include <algorithm>

extern "C" {
#include <string.h>
};

std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);
int strpos(char *haystack, char *needle, int nth);

std::string to_string(const std::string& value);


#endif //INCONSISTENCY_TRIMMERS_H
