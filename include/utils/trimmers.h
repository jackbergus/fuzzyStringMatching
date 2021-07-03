/*
 * trimmers.h
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
