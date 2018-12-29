//
// Created by giacomo on 17/10/18.
//

#ifndef INCONSISTENCY_UTILS_H
#define INCONSISTENCY_UTILS_H

#include <string>

extern  std::string slash;
std::string rectify(std::string& x);
std::string splitOnce(std::string& s, std::string& delimiter, int ith);
std::string unrectify(std::string& x);

#endif //INCONSISTENCY_UTILS_H
