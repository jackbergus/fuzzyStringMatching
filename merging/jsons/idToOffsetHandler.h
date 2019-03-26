//
// Created by giacomo on 25/01/19.
//

#ifndef INCONSISTENCY_IDTOOFFSETHANDLER_H
#define INCONSISTENCY_IDTOOFFSETHANDLER_H

#include "../conceptnet/utils.h"
#include "rapidjson/reader.h"
#include "rapidjson/filereadstream.h"
using namespace rapidjson;
#include "../conceptnet/deserialization/conceptnet5_vertex.h"
#include "../../utils/fixed_bimap.h"
#include "../../serializers/commons/structure.h"

/**
 * This class maps each ConceptNetId to its corresponding offset.
 * The result of the mapping is stored into a fixed_bimap, which provides the conversion from id to offset and viceversa.
 */
struct idToOffsetHandler : public rapidjson::BaseReaderHandler<UTF8<>, idToOffsetHandler> {
    fixed_bimap<std::string, LONG_NUMERIC> &map;
    std::unordered_map<std::string, conceptnet5_vertex> &translation;
    std::string key;

    /**
     *
     * @param map   BImap that is going to get updated during the traversal process. Mapping the id-offset to the
     *              actual ID representation
     * @param tr    Translation map, mapping the basic substring to the actual id
     */
    idToOffsetHandler(fixed_bimap<std::string, LONG_NUMERIC> &map,
                      std::unordered_map<std::string, conceptnet5_vertex> &tr);
    bool Int(int i);
    bool Uint(unsigned u);
    bool Int64(int64_t i);
    bool Uint64(uint64_t u);
    bool StartObject();
    bool Key(const char* str, SizeType length, bool copy);
    bool Default();
    bool EndObject(SizeType memberCount);
    void readFromFile(std::string path);
};

#endif //INCONSISTENCY_IDTOOFFSETHANDLER_H