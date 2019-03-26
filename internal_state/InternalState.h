//
// Created by giacomo on 13/10/18.
//

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "../datasets/helpers/Helpers.h"
#include "../utils/fixed_bimap.h"
#include "../serializers/commons/structure.h"
#include "../merging/conceptnet/deserialization/conceptnet5_vertex.h"
#include "../merging/jsons/idToOffsetHandler.h"
#include "../merging/jsons/objectToMultipleStrings.h"
#include "../merging/fuzzymatch/FuzzyMatch.h"
#include <iostream>

#ifndef INCONSISTENCY_INTERNALSTATE_H
#define INCONSISTENCY_INTERNALSTATE_H

#include <fstream>

/**
 * This class represents the main entrypoint that preserves the state of the current computation.
 * This also includes the objects that are currently opened and closed.
 *
 */
class InternalState {
    double fuzzyMatchThreshold;
    int fuzzyMatchTopK;
public:
    rapidjson::Document hypothesis;
    rapidjson::Document configuration;

    /**
     * This map univocally associates each ConceptNet url (in its non-basic form) into the id/offset of where such
     * vertex is stored within the serialized representation. This map is a non-mutable bijection, and therefore
     * the key might be searched to find the value and viceversa.
     */
    fixed_bimap<std::string, LONG_NUMERIC> non_3basicid_to_offset;

    /**
     * This map univocally associatetes each basic-form id into the overall vertex information that is required
     * to traverse the graph.
     */
    std::unordered_map<std::string, conceptnet5_vertex> vertex_main_id_to_vertex_information;

    FuzzyMatch hierarchiesForFuzzyMatch;

    // Legacy: helpers for parsing document representation.... Not needed now. Helpers helpers;
    void getdocument() {
        rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> &sg = hypothesis["subgraphs"];
        sg.GetArray().Size();
    }

    void load(std::string configuration_file) {
        std::ifstream ifs { configuration_file };
        rapidjson::IStreamWrapper isw { ifs };
        configuration.ParseStream( isw );

        // Creating a temporary object, that is only used to fast traverse the JSON file with minimal allocations and
        // to populate the two maps. After the process, the parser is going to be discarded, thus freeing some memory
        // This map allows to extract the id and offset information, that is not serialized in secondary memory for the
        // graph. This information is quite "small" compared to the graph and might fit in primary memory.

        std::cerr << "loading idToOffset... " << std::endl;
        {
            idToOffsetHandler hanlder{non_3basicid_to_offset, vertex_main_id_to_vertex_information};
            hanlder.readFromFile(configuration["idToOffsetHandler"].GetString());
        }

        // Even in this case, objectToMultipleStrings is a temporary object tht is only iused to fast traverse the
        // json file. In this case, we extend the json information from the previous files with additional string
        // preferred representation. This information is quite "small" compared to the graph and might fit in primary memory.
        std::cout << "loading objectToMultipleStrings" << std::endl;
        {
            objectToMultipleStrings handler{vertex_main_id_to_vertex_information};
            handler.readFromFile(configuration["objectToMultipleStrings"].GetString());
        }

        // Loading the directory where the hierarchies' information is stored.
        hierarchiesForFuzzyMatch.load(configuration["hierarchiesForFuzzyMatch"].GetString());

        // Getting the threshold used for fuzzy matching
        fuzzyMatchThreshold = configuration["fuzzyMatchThreshold"].GetDouble();

        // Getting the top-K score value for fuzzy matching
        fuzzyMatchTopK = configuration["fuzzyMatchTopK"].GetInt();

        /* Legacy:
        std::string argument = configuration["cameo_event_code"].GetString();
        helpers.loadCameoEventCode(argument);*/
    }


    void fuzzyMatchForConceptNet(std::string& dimension, std::string& object, TreeMultimap<double, LONG_NUMERIC>& resultMap) {
        hierarchiesForFuzzyMatch.fuzzyMatch(dimension, fuzzyMatchThreshold, fuzzyMatchTopK, object, resultMap);
    }

    void doesConceptNetContainExactTerm(std::string& dimension, std::string& object, ArrayList<LONG_NUMERIC> &result) {
        hierarchiesForFuzzyMatch.containsExactTerm(dimension, object, result);
    }
};

/**
 * This function allows to
 */
#define INTERNAL_STATE_READ_HYPOTHESIS_FROM_STRING(internalState, string)    ((internalState).hypothesis.Parse(string))

#endif //INCONSISTENCY_INTERNALSTATE_H
