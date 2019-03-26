//
// Created by giacomo on 25/01/19.
//

#ifndef INCONSISTENCY_CONCEPTNET5_VERTEX_H
#define INCONSISTENCY_CONCEPTNET5_VERTEX_H

#include <string>
#include <vector>
#include "../utils.h"

/**
 * Providing the basic vertex representation
 */
struct conceptnet5_vertex {
    /**
     * Head id (removes the sense information)
     */
    std::string id;
    /**
     * Language associated to the id
     */
    std::string language;
    /**
     * Multiple string representations associated to the same string
     */
    std::vector<std::string> surfaces;
    /**
     * Different POS associated to the string
     */
    std::vector<std::string> senses;
    /**
     * Sub-ids associated to the same string.
     */
    std::vector<std::string> subids;

    conceptnet5_vertex(std::string x);;

    /**
     * dedupling the information inserted within the vectors
     */
    void dedup();
};


#endif //INCONSISTENCY_CONCEPTNET5_VERTEX_H
