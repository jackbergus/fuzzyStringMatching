/*
 * conceptnet5_vertex.h
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
// Created by giacomo on 25/01/19.
//

#ifndef INCONSISTENCY_CONCEPTNET5_VERTEX_H
#define INCONSISTENCY_CONCEPTNET5_VERTEX_H

#include <string>
#include <vector>

/**
 * Providing the basic vertex representation
 */
struct conceptnet5_vertex {
    /**
     * Head id (removes the sense information)
     */
    std::string id;
    /**
     * Language associated to the id
     */
    std::string language;
    /**
     * Multiple string representations associated to the same string
     */
    std::vector<std::string> surfaces;
    /**
     * Different POS associated to the string
     */
    std::vector<std::string> senses;
    /**
     * Sub-ids associated to the same string.
     */
    std::vector<std::string> subids;

    conceptnet5_vertex(std::string x);;

    /**
     * dedupling the information inserted within the vectors
     */
    void dedup();
    void finalizeObject();
};



#endif //INCONSISTENCY_CONCEPTNET5_VERTEX_H
