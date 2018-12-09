//
// Created by giacomo on 09/11/17.
//

#include <iostream>
#include <boost/filesystem/path.hpp>
#include "../random/RandomGMarkFile.h"
#include "utils/NumberToString.h"
#include "collections/GraphCollectionSerializeSteps.h"
#include "collections/collection_consts.h.h"
#include "commons/primary_memory/entity_relationship.h"
#include "../rbtree/rbtree.h"
#include "../numeric/compares.h"
#include "commons/secondary_memory/primary_index.h"
#include "commons/Serialize.h"

#include <boost/dynamic_bitset.hpp>
#include <boost/filesystem/operations.hpp>

FILE* benchmark = nullptr;
#define TIME()          (std::clock())
#define EVAL(c)         ((double)((double)(std::clock() - c))/(CLOCKS_PER_SEC / 1000.0))

void serializeOperand(std::string basic_string, std::string basicString, unsigned long i);

void help() {
    std::cout << std::left
              << "This program takes as an input a file containing" << std::endl
              << "the Graph collection, a number expressing the" << std::endl
              << "size of such collection, the number of vertices." << std::endl
              << std::endl
              << "Each Graph collection is represented in" << std::endl
              << "the (extended) gMark format, where each line is defined as follows: "
              << std::endl
              << std::endl
              << "edgeId: idsrc EdgeLabel iddst"
              << std::endl
              << std::endl
              << "In particular, this serialization is performed over" << std::endl
              << "the bibliography network example, where all the edges" << std::endl
              << "are the same, and where each source is an author and" << std::endl
              << "each target is a paper. The data is serialized accor-" << std::endl
              << "dingly. Moreover, the Graph collection will be seria-" << std::endl
              << "lized as one GSM, where the first element is the" << std::endl
              << "entry point of the collection, all the following N" << std::endl
              << "elements are the graphs of the collections, and all" << std::endl
              << "the remaining objects are both the vertices and edges" << std::endl
              << "within each collection. ";
}


void serializer(std::string &serializationTarget, LONG_NUMERIC collectionSize) {
    boost::filesystem::path basePathSerialize{serializationTarget+"_ser"};
    boost::filesystem::path primary = basePathSerialize / "primary.bin";
    boost::filesystem::path values = basePathSerialize / "values.bin";
    boost::filesystem::create_directory(basePathSerialize);
    std::cerr << "Serialize to = " << basePathSerialize.c_str() << std::endl;

    FILE* primaryF = fopen64(primary.c_str(), "w");
    FILE* values_F = fopen64(values.c_str(),  "w");

    RandomGMarkFile file{serializationTarget, false};
    LONG_NUMERIC currentContainer = 1;
    RBTree<std::pair<unsigned long, unsigned long>, ERvertex> tree{&pairCompare};
    LONG_NUMERIC nextOffset = 0;

    if (file.hasNextEdge()) {
        nextOffset = serializeGraphCollectionEntryPoint(values_F, primaryF, nextOffset, collectionSize);
    }

    while (file.hasNextEdge()) {
        bool set = false;
        std::string extendedCurrentLine = file.readNextEdgeAsString();
        ERvertex container;
        container.hash = GRAPH_HASH;
        container.id = currentContainer++;

        {
            std::set<LONG_NUMERIC> vertexContainment;

            while (extendedCurrentLine.size()>0) {
                set = true;
                struct vertex v;
                unsigned long posColon = extendedCurrentLine.find(':');
                std::string _edgeId = extendedCurrentLine.substr(0,posColon);
                LONG_NUMERIC edgeIdN = StringToNumber<LONG_NUMERIC>(_edgeId);
                std::string currentLine = extendedCurrentLine.substr(extendedCurrentLine.find(':')+1);
                file.readVertex(&v, edgeIdN, currentLine);
                v.srcId = COLLECTION_ELEMENT_CONTENT_ID(v.srcId, collectionSize);
                v.dstId = COLLECTION_ELEMENT_CONTENT_ID(v.dstId, collectionSize);
                if (file.hasNextEdge())
                    extendedCurrentLine = file.readNextEdgeAsString();
                else
                    extendedCurrentLine = "";
                container.edge_containment.emplace_back(edgeIdN);
                vertexContainment.insert(v.srcId);
                vertexContainment.insert(v.dstId);
            }

            // Copying the elements linearly
            container.vertex_containment.reserve(vertexContainment.size());

            std::copy(vertexContainment.begin(), vertexContainment.end(), std::back_inserter(container.vertex_containment));
            // Sorting the edges by id
            std::sort(container.edge_containment.begin(), container.edge_containment.end());


        } // disposing the set

        if (set) {
            nextOffset = serializeGraphEntryPoint(values_F, primaryF, nextOffset, container);
        }

    }

    fclose(primaryF);
    fclose(values_F);
}

void serializeCollections(std::string &basePath, std::string baseFolderName, unsigned long int iteration) {
    boost::filesystem::path basePathSerialize{basePath};
    std::string paceStirng = NumberToString<unsigned long int>(iteration);
    baseFolderName += "_operands";
    baseFolderName = baseFolderName.replace(baseFolderName.find('*'),paceStirng.size(),paceStirng);
    boost::filesystem::path currentFolder = basePathSerialize / baseFolderName;

    LONG_NUMERIC nVertex = (LONG_NUMERIC )std::pow((long double) 10, (long double)iteration);

    std::cout << "Now Serializing = " << currentFolder.string() << std::endl;
    boost::filesystem::path sizes = currentFolder / "count.txt";
    std::fstream myfile(sizes.c_str(), std::ios_base::in);
    LONG_NUMERIC edgeSize, vertexSize;
    myfile >> edgeSize >> vertexSize;

    std::cout << "\tSerializing edges" << std::endl;
    std::string edges = (currentFolder / "edge_multigraphs.txt").string();

    clock_t edgeTime = TIME();
    serializer(edges, edgeSize);
    double eColl = EVAL(edgeTime);

    std::cout << "\tSerializing vertices" << std::endl;
    std::string vertices = (currentFolder / "vertex_multigraphs.txt").string();

    clock_t vertexTime = TIME();
    serializer(vertices, vertexSize);
    double vColl = EVAL(vertexTime);

    std::string toWrite = "collections," + NumberToString<unsigned long>((unsigned long)std::pow(10.0,iteration+1)) + "," + NumberToString<double>(vColl+eColl) + "\n";
    fwrite(toWrite.c_str(),toWrite.size(),1,benchmark);
    fflush(benchmark);

}

void serializeOperand(std::string basic_string, std::string basicString, unsigned long iteration) {
    std::string paceStirng = NumberToString<unsigned long int>(iteration);
    basicString = basicString.replace(basicString.find('*'),paceStirng.size(),paceStirng);
    boost::filesystem::path header(basic_string);
    boost::filesystem::path currentFolder = header / basicString;
    RandomGMarkFile file{currentFolder.string(), false};

    std::cout << "Now Serializing = " << currentFolder.string() << std::endl;
    std::cout << "\tIndexing the file in primary memory" << std::endl;

    // ELEMENT_LABEL_HASH(0) = PaperId
    // ELEMENT_LABEL_HASH(1) = AuthorId
    // ELEMENT_LABEL_HASH(3) = edge hash
    clock_t time = TIME();
    RBTree<std::pair<unsigned long,unsigned long>, edges_in_vertices> tree{&pairCompare};
    LONG_NUMERIC edgeId = 0;
    while  (file.hasNextEdge()) {
        struct vertex v;
        file.readNextEdge(&v, edgeId++);
        if (!file.readError()) {
            {
                Node<std::pair<unsigned long, unsigned long>, edges_in_vertices> *n = tree.insertKey(std::make_pair(ELEMENT_LABEL_HASH(1), v.srcId));
                n->overflowList.emplace_back(v.edgeId, ELEMENT_LABEL_HASH(3), v.dstId, ELEMENT_LABEL_HASH(0));
            }
            {
                Node<std::pair<unsigned long, unsigned long>, edges_in_vertices> *n = tree.insertKey(std::make_pair(ELEMENT_LABEL_HASH(0), v.dstId));
                n->overflowList.emplace_back(v.edgeId, ELEMENT_LABEL_HASH(3), v.srcId, ELEMENT_LABEL_HASH(1));
            }
        }
    }

    boost::filesystem::path serFolder = header / (basicString+"_ser");
    boost::filesystem::create_directory(serFolder);

    boost::filesystem::path hash = serFolder / "hash.bin";
    FILE* hashF = fopen64(hash.c_str(), "w");

    boost::filesystem::path seco = serFolder / "values.bin";
    FILE* secoF = fopen64(seco.c_str(), "w");

    std::cout << "\tFinally serializing" << std::endl;

    LONG_NUMERIC prevHash = std::numeric_limits<LONG_NUMERIC>::max();
    LONG_NUMERIC offsetValues = 0;
    RBTree<LONG_NUMERIC,std::pair<LONG_NUMERIC , LONG_NUMERIC >> fixtree{&compareUL_Int};
    {
        RBTree<std::pair<unsigned long, unsigned long>, edges_in_vertices>::rbiterator it = tree.iterator();
        while (it.hasNext()) {
            Node<std::pair<unsigned long, unsigned long>, edges_in_vertices> *current = it.disposeWhileIterating();
            if (((LONG_NUMERIC )current->key.first) != prevHash) {
                prevHash = current->key.first;
                struct hashIndex hashWrite{prevHash, offsetValues};
                fwrite(&hashWrite, sizeof(struct hashIndex), 1, hashF);
            }
            fixtree.insertKey(current->key.second)->add(prevHash, offsetValues);
            ERvertex evertex{current->key.second, current->key.first};
            for (struct edges_in_vertices& x : current->overflowList) {
                // Author
                if (current->key.first == ELEMENT_LABEL_HASH(1)) {
                    evertex.outgoingEdges.emplace_back(x.edgeId,x.edgeHash);
                    evertex.outgoingEdges_vertices.emplace_back(x.vertexId, x.vertexHash);
                } else if (current->key.first == ELEMENT_LABEL_HASH(0)) {
                    evertex.ingoingEdges.emplace_back(x.edgeId,x.edgeHash);
                    evertex.ingoingEdges_vertices.emplace_back(x.vertexId, x.vertexHash);
                }

            }
            offsetValues += serialize(&evertex, secoF);
        }
    }
    fclose(hashF);
    fclose(secoF);

    boost::filesystem::path prim = serFolder / "secondary.bin";
    FILE* primF = fopen64(prim.c_str(), "w");
    RBTree<LONG_NUMERIC, std::pair<LONG_NUMERIC, LONG_NUMERIC>>::rbiterator iit = fixtree.iterator();
    while (iit.hasNext()) {
        Node<LONG_NUMERIC, std::pair<LONG_NUMERIC, LONG_NUMERIC>> *current = iit.disposeWhileIterating();
        struct primary_index pix{current->key, current->overflowList[0].first, current->overflowList[0].second};
        fwrite(&pix, sizeof(struct primary_index), 1, primF);
    }
    fclose(primF);

    double secs = EVAL(time);
    std::string toWrite = "operand," + NumberToString<unsigned long>((unsigned long)std::pow(10.0,iteration+1)) + "," + NumberToString<double>(secs) + "\n";
    fwrite(toWrite.c_str(),toWrite.size(),1,benchmark);
    fflush(benchmark);

}

int main(int argc, char* argv[]) {

    if (argc <= 3) {
        help();
    } else {
        boost::filesystem::path bfp{"benchmark_serialization.csv"};
        bool writeHeader = (boost::filesystem::exists(bfp));
        benchmark = fopen64("benchmark_serialization.csv","wa");
        if (writeHeader) {
            std::string header = "operation,size,msec\n";
            fwrite(header.c_str(), header.size(), 1, benchmark);
        }
        std::string basePath{argv[1]};
        std::string baseFolderName{argv[2]};

        std::string startIteration{argv[3]};
        unsigned long int min = StringToNumber<unsigned long int>(startIteration);

        std::string endIteration{argv[4]};
        unsigned long int max = StringToNumber<unsigned long int>(endIteration);

        for (unsigned long int i = min; i<=max; i++) {
            serializeOperand(basePath, baseFolderName, i);
            //serializeCollections(basePath, baseFolderName, i);
        }
        fclose(benchmark);
        benchmark = nullptr;
    }

}

