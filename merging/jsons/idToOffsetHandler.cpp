/*
 * idToOffsetHandler.cpp
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

#include "idToOffsetHandler.h"
#include "../conceptnet/utils.h"

idToOffsetHandler::idToOffsetHandler(fixed_bimap<std::string, LONG_NUMERIC> &map,
                                     std::unordered_map<std::string, conceptnet5_vertex> &tr) : map(map), translation(tr) {}

bool idToOffsetHandler::Int(int i) { map.put(key, i); return true; }

bool idToOffsetHandler::Uint(unsigned u) { map.put(key, u); return true; }

bool idToOffsetHandler::Int64(int64_t i) { map.put(key, i); return true; }

bool idToOffsetHandler::Uint64(uint64_t u) { map.put(key, u); return true; }

bool idToOffsetHandler::StartObject() { return true; }

bool idToOffsetHandler::Key(const char *str, SizeType length, bool copy) {
    key = str;
    std::string ebi = extract_basic_id(key);
    translation.insert({ebi, {ebi}}).first->second.subids.emplace_back(key);
    return true;
}

bool idToOffsetHandler::Default() { return false; }

bool idToOffsetHandler::EndObject(SizeType memberCount) { return true; }

void idToOffsetHandler::readFromFile(std::string path) {
    FILE* fp = fopen(path.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Reader reader;
    reader.Parse(is, *this);
}
