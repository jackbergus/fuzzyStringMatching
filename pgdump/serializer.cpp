#include <iostream>
#include <fstream>
#include <iomanip>

#define SERIALIZE_EDGE
#define SERIALIZE_OFFSET

#include "json.hpp"
#include "../fromJava/evaluateHashes.h"
#include "../serializers/commons/primary_memory/entity_relationship.h"
#include "../serializers/commons/secondary_memory/header.h"
#include "../serializers/commons/Serialize.h"
#include "../serializers/commons/secondary_memory/primary_index.h"
#include "../rbtree/rbtree.h"
#include "../numeric/compares.h"
#include <unistd.h>


#include <string.h>
#include <stdlib.h>
#include <functional>

bool replace(std::string& str, const std::string& from, const std::string& to) {
    std::string::size_type n = 0;
    while ( ( n = str.find( from, n ) ) != std::string::npos )
    {
        str.replace( n, from.size(), to );
        n += to.size();
    }
    return n > 0;
}

//std::hash<std::string> hash_fn;

char* strpos(const char *haystack, const char *needle, int nth)
{
    char *res = (char*)haystack;
    for(int i = 1; i <= nth; i++)
    {
        res = strstr(res, needle);
        if (!res)
            return NULL;
        else if(i != nth)
            res = res+1;
    }
    return res+1;
}

std::unordered_map<std::string, unsigned long> nodeToId;
std::unordered_map<unsigned long, std::string> idToNode;

std::pair<std::unordered_map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, unsigned long>::iterator, bool>
resolveNode(std::string& nodeId, unsigned long id) {
    const std::pair<std::unordered_map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, unsigned long>::iterator, bool> &cp = nodeToId.insert(std::make_pair(nodeId, id));
    if (cp.second) {
        idToNode[id] = nodeId;
    }
    return cp;
}


const std::vector<std::string> relationships({"Antonym","AtLocation","CapableOf","Causes","CausesDesire","CreatedBy","DefinedAs","DerivedFrom","Desires","DistinctFrom","Entails","EtymologicallyDerivedFrom","EtymologicallyRelatedTo","ExternalURL","FormOf","HasA","HasContext","HasFirstSubevent","HasLastSubevent","HasPrerequisite","HasProperty","HasSubevent","InstanceOf","IsA","LocatedNear","MadeOf","MannerOf","MotivatedByGoal","NotCapableOf","NotDesires","NotHasProperty","NotUsedFor","ObstructedBy","PartOf","ReceivesAction","RelatedTo","SimilarTo","SymbolOf","Synonym","UsedFor","capital","field","genre","genus","influencedBy","knownFor","language","leader","occupation","product"});
std::unordered_map<std::string, unsigned long> relationshipId;
void initializeRelationships() {
    unsigned long pow2 = 2;
    for (const std::string & s : relationships) {
        relationshipId[s] = pow2;
        pow2 *= 2;
    }
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main() {
    std::ifstream file("/media/giacomo/3844311f-c5bc-4422-b67c-3e26e796c95d/conceptnet5/data/psql/edges.csv");
    std::string line;
    std::string isConceptNet = "/c/";
    std::string isRelationship = "/r/";
    std::string isDBPediaRelationship = "/r/dbpedia/";
    const char* element = const_cast<char *>("\t");
    const std::string isNoun("/n");
    unsigned long countId = 0;
    unsigned long edgeId = 0;
    std::vector<std::string> edgeValue{};

    std::string quoteb{"\\\\"};
    std::string quotee{"\\"};
    initializeRelationships();

    RBTree<LONG_NUMERIC, edges_in_vertices> outTree{&compareUL_Int};

    //Preloading the mapping from nodeId to offset
    int i;

    // Edge information providing the content
//#ifdef SERIALIZE_EDGE
    FILE* edgeP = fopen64("edge_primary.bin", "w");
    FILE* edgeV = fopen64("edge_values.bin", "w");
    unsigned long offsetEdge = 0;
//#endif
    // While traversing the vertices
    while (std::getline(file, line)) {
        std::string edgeValueToSerialize{strpos(line.c_str(), element, 6)};

        // Preserving the extracted string
        std::string original{edgeValueToSerialize};

//#ifndef NOOTHER
        // the to-be-parsed string has some issues to be parsed in C++, while it is perfectly recognized in Java.
        // Therefore, I have to do a twick, only to extract the relevant fields
        replace(edgeValueToSerialize, quoteb, quotee);
        //try {

            auto j = nlohmann::json::parse(edgeValueToSerialize);

            // For both start and end, those must not be adjectives or verbs. Moreover, they must come ConceptNet
            // Moreover, the noun information is stripped
            std::string start = j["start"];
            if (hasEnding(start, "/a")) continue;
            if (hasEnding(start, "/v")) continue;
            if (start.compare(0, isConceptNet.size(), isConceptNet)) continue;
            if (start.substr(start.size() - isNoun.size()) == isNoun) {
                start = start.substr(0, start.size() - isNoun.size());
            }
            const std::pair<std::unordered_map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, unsigned long>::iterator, bool> &resolveStart = resolveNode(
                    start, countId);
            if (resolveStart.second) {
                countId++;
            }
            unsigned long startId = resolveStart.first->second;

            std::string end = j["end"];
            if (hasEnding(end, "/a")) continue;
            if (hasEnding(end, "/v")) continue;
            if (end.compare(0, isConceptNet.size(), isConceptNet)) continue;
            if (end.substr(end.size() - isNoun.size()) == isNoun) {
                end = end.substr(0, end.size() - isNoun.size());
            }
            const std::pair<std::unordered_map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>, unsigned long>::iterator, bool> &resolveEnd = resolveNode(
                    end, countId);
            if (resolveEnd.second) {
                countId++;
            }
            unsigned long endId = resolveEnd.first->second;

            std::string rel = j["rel"];
            replace(rel, isDBPediaRelationship, "");
            replace(rel, isRelationship, "");

            unsigned long edgeHash = relationshipId[rel];
//#endif

//#ifdef SERIALIZE_EDGE
            // writing the edge information into secondary memory
            fwrite(&offsetEdge, sizeof(offsetEdge), 1, edgeP);
            LONG_NUMERIC size = original.size()+1;
            fwrite(original.c_str(), size, 1, edgeV);
            offsetEdge += size;
            /*if ((start == ("/c/en/weapon")) || (end == ("/c/en/weapon"))) {
                //std::cout << "weapon id =" << startId << " == " << endId << std::endl;
                std::cout << "edge id =" << edgeId    << " with value = " << original << std::endl;
                //std::cout << rel << " -> " << std::to_string(edgeHash) << std::endl;
                std::cout << "--" << std::endl;
            }*/
//#endif

//#ifndef NOOTHER
            {
                Node<LONG_NUMERIC, edges_in_vertices> *n = outTree.insertKey(startId);
                n->overflowList.emplace_back(edgeId, edgeHash, endId, 0);
            }
            // ingoing edges have odd numbers
            {
                Node<LONG_NUMERIC, edges_in_vertices> *n = outTree.insertKey(endId);
                n->overflowList.emplace_back(edgeId, edgeHash + 1, startId,0);
            }
//#endif
            //std::cout << startId << ", " << endId << ", " << start << ", " << end << std::endl;
            edgeId++;
            /*if (edgeId % 10000 == 0)
                std::cout << (edgeId)/1000 << " k" << std::endl;*/
            if (edgeId/10000 == 0) {
//#ifdef SERIALIZE_EDGE
                fflush(edgeP);
                fflush(edgeV);
//#endif
            }
        /*} catch (...) {
            std::cout << edgeValueToSerialize << std::endl << std::endl;
            std::cout << original << std::endl;
            continue;
        }*/
    }
//#ifdef SERIALIZE_EDGE
    fclose(edgeP);
    fclose(edgeV);
//#endif
//#ifdef NOOTHER
//    exit(0);
//#endif
    std::cout << "\tFinally serializing the vertices" << std::endl;

    // No more hashing associated to the vertices
    LONG_NUMERIC prevHash = 0;

    // The first offset is located at position zero
    LONG_NUMERIC offsetValues = 0;

    // Adjacency list
    //FILE* hashF = fopen64("vertex_hashing.bin", "w");
    FILE* secoF = fopen64("vertex_values.bin", "w");

    RBTree<LONG_NUMERIC,std::pair<LONG_NUMERIC , LONG_NUMERIC >> fixtree{&compareUL_Int};
    {
        RBTree<LONG_NUMERIC , edges_in_vertices>::rbiterator it = outTree.iterator();
        while (it.hasNext()) {
            Node<LONG_NUMERIC, edges_in_vertices> *current = it.disposeWhileIterating();
            /*if (((LONG_NUMERIC )current->key.first) != prevHash) {
                prevHash = current->key.first;
                struct hashIndex hashWrite{prevHash, offsetValues};
                fwrite(&hashWrite, sizeof(struct hashIndex), 1, hashF);
            }*/
            fixtree.insertKey(current->key)->add(prevHash, offsetValues);

            // the vertex is defined by id (second) and hash (first)
            ERvertex evertex{current->key, 0};
            for (struct edges_in_vertices& x : current->overflowList) {
                // detecting the difference between ingoing and outgoing by just having an odd hashing or not.
                // the hash value is still the same.
                if (x.edgeHash & 1) {
                    evertex.ingoingEdges.emplace_back(x.edgeId,x.edgeHash-1);//renormalizing the edge hash for correctly storing it in secondary memory
                    evertex.ingoingEdges_vertices.emplace_back(x.vertexId, x.vertexHash);
                    if (x.vertexId == 50134 || current->key == 50134)
                    std::cout << std::to_string(x.edgeId) << "-" << std::to_string(x.edgeHash-1) << "-"<< std::to_string(x.vertexId) << "-" << std::to_string(x.vertexHash) << std::endl;
                } else {
                     evertex.outgoingEdges.emplace_back(x.edgeId,x.edgeHash);
                     evertex.outgoingEdges_vertices.emplace_back(x.vertexId, x.vertexHash);
                    if (x.vertexId == 50134 || current->key == 50134)
                        std::cout << std::to_string(x.edgeId) << "-" << std::to_string(x.edgeHash) << "-"<< std::to_string(x.vertexId) << "-" << std::to_string(x.vertexHash) << std::endl;
                }

            }

            // associating the vertex with some values, that is the only value that it is stored inside the vertex.
            evertex.properties.emplace_back("id", idToNode[current->key]);
            offsetValues += serialize(&evertex, secoF);
        }
    }
    //fclose(hashF);
    fclose(secoF);

//#ifdef SERIALIZE_OFFSET
    //FILE* primF = fopen64("vertex_secondary.bin", "w");
    std::ofstream csvVertexOffsetByString;
    csvVertexOffsetByString.open("nodes_name_to_offset.csv", std::ofstream::binary);
    RBTree<LONG_NUMERIC, std::pair<LONG_NUMERIC, LONG_NUMERIC>>::rbiterator iit = fixtree.iterator();
    while (iit.hasNext()) {
        Node<LONG_NUMERIC, std::pair<LONG_NUMERIC, LONG_NUMERIC>> *current = iit.disposeWhileIterating();
        // id, hash, offset
        //struct primary_index pix{current->key, current->overflowList[0].first, current->overflowList[0].second};
        //fwrite(&pix, sizeof(struct primary_index), 1, primF);
        std::string vertexNameToOffset = idToNode[current->key] + "," + std::to_string(current->overflowList[0].second) +"\n";
        csvVertexOffsetByString.write(vertexNameToOffset.c_str(), vertexNameToOffset.length());
    }
    csvVertexOffsetByString.close();
    //fclose(primF);
//#endif


}