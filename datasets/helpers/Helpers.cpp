//
// Created by giacomo on 11/12/18.
//

#include "Helpers.h"

void Helpers::loadCameoEventCode(std::string &filename) {
    std::ifstream infile(filename);
    std::string line, key, value;
    bool  skipFirst = true;
    while (std::getline(infile, line)) {
        if (!skipFirst) {
            SplitStringIterator it{line, "\t"}, end{};
            key = trim(*it); it++;
            value = trim(*it); it++;
            cameo_event_code_to_representation[key] = value;
        } else {
            skipFirst = false;
        }
    }
}
