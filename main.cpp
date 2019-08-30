/*
 * main.cpp
 * This file is part of fuzzyStringMatching
 *
 * Copyright (C) 2019 - Giacomo Bergami
 *
 * fuzzyStringMatching is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * fuzzyStringMatching is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fuzzyStringMatching. If not, see <http://www.gnu.org/licenses/>.
 */

#include "merging/fuzzymatch/FuzzyMatch.h"
#include "merging/fuzzymatch/FuzzyMatchSerializerSEC.h"

/*
#include <iostream>
#include "merging/jsons/idToOffsetHandler.h"
#include "merging/fuzzymatch/FuzzyMatch.h"
#include "merging/jsons/objectToMultipleStrings.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"*/

#include <iostream>
#include <locale.h>

void serialize_test_to2M() {
    FuzzyMatchSerializerSEC secondary_test{"/media/giacomo/Data/test_serialization_csvDir"};

    {
        LONG_NUMERIC id = 0;
        std::string key{"Giacomo Bergami"};
        std::vector<std::string> vector;
        vector.emplace_back("jackbergus");
        vector.emplace_back("bergamigiacomo");
        vector.emplace_back("jackb09");
        vector.emplace_back("jackb90");

        secondary_test.addGramsToMap(key, id, vector);
    }

    {
        LONG_NUMERIC id = 1;
        std::string key{"Bergami Giancarlo"};
        std::vector<std::string> vector;
        vector.emplace_back("bergamisaladini");

        secondary_test.addGramsToMap(key, id, vector);
    }

    {
        LONG_NUMERIC id = 2;
        std::string key{"Saladini Merinella"};
        std::vector<std::string> vector;
        vector.emplace_back("bergamisaladini");

        secondary_test.addGramsToMap(key, id, vector);
    }

    secondary_test.serialize();
}

void test_query() {
    FuzzyMatch fm{"/media/giacomo/Data/"};
    std::string dimension{"test_serialization"};
    TreeMultimap<double, LONG_NUMERIC> res;
    std::string query{"gia"};
    fm.fuzzyMatch(dimension, 0.0, 100, query, res);
    for (auto it = res.begin(), en = res.end(); it != en; it++) {
        std::cout << it->first << " @ " << it->second << std::endl;
    }
}

int main() {
    /*rapidjson::Document hypothesis;
    rapidjson::Document configuration;

    /**
     * This map univocally associates each ConceptNet url (in its non-basic form) into the id/offset of where such
     * vertex is stored within the serialized representation. This map is a non-mutable bijection, and therefore
     * the key might be searched to find the value and viceversa.
     *
    fixed_bimap<std::string, LONG_NUMERIC> non_3basicid_to_offset;

    /**
     * This map univocally associatetes each basic-form id into the overall vertex information that is required
     * to traverse the graph.
     *
    std::unordered_map<std::string, conceptnet5_vertex> vertex_main_id_to_vertex_information;

    FuzzyMatch hierarchiesForFuzzyMatch;
    // Creating a temporary object, that is only used to fast traverse the JSON file with minimal allocations and
    // to populate the two maps. After the process, the parser is going to be discarded, thus freeing some memory
    // This map allows to extract the id and offset information, that is not serialized in secondary memory for the
    // graph. This information is quite "small" compared to the graph and might fit in primary memory.

    std::cerr << "loading idToOffset... " << std::endl;
    {
        idToOffsetHandler hanlder{non_3basicid_to_offset, vertex_main_id_to_vertex_information};
        hanlder.readFromFile("/media/giacomo/Biggus/project_dir/data/json/idToOffset.json");
    }

    // Even in this case, objectToMultipleStrings is a temporary object tht is only iused to fast traverse the
    // json file. In this case, we extend the json information from the previous idToOffsetHandler graph and might fit in primary memory.
    std::cout << "loading objectToMultipleStrings" << std::endl;
    {
        objectToMultipleStrings handler{vertex_main_id_to_vertex_information};
        handler.readFromFile("/media/giacomo/Biggus/project_dir/data/json/id_to_strings/objectToMultipleStrings.json");
    }*/

    //serialize_test_to2M();
    test_query();


}
