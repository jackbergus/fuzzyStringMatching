//
// Created by giacomo on 10/12/18.
//

#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <regex>


#include "NELL.h"
#include "../../serializers/Streamers.h"

#include "../../merging/SplitStringIterator.h"
#include "../../fromJava/trimmers.h"


NELL::NELL(LONG_NUMERIC id, std::string &line) {
    SplitStringIterator it{line, "\t"};
    this->id = id;
    std::stringstream ss;

    this->src.ontology_name = *it; it++;
    relation.type = *it; it++;
    this->value.ontology_name = *it; it++;

    // Iteration_of_Candidacy
    /*std::string ioc = *it;*/ it++;
    /*ioc.erase(std::remove_if(ioc.begin(), ioc.end(), [](char c) { return (!std::isdigit(c))&&(!std::isspace(c)); }), ioc.end());
    ss << ioc;
    LONG_NUMERIC lfound;
    while (!ss.eof()) {
        std::string temp;
        ss >> temp;
        if (std::stringstream(temp) >> lfound)
            Iteration_of_Candidacy.push_back(lfound);
        temp = "";
    }
    ss.clear();*/

    // Candidate_Probability
    std::string ioc = *it; it++;
    ioc.erase(std::remove_if(ioc.begin(), ioc.end(), [](char c) { return (!std::isdigit(c))&&(!std::isspace(c))&&(c != '.'); }), ioc.end());
    ss << ioc;
    double dfound;
    relation.probability = 1.0;
    while (!ss.eof()) {
        std::string temp;
        /* extracting word by word from stream */
        ss >> temp;
        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> dfound)
            relation.probability = relation.probability * (1.0-dfound);
        /* To save from space at the end of string */
        temp = "";
    }
    relation.probability = 1.0 - relation.probability;

    // Source
    it++;

    // Entity_literalStrings
    ioc = *it; it++;
    std::istringstream iss(ioc);
    std::string s;
    while (iss >> std::quoted(s)) {
        this->src.literalStrings.push_back(s);
    }
    iss.clear();

    // Value_literalStrings
    ioc = *it; it++;
    iss.str(ioc);
    while (iss >> std::quoted(s)) {
        this->value.literalStrings.push_back(s);
    }

    this->src.best_string = *it; it++;
    this->value.best_string = *it; it++;

    // Categories_for_Entity
    ioc = *it; it++;
    std::regex rgx("\\s+");
    {
        std::sregex_token_iterator iter(ioc.begin(), ioc.end(), rgx, -1);
        std::sregex_token_iterator end;
        std::string tmp;
        for ( ; iter != end; ++iter) {
            tmp = *iter;
            if (!(std::all_of((tmp).begin(),tmp.end(),isspace))&&(!tmp.empty())) this->src.hasCategory.push_back(tmp);
        }
    }

    // Categories_for_Value
    ioc = *it; it++;
    std::sregex_token_iterator iter(ioc.begin(), ioc.end(), rgx, -1);
    std::sregex_token_iterator end;
    std::string tmp;
    for ( ; iter != end; ++iter) {
        tmp = *iter;
        if (!(std::all_of((tmp).begin(),tmp.end(),isspace))&&(!tmp.empty()))
            this->value.hasCategory.push_back(*iter);
    }
}

std::ostream &operator<<(std::ostream &os, const NELL &nell) {
    os << "NELL\n\t<" << nell.src << ">--[label=" << nell.relation.type
       << /*", p=" << nell.relation.probability <<*/ "]-><" << nell.value << ">";
    return os;
}

void NELL::updateWith(NELL nell) {
    value.updateWith(nell.value);
    src.updateWith(nell.src);
    relation.probability = std::max(relation.probability, nell.relation.probability);
}

void NELL::getEdge(std::ofstream &file) {
    std::string bs = trim(value.best_string);
    if (bs.empty()) {
        file << trim(relation.type) << "\t" << src.best_string << "\t" << value.ontology_name << "\t" << std::to_string(relation.probability) << std::endl;
    } else {
        file << trim(relation.type) << "\t" << src.best_string << "\t" << value.best_string << "\t" << std::to_string(relation.probability) << std::endl;
    }
}

void NELL::getAdditionalElements(std::ofstream &file) {
    std::string probability = std::to_string(relation.probability);
    std::string bs = trim(value.best_string);
    file << ( "sameas\t") << ( src.best_string) << ( "\t") << (src.ontology_name) << ("\t") << (probability) << std::endl;
    if (!value.best_string.empty())
        file << ( "sameas\t") << (value.best_string) << ( "\t") << (value.ontology_name) << ("\t") << (probability) << std::endl;
    for (std::string& x: src.hasCategory) {
        file << ( "isa\t") << ( src.best_string) << ( "\t") << (x) << ("\t") << (probability) << std::endl;
    }
    for (std::string& x: value.hasCategory) {
        file << ( "isa\t") << ( value.best_string) << ( "\t") << (x) << ("\t") << (probability) << ("\n");
    }
}
