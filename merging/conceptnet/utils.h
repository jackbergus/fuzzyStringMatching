//
// Created by giacomo on 17/10/18.
//

#ifndef INCONSISTENCY_UTILS_H
#define INCONSISTENCY_UTILS_H

#include <string>
#include "../../fromJava/trimmers.h"

extern  std::string slash;
std::string rectify(std::string& x);
std::string splitOnce(std::string& s, std::string& delimiter, int ith);
std::string unrectify(std::string& x);
std::string extract_basic_id(std::string& generic_id);

#endif //INCONSISTENCY_UTILS_H
