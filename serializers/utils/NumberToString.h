/*
 * NumberToString.h
 * This file is part of graphSampler
 *
 * Copyright (C) 2017 - Giacomo Bergami
 *
 * graphSampler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * graphSampler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with graphSampler. If not, see <http://www.gnu.org/licenses/>.
 */


//
// Created by giacomo on 10/08/17.
//

#ifndef PROJECT_NUMBERTOSTRING_H
#define PROJECT_NUMBERTOSTRING_H

/* http://www.cplusplus.com/articles/D9j2Nwbp/ */

#include <sstream>

template <typename T> std::string NumberToString (T Number ) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

template <typename T> T StringToNumber ( const std::string &Text )  {
    std::istringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}

#endif //PROJECT_NUMBERTOSTRING_H
