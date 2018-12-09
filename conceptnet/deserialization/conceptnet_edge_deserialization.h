//
// Created by giacomo on 17/10/18.
//

#ifndef INCONSISTENCY_CONCEPTNET_EDGE_DESERIALIZATION_H
#define INCONSISTENCY_CONCEPTNET_EDGE_DESERIALIZATION_H

#include <iostream>
#include "rapidjson/reader.h"
#include "../../relationships/RelationshipTypes.h"
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

using namespace rapidjson;
using namespace std;

/**
 * Vertex associated to the graph
 */
struct conceptnet_vertex {
    std::string id;
    std::string surface;
    std::string language;
    std::string sense;
    friend ostream &operator<<(ostream &os, const conceptnet_vertex &vertex);
};

/**
 * This class describes the pieces of information associated to each element.
 */
class conceptnet_edge_deserialization {
    std::string currentKey;
    std::stack<bool> isCurrentAnAtomicValue{};
    bool isObjectStarted = true;

    /**
     * Finalization process, in order to map into one single class all the former representations of the java object
     */
    void finalizeObject();

public:
    bool symmetry = false;
    bool negated = false;

    /**
     * This function allows to deserialize the json-string object into the current instance object without allocating
     * any intermediate DOM. This process enhances the deserialization process without
     * @param json      Serialized representation as a string
     * @param reader    Element providing the parsing for the current object.
     */
    void readFromChars(const char json[], Reader& reader);

    /// Arguments


    /*std::string start;
    std::string surfaceStart;
    std::string src_language;
    std::string src_senseLabel;*/
    /*std::string end_;
std::string surfaceEnd;
std::string dst_language;
std::string dst_senseLabel;*/


    conceptnet_vertex vStart;
    conceptnet_vertex vEnd;
    std::string rel;
    RelationshipTypes relType;
    std::string surfaceText;
    std::string dataset;
    double weight;

    //std::string uri;
    //std::string license;
    // legacy: ArrayList<ObjectNode> sources;
    //std::vector<std::string> features;

    // Pretty Printer

    // Parser's event hanlders / triggers:
    bool Null();
    bool Bool(bool b);
    bool Int(int i);
    bool Uint(unsigned u);
    bool Int64(int64_t i);
    bool Uint64(uint64_t u);
    bool Double(double d);
    bool String(const char* str, SizeType length, bool copy);
    bool RawNumber(const char* str, SizeType length, bool copy);
    bool StartObject();
    bool Key(const char* str, SizeType length, bool copy);
    bool EndObject(SizeType memberCount);
    bool StartArray();
    bool EndArray(SizeType elementCount);

    friend ostream &operator<<(ostream &os, const conceptnet_edge_deserialization &deserialization);

    conceptnet_edge_deserialization();;
    conceptnet_edge_deserialization(conceptnet_edge_deserialization&& cc);
};

// Java backward compatibility macros. In this way I map the new classes into the old ones without the cost of re-mapping an object.
// I'll just simply flatten the representation

#define EDGE_ISSYMMETRY(x)          (((conceptnet_edge_deserialization*)x)->symmetry)
#define EDGE_ID(x)                  (((conceptnet_edge_deserialization*)x)->uri)
#define EDGE_WEIGHT(x)              (((conceptnet_edge_deserialization*)x)->weight)
#define EDGE_REL_ID(x)              (((conceptnet_edge_deserialization*)x)->rel)
#define EDGE_REL_LABEL(x)           EDGE_ID(x)

// Some edge rewriting macros that are unaware (_U*) of whether the edge is symmetrical or not
#define EDGE_USTART_ID(x)            (((conceptnet_edge_deserialization*)x)->vStart.id)
#define EDGE_USTART_POS(x)           (((conceptnet_edge_deserialization*)x)->vStart.semse)
#define EDGE_USTART_LAN(x)           (((conceptnet_edge_deserialization*)x)->vStart.language)
#define EDGE_USTART_LABEL(x)         (((conceptnet_edge_deserialization*)x)->vStart.surface)
#define EDGE_UEND_ID(x)            (((conceptnet_edge_deserialization*)x)->vEnd.id)
#define EDGE_UEND_LAN(x)           (((conceptnet_edge_deserialization*)x)->vEnd.language)
#define EDGE_UEND_POS(x)           (((conceptnet_edge_deserialization*)x)->vEnd.sense)
#define EDGE_UEND_LABEL(x)         (((conceptnet_edge_deserialization*)x)->vEnd.surface)
#define EDGE_RELTYPE(x)         (((conceptnet_edge_deserialization*)x)->relType)

#define EDGE_START_ID(x)            (EDGE_ISSYMMETRY(x) ? EDGE_UEND_ID(x) : EDGE_USTART_ID(x))
#define EDGE_END_ID(x)              ((!EDGE_ISSYMMETRY(x)) ? EDGE_UEND_ID(x) : EDGE_USTART_ID(x))
#define EDGE_START_POS(x)           (EDGE_ISSYMMETRY(x) ? EDGE_UEND_POS(x) : EDGE_USTART_POS(x))
#define EDGE_END_POS(x)             ((!EDGE_ISSYMMETRY(x)) ? EDGE_UEND_POS(x) : EDGE_USTART_POS(x))
#define EDGE_START_LAN(x)           (EDGE_ISSYMMETRY(x) ? EDGE_UEND_LAN(x) : EDGE_USTART_LAN(x))
#define EDGE_END_LAN(x)             ((!EDGE_ISSYMMETRY(x)) ? EDGE_UEND_LAN(x) : EDGE_USTART_LAN(x))
#define EDGE_START_LABEL(x)         (EDGE_ISSYMMETRY(x) ? EDGE_UEND_LABEL(x) : EDGE_USTART_LABEL(x))
#define EDGE_END_LABEL(x)           ((!EDGE_ISSYMMETRY(x)) ? EDGE_UEND_LABEL(x) : EDGE_USTART_LABEL(x))
#define EDGE_START_VALUE(x)         EDGE_START_LABEL(x)
#define EDGE_END_VALUE(x)           EDGE_END_LABEL(x)

#define EDGE_notVerbOrAdjective(x)  (EDGE_START_POS(x).empty() || (EDGE_START_POS(x) == "n"))
#define EDGE_isAnglophone(x)        ((EDGE_START_LAN(x) == "en") && (EDGE_END_LAN(x) == "en"))
#define EDGE_anglophoneAndNotVerbOrAdjective(x)     (EDGE_isAnglophone(x) && EDGE_notVerbOrAdjective(x))

#define EDGE_isType(x, T)             isA(EDGE_ISSYMMETRY(x), T, EDGE_RELTYPE(x))

#define EDGE_SRC_getSemanticId(x)   EDGE_START_ID(x)

#endif //INCONSISTENCY_CONCEPTNET_EDGE_DESERIALIZATION_H
