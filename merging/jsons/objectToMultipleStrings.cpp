//
// Created by giacomo on 25/01/19.
//

#include "objectToMultipleStrings.h"
#include "../conceptnet/utils.h"

objectToMultipleStrings::objectToMultipleStrings(std::unordered_map<std::string, conceptnet5_vertex> &tr) :  translation(tr) {}

bool objectToMultipleStrings::StartObject() { pos++; return true; }

bool objectToMultipleStrings::Key(const char *str, SizeType length, bool copy) {
    if (pos == 1) {
        std::string key{str, length};
        ebi = extract_basic_id(key);
        return true;
    } else
        return pos == 2;
}

bool objectToMultipleStrings::Default() { return false; }

bool objectToMultipleStrings::EndObject(SizeType memberCount) {
    pos--;
    if (!doFind) {
        if (it != translation.cend())
            it->second.dedup();
        doFind = true;
    }
    return true;
}

void objectToMultipleStrings::readFromFile(std::string path) {
    FILE* fp = fopen(path.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    Reader reader;
    reader.Parse(is, *this);
}

bool objectToMultipleStrings::String(const char *ch, SizeType t, bool v) {
    if (doFind) {
        it = translation.find(ebi);
        doFind = false;
    }
    if (it != translation.cend()) {
        std::string surfaces{ch, t};
        it->second.surfaces.emplace_back(surfaces);
    }
    return true;
}

bool objectToMultipleStrings::StartArray() { return true; }

bool objectToMultipleStrings::EndArray(SizeType t) { return true; }
