//
// Created by giacomo on 17/10/18.
//

#include "conceptnet_edge_deserialization.h"
#include "../utils.h"

/**
 * Move constructor
 * @param cc
 */
conceptnet_edge_deserialization::conceptnet_edge_deserialization(conceptnet_edge_deserialization &&cc) {
    this->vEnd = cc.vEnd;
    this->vStart = cc.vStart;
    this->symmetry = cc.symmetry;
    this->relType = cc.relType;
    this->weight = cc.weight;
    this->currentKey = cc.currentKey;
    this->dataset = cc.dataset;
    this->surfaceText = cc.surfaceText;
    this->isObjectStarted = cc.isObjectStarted;
    this->negated = cc.negated;
}

conceptnet_edge_deserialization::conceptnet_edge_deserialization() {}

// Deserializer
void conceptnet_edge_deserialization::readFromChars(const char *json, Reader &reader) {
    StringStream ss(json);
    reader.Parse(ss, *this);
}


// Triggers / Event Handlers
bool conceptnet_edge_deserialization::Null() { return true; }
bool conceptnet_edge_deserialization::Double(double d) {
    if (currentKey == "weight") {
        weight = d;
        if (weight > 1.0)
            weight = 1.0;
        return true;
    } else return false;
    //cout << "Double(" << d << ")" << endl; return true;
}
bool conceptnet_edge_deserialization::String(const char *str, SizeType length, bool copy) {
    if (currentKey == "start") {
        this->vStart.id = str;
    } else if (currentKey == "end") {
        this->vEnd.id = str;
    } else if (currentKey == "rel") {
        this->rel = str;
    } else if (currentKey == "uri") {
        //this->uri = str;
    } else if (currentKey == "license") {
        //this->license = str;
    } else if (currentKey == "license") {
        //this->license = str;
    } else if (currentKey == "surfaceText") {
        this->surfaceText = str;
    } else if (currentKey == "surfaceStart") {
        this->vStart.surface = str;
    } else if (currentKey == "surfaceEnd") {
        this->vEnd.surface = str;
    } else if (currentKey == "dataset") {
        this->dataset = str;
    } else if (currentKey == "features") {
        //this->features.emplace_back(str);
    }
    //cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
    return true;
}

bool conceptnet_edge_deserialization::Bool(bool b) { return false; }
bool conceptnet_edge_deserialization::Int(int i) { return false; }
bool conceptnet_edge_deserialization::Uint(unsigned u) { return false; }
bool conceptnet_edge_deserialization::Int64(int64_t i) { return false; }
bool conceptnet_edge_deserialization::Uint64(uint64_t u) { return false; }
bool conceptnet_edge_deserialization::RawNumber(const char *str, SizeType length, bool copy) { return false; }


bool conceptnet_edge_deserialization::StartArray() { return true; }
bool conceptnet_edge_deserialization::EndArray(SizeType elementCount) { return true; }

bool conceptnet_edge_deserialization::StartObject() {
    if (isObjectStarted && isCurrentAnAtomicValue.empty()) {
        isObjectStarted = false;
    }
    return true;
}

bool conceptnet_edge_deserialization::Key(const char *str, SizeType length, bool copy) {
    currentKey = str;
    return true;
}

bool conceptnet_edge_deserialization::EndObject(SizeType memberCount) {
    if ((!isObjectStarted) && isCurrentAnAtomicValue.empty()) {
        isObjectStarted = true;
        finalizeObject();
    }
    return true;
}

void conceptnet_edge_deserialization::finalizeObject() {
    if (vStart.surface.empty()) {
        vStart.surface = unrectify(vStart.id);
    }
    if (vEnd.surface.empty()) {
        vEnd.surface = unrectify(vEnd.id);
    }

    size_t next = 0, pos = 0, count = 0, c = 0;
    while ((next = vStart.id.find('/', pos)) != std::string::npos) {
        if (count == 2) {
            c = (vStart.id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == vStart.id.length() ? "" :
                                vStart.id.substr(pos+1,(test ? c-pos-1 : vStart.id.length()));
            this->vStart.language = toret;
        } else if (count == 4) {
            c = (vStart.id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == vStart.id.length() ? "" :
                                vStart.id.substr(pos+1,(test ? c-pos-1 : vStart.id.length()));
            this->vStart.sense = vStart.id.substr(pos, next);
        }
        count++;
        pos = vStart.id.find('/', next+1);
    }

    next = 0, pos = 0, count = 0;
    while ((next = vEnd.id.find('/', pos)) != std::string::npos) {
        if (count == 2) {
            c = (vEnd.id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == vEnd.id.length() ? "" :
                                vEnd.id.substr(pos+1,(test ? c-pos-1 : vEnd.id.length()));
            this->vEnd.language = toret;
        } else if (count == 4) {
            c = (vEnd.id.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == vEnd.id.length() ? "" :
                                vEnd.id.substr(pos+1,(test ? c-pos-1 : vEnd.id.length()));
            this->vEnd.sense = toret;
        }
        count++;
        pos = vStart.id.find('/', next+1);
    }

    std::string res{splitOnce(rel, slash, 10)};
    relType = res.empty() ? RelationshipTypes::ExternalURL : static_cast<RelationshipTypes>(enumMap.at(res));
    negated = res.empty() ? false : SemanticEdge_isNegated(relType);
    if (!isPreferredDirection_normal(relType)) {
        symmetry = true;
    }
}

ostream &operator<<(ostream &os, const conceptnet_edge_deserialization &deserialization) {
    os << "currentKey: " << deserialization.currentKey << " isObjectStarted: " << deserialization.isObjectStarted
       << " symmetry: " << deserialization.symmetry << " negated: " << deserialization.negated << " vStart: "
       << deserialization.vStart << " vEnd: " << deserialization.vEnd << " rel: " << deserialization.rel << " relType: "
       << deserialization.relType << " surfaceText: " << deserialization.surfaceText << " dataset: "
       << deserialization.dataset << " weight: " << deserialization.weight;
    return os;
}

ostream &operator<<(ostream &os, const conceptnet_vertex &vertex) {
    os << "id: " << vertex.id << " surface: " << vertex.surface << " language: " << vertex.language << " sense: "
       << vertex.sense;
    return os;
}
