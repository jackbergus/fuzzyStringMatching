/*
 * objectToMultipleStrings.h
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2019 - Giacomo Bergami
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

#ifndef INCONSISTENCY_OBJECTTOMULTIPLESTRINGS_H
#define INCONSISTENCY_OBJECTTOMULTIPLESTRINGS_H

#include "rapidjson/reader.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;

#include <unordered_map>

#include "../conceptnet/deserialization/conceptnet5_vertex.h"


struct objectToMultipleStrings : public rapidjson::BaseReaderHandler<UTF8<>, objectToMultipleStrings> {
    std::unordered_map<std::string, conceptnet5_vertex> &translation;
    std::unordered_map<std::string, conceptnet5_vertex>::iterator it;
    bool doFind = true;
    std::string ebi;
    short int pos = 0;

    /**
     * @param tr    Translation map, mapping the basic substring to the actual id
     */
    objectToMultipleStrings(std::unordered_map<std::string, conceptnet5_vertex> &tr);
    bool StartObject();
    bool Key(const char* str, SizeType length, bool copy);
    bool Default();
    bool EndObject(SizeType memberCount);
    void readFromFile(std::string path);

    bool String(const Ch* ch, SizeType t, bool v);
    bool StartArray();
    bool EndArray(SizeType t);
};


#endif //INCONSISTENCY_OBJECTTOMULTIPLESTRINGS_H
