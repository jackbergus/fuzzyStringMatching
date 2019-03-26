#include <iostream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

#include "merging/conceptnet/utils.h"
#include "rapidjson/reader.h"
#include "rapidjson/filereadstream.h"
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

#include "merging/fuzzymatch/FuzzyMatchSerializer.h"

#include "utils/fixed_bimap.h"

#include <unordered_map>
#include <iostream>
#include <lemon/list_graph.h>

#include <unordered_set>
#include <sstream>
#include <string>

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

// TODO: able to list all the hierarchies within the folder
// TODO: GraphQueryIterator is the class that uses "offsets" to refer to vertex ids, and returs parsed edges as the output of the iteration process. Therefore, use multiple possible LONGS --> merge the iterators together
int main() {
    // Loading the translation offset/id
    /*// Result map
    TreeMultimap<double, LONG_NUMERIC> result;
    // Performing the query
    std::cout << "Fuzzy matching" << std::endl  << std::endl;
    fm.fuzzyMatch(dim, 0.6, 3, obj, result);
    for (auto it = result.rbegin(); it != result.rend(); it++) {
        std::cout << it->first << " - " << non_3basicid_to_offset.getKey(it->second) << std::endl;
    }*/
}
