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

#include "versions/v0.2/FuzzyMatch.h"
#include "versions/v0.2/FuzzyMatchSerializerSEC.h"
#include <iostream>
#include <locale.h>

void serialize_test_to2M() {
    FuzzyMatchSerializerSEC secondary_test{"test_serialization_csvDir"};

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
    FuzzyMatch fm{"current_folder"};
    std::string dimension{"test_serialization"};
    TreeMultimap<double, LONG_NUMERIC> res;
    std::string query{"gia"};
    fm.fuzzyMatch(dimension, 0.0, 100, query, res);
    for (auto it = res.begin(), en = res.end(); it != en; it++) {
        std::cout << it->first << " @ " << it->second << std::endl;
    }
}

int main() {
    test_query();
}
