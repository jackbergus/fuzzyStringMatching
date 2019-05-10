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
