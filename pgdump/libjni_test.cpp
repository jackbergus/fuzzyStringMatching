//
// Created by giacomo on 23/09/18.
//

#include <unordered_map>
#include <iostream>
#include <cmath>
#include <functional>
#include <unordered_set>
#include "../serializers/utils/NumberToString.h"
#include "../serializers/commons/secondary_memory/utils/Graph.h"
#include "../serializers/commons/globals.h"
#include "../serializers/commons/secondary_memory/queryresult.h"
#include "../serializers/commons/secondary_memory/JOINRESULT.h"

// ???
struct id_dst {
    LONG_NUMERIC edgeId;
    LONG_NUMERIC dst;
    id_dst(LONG_NUMERIC eid, LONG_NUMERIC dst) : edgeId{eid}, dst{dst} {};

    bool operator<(const id_dst &rhs) const {
        if (dst < rhs.dst)
            return true;
        if (rhs.dst < dst)
            return false;
        return edgeId < rhs.edgeId;
    }
};

namespace std {
    template<>
    class hash<id_dst> {
    public:
        size_t operator()(const id_dst &s) const {
            return (s.dst) ^ (s.edgeId << 1);
        }
    };
};

inline bool operator==(const struct id_dst& lhs, const struct id_dst& rhs){ return (lhs.edgeId == rhs.edgeId) && (lhs.dst == rhs.dst); }

Graph graph{};

const std::vector<std::string> relationships({"Antonym","AtLocation","CapableOf","Causes","CausesDesire","CreatedBy","DefinedAs","DerivedFrom","Desires","DistinctFrom","Entails","EtymologicallyDerivedFrom","EtymologicallyRelatedTo","ExternalURL","FormOf","HasA","HasContext","HasFirstSubevent","HasLastSubevent","HasPrerequisite","HasProperty","HasSubevent","InstanceOf","IsA","LocatedNear","MadeOf","MannerOf","MotivatedByGoal","NotCapableOf","NotDesires","NotHasProperty","NotUsedFor","ObstructedBy","PartOf","ReceivesAction","RelatedTo","SimilarTo","SymbolOf","Synonym","UsedFor","dbpedia_capital","dbpedia_field","dbpedia_genre","dbpedia_genus","dbpedia_influencedBy","dbpedia_knownFor","dbpedia_language","dbpedia_leader","dbpedia_occupation","dbpedia_product"});
std::unordered_map<unsigned long, std::string> relationshipId;
void initializeRelationships() {
    unsigned long pow2 = 2;
    for (const std::string & s : relationships) {
        relationshipId[pow2] = s;
        pow2 *= 2;
    }
}


std::vector<std::string> query(LONG_NUMERIC node, bool ingoing, unsigned long relBitMap) {
    header *v = vertex_offset(graph.begin, node);
    LONG_NUMERIC n = ingoing ? vertex_ingoing_edges_len(v) : vertex_outgoing_edges_len(v);
    edges_in_vertices* vec = ingoing ? vertex_ingoing_edges_vec(v) : vertex_outgoing_edges_vec(v);
    std::vector<std::string> toRet;
    for (LONG_NUMERIC i = 0; i<n; i++) {
        if (vec[i].edgeHash & relBitMap) {
            std::string str{graph.resolveEdgeValue(vec[i].edgeId)};
            toRet.push_back(str);
        }
    }
    return toRet;
}

#ifndef IS_LIBRARY
void oldReder() {
    header *v = (header*)(((char*)graph.begin)+0);
    //for (; v < graph.end; v = vertex_next(v)) {
        LONG_NUMERIC hash = vertex_hash(v);
        LONG_NUMERIC id = vertex_id(v);
        LONG_NUMERIC propLen = vertex_properties_len(v);
        if (propLen == 1) {
            char* nodeId = vertex_property_ith_value(v, 0);
            std::cout << "vertex " << nodeId << " of id " << id << " and hash " << hash << std::endl;
        }

        LONG_NUMERIC out = vertex_outgoing_edges_len(v);
        if (out > 0) {
            std::cout << "\tOutgoing edges" << std::endl;
            struct edges_in_vertices* outPtr = vertex_outgoing_edges_vec(v);
            for (LONG_NUMERIC i = 0; i<out; i++) {
                LONG_NUMERIC eid = outPtr[i].edgeId;
                std::cout << "\t * Id=" << eid << " Relationship=" << std::to_string(outPtr[i].edgeHash) << std::endl;
                std::cout << "\t   " << graph.resolveEdgeValue(eid) << std::endl;
            }
        }

        LONG_NUMERIC in = vertex_ingoing_edges_len(v);
        if (in > 0) {
            std::cout << "\tIngoing edges" << std::endl;
            struct edges_in_vertices* outPtr = vertex_ingoing_edges_vec(v);
            for (LONG_NUMERIC i = 0; i<in; i++) {
                LONG_NUMERIC eid = outPtr[i].edgeId;
                std::cout << "\t * Id=" << eid << " Relationship=" << std::to_string(outPtr[i].edgeHash) << std::endl;
                std::cout << "\t   " << graph.resolveEdgeValue(eid) << std::endl;
            }
        }

        std::cout << std::endl << std::endl << "-- Press Enter to Continue: ";
        std::string str;
        std::getline(std::cin, str);
    //}
}


int main() {
    initializeRelationships();
    graph.open();
    for (std::string& s : query(125438203, false, 549755813892))
        std::cout << s << std::endl;
    graph.clos();
}
#endif