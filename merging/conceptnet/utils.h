/*
 * utils.h
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2018 - Giacomo Bergami
 *
 * fuzzyStringMatching is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * fuzzyStringMatching is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fuzzyStringMatching. If not, see <http://www.gnu.org/licenses/>.
 */


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
