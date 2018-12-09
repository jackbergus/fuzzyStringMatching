#include <iostream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <numeric>

#include "rapidjson/reader.h"
using namespace rapidjson;

#include "conceptnet/deserialization/conceptnet_edge_deserialization.h"
#include "relationships/RelationshipTypes.h"
#include "conceptnet/utils.h"
#include "serializers/commons/secondary_memory/utils/Graph.h"

#include <iostream>
#include <lemon/list_graph.h>
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
    cout << "Hello World! This is LEMON library here." << std::endl;
    cout << "We have a directed graph with " << lemon::countNodes(g) << " nodes "
         << "and " << lemon::countArcs(g) << " arc." << std::endl;
}

int main() {
    Graph g;
}
