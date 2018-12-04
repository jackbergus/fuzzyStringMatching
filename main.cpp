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

int main() {
    const char json[] = "{\"end\": \"/c/ar/صد\", \"rel\": \"/r/FormOf\", \"uri\": \"/a/[/r/FormOf/,/c/ar/نصدد/v/,/c/ar/صد/]\", \"start\": \"/c/ar/نصدد/v\", \"weight\": 1.0, \"dataset\": \"/d/wiktionary/en\", \"license\": \"cc:by-sa/4.0\", \"sources\": [{\"process\":"
                        " \"/s/process/wikiparsec/2\", \"contributor\": \"/s/resource/wiktionary/en\"}], \"features\": [\"/c/ar/نصدد /r/FormOf -\", \"/c/ar/نصدد - /c/ar/صد\", \"- /r/FormOf /c/ar/صد\"], \"surfaceEnd\": null, \"surfaceText\": null, \"surfaceStart\": null}";
    conceptnet_edge_deserialization handler;
    Reader reader;
    handler.readFromChars(json, reader);
    std::cout << handler << std::endl;
    std::cout << handler.relType << std::endl;
    return 0;
}
