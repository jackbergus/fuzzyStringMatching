//
// Created by giacomo on 17/10/18.
//

#include "conceptnet_edge_deserialization.h"
#include "../utils.h"


// Pretty Printer
ostream &operator<<(ostream &os, const conceptnet_edge_deserialization &handler) {
    os << "{ weight: " << handler.weight << "\n start: "
       << handler.start << "\n end_: " << handler.end_ << "\n rel: " << handler.rel /*<< "\n uri: " << handler.uri*/
       <</* "\n license: " << handler.license <<*/ "\n surfaceText: " << handler.surfaceText << "\n surfaceStart: "
       << handler.surfaceStart << "\n surfaceEnd: " << handler.surfaceEnd << "\n dataset: " << handler.dataset
       /*<< "\n features: [" << std::accumulate(handler.features.begin(), handler.features.end(), std::string("; "))*/ << "]}";
    return os;
}

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
        this->start = str;
    } else if (currentKey == "end") {
        this->end_ = str;
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
        this->surfaceStart = str;
    } else if (currentKey == "surfaceEnd") {
        this->surfaceEnd = str;
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
    if (surfaceStart.empty()) {
        surfaceStart = unrectify(start);
    }
    if (surfaceEnd.empty()) {
        surfaceEnd = unrectify(end_);
    }

    size_t next = 0, pos = 0, count = 0, c = 0;
    while ((next = start.find('/', pos)) != std::string::npos) {
        if (count == 2) {
            c = (start.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == start.length() ? "" :
                                start.substr(pos+1,(test ? c-pos-1 : start.length()));
            this->src_language = toret;
        } else if (count == 4) {
            c = (start.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == start.length() ? "" :
                                start.substr(pos+1,(test ? c-pos-1 : start.length()));
            this->src_senseLabel = start.substr(pos, next);
        }
        count++;
        pos = start.find('/', next+1);
    }

    next = 0, pos = 0, count = 0;
    while ((next = end_.find('/', pos)) != std::string::npos) {
        if (count == 2) {
            c = (end_.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == end_.length() ? "" :
                                end_.substr(pos+1,(test ? c-pos-1 : end_.length()));
            this->dst_language = toret;
        } else if (count == 4) {
            c = (end_.find('/', pos+1));
            bool test = c != std::string::npos;
            std::string toret = next == end_.length() ? "" :
                                end_.substr(pos+1,(test ? c-pos-1 : end_.length()));
            this->dst_senseLabel = toret;
        }
        count++;
        pos = start.find('/', next+1);
    }

    std::string res{splitOnce(rel, slash, 10)};
    relType = res.empty() ? RelationshipTypes::ExternalURL : static_cast<RelationshipTypes>(enumMap.at(res));
    negated = res.empty() ? false : SemanticEdge_isNegated(relType);
    if (!isPreferredDirection_normal(relType)) {
        symmetry = true;
    }
}
