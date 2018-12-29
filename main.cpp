#include <iostream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

#include "rapidjson/reader.h"
using namespace rapidjson;

#include "relationships/RelationshipTypes.h"
#include "serializers/commons/secondary_memory/utils/Graph.h"
#include "merging/conceptnet/deserialization/conceptnet_edge_deserialization.h"
#include "merging/fuzzymatch/FuzzyMatch.h"
#include "fromJava/classes.h"
#include "datasets/NELL/NELL.h"
#include "datasets/ICEWS/ICEWS.h"
#include "datasets/GDELT/GDELT.h"
#include "datasets/Phoenix/Phoenix.h"
#include "numeric/ProgressBar.h"

#include <unordered_map>
#include <iostream>
#include <lemon/list_graph.h>

#include <sstream>
#include <string>
#include <unordered_map>

void test_json_edgeparser() {
    const char json[] = "{\"end\": \"/c/ar/صد\", \"rel\": \"/r/FormOf\", \"uri\": \"/a/[/r/FormOf/,/c/ar/نصدد/v/,/c/ar/صد/]\", \"start\": \"/c/ar/نصدد/v\", \"weight\": 1.0, \"dataset\": \"/d/wiktionary/en\", \"license\": \"cc:by-sa/4.0\", \"sources\": [{\"process\":"
                        " \"/s/process/wikiparsec/2\", \"contributor\": \"/s/resource/wiktionary/en\"}], \"features\": [\"/c/ar/نصدد /r/FormOf -\", \"/c/ar/نصدد - /c/ar/صد\", \"- /r/FormOf /c/ar/صد\"], \"surfaceEnd\": null, \"surfaceText\": null, \"surfaceStart\": null}";
    conceptnet_edge_deserialization handler;
    Reader reader;
    handler.readFromChars(json, reader);
    std::cout << handler << std::endl;
    std::cout << handler.relType << std::endl;
}

void test_lemon() {
    // TODO: https://github.com/sommergis/MyBlogEntries/blob/master/Dijkstra/dijkstra_lemon.cc
    lemon::ListDigraph g;
    lemon::ListDigraph::Node u = g.addNode();
    lemon::ListDigraph::Node v = g.addNode();
    lemon::ListDigraph::Arc  a = g.addArc(u, v);
    std::cout << "Hello World! This is LEMON library here." << std::endl;
    std::cout << "We have a directed graph with " << lemon::countNodes(g) << " nodes "
         << "and " << lemon::countArcs(g) << " arc." << std::endl;
}

/**
 * Process allowing to read NELL data.
 * Each relationship carries out also is-a relationships.
 *
 * NELL provies an ontology which provies a skeleton of a is-a hierarchy
 */
void read_nell_data() {
    ProgressBar pb{32687353.0};
    std::map<std::string, NELL> map;
    std::unordered_map<std::string, std::set<std::string>> string_candidates;
    std::ifstream infile("/media/giacomo/80CEAABECEAAABBA/Data/NELL/NELL.08m.1110.cesv.csv");
    std::ifstream infile2("/media/giacomo/80CEAABECEAAABBA/Data/NELL/NELL.08m.1115.esv.csv");
    std::string line;
    bool  skipFirst = true;
    LONG_NUMERIC id = 0, c = 0;

    //LONG_NUMERIC MAX_DEBUG = 200, c = 0;
    while (std::getline(infile, line) /*&& (c < MAX_DEBUG)*/) {
        if (!skipFirst) {
            NELL nell{id++, line};
            std::ostringstream ss;
            ss << nell;
            std::string sstring = ss.str();
            for (std::string &x : nell.src.literalStrings) {
                string_candidates[nell.src.best_string].insert(x);
            }
            nell.src.literalStrings.clear();
            auto it = map.insert(std::make_pair(sstring, nell));
            if (!it.second) {
                it.first->second.updateWith(nell);
            }
            c++;
        } else {
            skipFirst = false;
        }
        pb.update(c);
    }

    pb.reset();
    while (std::getline(infile2, line) /*&& (c < MAX_DEBUG)*/) {
        if (!skipFirst) {
            NELL nell{id++, line};
            std::ostringstream ss;
            ss << nell;
            std::string sstring = ss.str();
            for (std::string &x : nell.src.literalStrings) {
                string_candidates[nell.src.best_string].insert(x);
            }
            nell.src.literalStrings.clear();
            auto it = map.insert(std::make_pair(sstring, nell));
            if (!it.second) {
                it.first->second.updateWith(nell);
            }
            c++;
        } else {
            skipFirst = false;
        }
        pb.update(c);
    }

    {
        std::ofstream file{"/media/giacomo/80CEAABECEAAABBA/Data/NELL/nell.csv"};
        for (auto it = map.begin(); it != map.cend(); it++) {
            it->second.getAdditionalElements(file);
            it->second.getEdge(file);
        }
    }
    {
        std::ofstream file{"/media/giacomo/80CEAABECEAAABBA/Data/NELL/nell_disambiguations.csv"};
        for (auto it = string_candidates.begin(); it != string_candidates.end(); it++) {
            std::ostringstream oss;
            file << it->first << "\t";
            if (!it->second.empty()) {
                // Convert all but the last element to avoid a trailing ","
                std::copy(it->second.begin(), it->second.end(),
                          std::ostream_iterator<std::string>(oss, "; "));
            }
            file << "[" << oss.str() << "]"  << std::endl;
        }
    }
}

void read_icews_data() {
    std::unordered_map<std::string, std::set<std::string>> disambiguations;
    std::map<std::string, ICEWS> map;
    std::ifstream infile("/media/giacomo/80CEAABECEAAABBA/Data/ICEWS/Events/20181004-icews-events.tab");
    std::string line;
    bool  skipFirst = true;
    LONG_NUMERIC id = 0;
    LONG_NUMERIC MAX_DEBUG = 200, c = 0;
    while (std::getline(infile, line) && (c < MAX_DEBUG)) {
        if (!skipFirst) {
            ICEWS nell{line};
            std::ostringstream ss;
            ss << nell;
            std::string sstring = ss.str();
            auto it = map.insert(std::make_pair(sstring, nell));
        } else {
            skipFirst = false;
        }
    }
    for (auto it = map.begin(); it != map.cend(); it++) {
        std::cout << it->second << std::endl;
    }
}

void phoenix() {
    std::ifstream infile("/media/giacomo/80CEAABECEAAABBA/Data/Phoenix/PhoenixFBIS_1995-2004.csv");
    std::string line;
    std::istringstream sss;
    bool  skipFirst = true;
    while (std::getline(infile, line)) {
        if (skipFirst) {
            skipFirst = false;
        } else {
            sss.str(line);
            CSVIterator it{sss};
            Phoenix p;
            p.load(it);
            std::cout << p << std::endl;
            sss.clear();
        }
    }
}

#include "internal_state/InternalState.h"

void gdelt_example() {
    InternalState internalState;
    internalState.load("configuration.json");
    std::ifstream infile("/media/giacomo/80CEAABECEAAABBA/Data/GDELT/gdelt20/all/201303.csv");
    std::string line;
    while (std::getline(infile, line)) {
        SplitStringIterator it{line, "\t"};
        GDELT gdelt;
        gdelt.load(it, true);
        gdelt.relation.event_name = internalState.helpers.cameo_event_code_to_representation[gdelt.relation.event_code];
        if ((!gdelt.src.name.empty()) && (!gdelt.dst.name.empty()) && (gdelt.relation.event_rootcode == "19"))
            std::cout << gdelt << std::endl;
        line.clear();
    }
}

int main() {
    /*FuzzyMatch fm{"/media/giacomo/Biggus/project_dir/data/hierarchies"};
    std::string dim{"Weapon"};
    std::string obj{"surface to   air missile"};
    TreeMultimap<double, LONG_NUMERIC> result;
    fm.fuzzyMatch(dim, 0.6, 3, obj, result);
    for (auto it = result.rbegin(); it != result.rend(); it++) {
        std::cout << it->first << " - " << it->second << std::endl;
    }*/
    gdelt_example();

    /**/
}
