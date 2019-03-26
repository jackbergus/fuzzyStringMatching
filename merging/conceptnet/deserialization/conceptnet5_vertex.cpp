//
// Created by giacomo on 25/01/19.
//

#include "conceptnet5_vertex.h"

#include <unordered_set>
#include <algorithm>
#include <iostream>

conceptnet5_vertex::conceptnet5_vertex(std::string x) : id{x} {
    std::cerr << "ERROR: do I have to call dedup or finalizeObject()?";
}

void conceptnet5_vertex::dedup() {
    {
        std::unordered_set<std::string> s;
        for (std::string& i : surfaces) s.insert(i);
        surfaces.assign( s.begin(), s.end() );
        std::sort( surfaces.begin(), surfaces.end() );
    }

    {
        std::unordered_set<std::string> s;
        for (std::string& i : subids) s.insert(i);
        subids.assign( s.begin(), s.end() );
        std::sort( subids.begin(), subids.end() );
    }

    if (surfaces.empty()) {
        surfaces.push_back(unrectify(id));
    }

    for (std::string& x : subids) {
        size_t next = 0, pos = 0, count = 0, c = 0;
        while ((next = x.find('/', pos)) != std::string::npos) {
            if (count == 4) {
                c = (x.find('/', pos+1));
                bool test = c != std::string::npos;
                std::string toret = next == x.length() ? "" :
                                    x.substr(pos+1,(test ? c-pos-1 : x.length()));
                senses.push_back(x.substr(pos, next));
            }
            count++;
            pos = x.find('/', next+1);
        }
    }
}


void conceptnet5_vertex::finalizeObject() {
    if (surfaces.empty()) {
        surfaces.emplace_back(unrectify(id));
    }

    size_t next = 0, pos = 0, count = 0, c = 0;
    while ((next = id.find('/', pos)) != std::string::npos) {
        if (count == 2) {
            c = (id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == id.length() ? "" :
                                id.substr(pos+1,(test ? c-pos-1 : id.length()));
            this->language = toret;
        } else if (count == 4) {
            c = (id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == id.length() ? "" :
                                id.substr(pos+1,(test ? c-pos-1 : id.length()));
            this->senses.emplace_back(id.substr(pos, next));
        }
        count++;
        pos = id.find('/', next+1);
    }
}

