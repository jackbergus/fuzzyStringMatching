//
// Created by giacomo on 25/03/19.
//

#include "FuzzyMatchSerializer.h"
#include <boost/filesystem.hpp>
#include <cstdio>

void compareStringHashmap1(std::string &str, std::unordered_map<std::string, LONG_NUMERIC> &map,
                           std::vector<LONG_NUMERIC> &vec) {
    LONG_NUMERIC numPairs = str.length() - 1;
    if (numPairs == 0) {
        map[str] = 0;
        vec.emplace_back(1);
    } else {
        if (numPairs < 0) numPairs = 0;
        int singleGrams = 0;
        for (int i = 0; i < numPairs; i++) {
            std::string s = str.substr(i, 2);
            std::unordered_map<std::string,LONG_NUMERIC>::iterator pos = map.find(s);
            if (pos == map.end()) {
                map[s] = singleGrams++;
                vec.emplace_back(1);
            } else {
                LONG_NUMERIC x = vec[pos->second];
                vec[pos->second] = x+1;
            }
        }
    }
}

void compareStringHashmap2(std::string &string, std::unordered_map<std::string, LONG_NUMERIC> &map,
                           std::vector<LONG_NUMERIC> &vec) {
    {
        std::string str;
        std::stringstream ss(string);
        std::vector<std::string> pairs;

        while (ss >> str) {
            compareStringHashmap1(str, map, vec);
        }
    }
    for (std::unordered_map<std::string,LONG_NUMERIC>::iterator kp = map.begin(), end = map.end(); kp != end; ++kp) {
        kp->second = vec[kp->second];
    }
}

void FuzzyMatchSerializer::serialize(std::string path) {
    boost::filesystem::path p{path};
    if (!boost::filesystem::exists(p)) {
        boost::filesystem::create_directories(p);
    } else {
        if (!boost::filesystem::is_directory(p)) {
            std::cout << "Removing the file associated to " << p << std::endl;
            boost::filesystem::remove(p);
            boost::filesystem::create_directories(p);
        }

        // gramToObject serialization
        {
            std::string gramToObject_hash = boost::filesystem::canonical(p / "gramToObjects.csv_vector.bin").string();
            std::string gramToObject_vals = boost::filesystem::canonical(p / "gramToObjects.csv_values.bin").string();
            FILE *hash = fopen64(gramToObject_hash.c_str(), "w");
            FILE *valu = fopen64(gramToObject_vals.c_str(), "w");
            this->gramToObject.serialize(hash, valu);
            fclose(hash);
            fclose(valu);
        }

        // objectGramSize serialization
        {
            std::string gramToObject_hash = boost::filesystem::canonical(p / "objectGramSize.csv_vector.bin").string();
            std::string gramToObject_vals = boost::filesystem::canonical(p / "objectGramSize.csv_values.bin").string();
            FILE *hash = fopen64(gramToObject_hash.c_str(), "w");
            FILE *valu = fopen64(gramToObject_vals.c_str(), "w");
            this->objectGramSize.serialize(hash, valu);
            fclose(hash);
            fclose(valu);
        }

        // termObject serialization
        {
            std::string gramToObject_hash = boost::filesystem::canonical(p / "termToObjects.csv_vector.bin").string();
            std::string gramToObject_vals = boost::filesystem::canonical(p / "termToObjects.csv_values.bin").string();
            FILE *hash = fopen64(gramToObject_hash.c_str(), "w");
            FILE *valu = fopen64(gramToObject_vals.c_str(), "w");
            this->termObject.serialize(hash, valu);
            fclose(hash);
            fclose(valu);
        }

        // objectMultipleStirngs serialization
        {
            std::string gramToObject_hash = boost::filesystem::canonical(
                    p / "objectMultipleStirngs.csv_vector.bin").string();
            std::string gramToObject_vals = boost::filesystem::canonical(
                    p / "objectMultipleStirngs.csv_values.bin").string();
            FILE *hash = fopen64(gramToObject_hash.c_str(), "w");
            FILE *valu = fopen64(gramToObject_vals.c_str(), "w");
            this->objectMultipleStirngs.serialize(hash, valu);
            fclose(hash);
            fclose(valu);
        }

        // twogramAndStringMultiplicity serialization
        {
            std::string gramToObject_hash = boost::filesystem::canonical(
                    p / "twogramAndStringToMultiplicity.csv_vector.bin").string();
            std::string gramToObject_vals = boost::filesystem::canonical(
                    p / "twogramAndStringToMultiplicity.csv_values.bin").string();
            FILE *hash = fopen64(gramToObject_hash.c_str(), "w");
            FILE *valu = fopen64(gramToObject_vals.c_str(), "w");
            this->twogramAndStringMultiplicity.serialize(hash, valu);
            fclose(hash);
            fclose(valu);
        }



    }
}
