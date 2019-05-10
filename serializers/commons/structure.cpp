//
// Created by giacomo on 27/07/17.
//


#include <iostream>
#include "structure.h"


extern "C" {
#include <unistd.h>
}

inline static LONG_NUMERIC binsearch_edges_in_vertices_inner_loop(struct edges_in_vertices* e, LONG_NUMERIC i, LONG_NUMERIC n, LONG_NUMERIC mid, LONG_NUMERIC expected, char field, bool* found) {
    LONG_NUMERIC val, val2;
    if (n > 0) {
        get_field_from(e[i], field, val);
        get_field_from(e[n-1], field, val2);
#ifdef PRINTDEBUG
        std::cout << "val=" << val << " val2=" << val2 << " expected=" << expected << std::endl;
#endif
        if (val <= expected && expected <= val2 && i <= mid && mid <= n) while (i <= n) {
#ifdef PRINTDEBUG
                std::cout << "i=" << i << " n=" << n << " mid=" << mid << std::endl;
                sleep(1);
#endif
                get_field_from(e[mid], field, val);
                if (val == expected) {
                    if (found) *found = true;
                    return mid;
                }
                else if (val < expected) i = mid+1;
                else n = mid-1;
                mid = (n+i)/2;
#ifdef PRINTDEBUG
                std::cout << "[beforeloop] i=" << i << " n=" << n << " mid=" << mid << std::endl;
                sleep(1);
#endif
            }
    }
#ifdef PRINTDEBUG
    std::cout << n << std::endl;
#endif
    if (found) *found = false;
}

/**
 *
 * @param h_v:  If zero, it means that any element will do. So, it searches for all the elements with a given non-zero
 *              h_e. If h_v is not zero, then searches for the vertices having a given hash value
 * @param h_e:  If zero, any edge will do, so it returns all the boundary of the edges, and leaves the query plan to
 *              a better solution for searching for the h_v... otherwise, it scans the
 *
 *              TODO: optimization, when the edge has no hash, then assumes the hash of the vertex (but it has to be
 *              TODO: decided at the upper level)
 */
bool binsearch_edges_in_vertices(struct edges_in_vertices *e, LONG_NUMERIC h_e, LONG_NUMERIC h_v, LONG_NUMERIC size,
                                 LONG_NUMERIC *left_limit, LONG_NUMERIC *right_limit) {
    bool inner_found = false;
    LONG_NUMERIC findEdge;
    if (h_e == 0 && size > 0) {
        // In this scenario, any edge will do, and hence, we only have to filter over the vertices. So we have to do
        // a linear scan for the vertices
        if (left_limit) *left_limit = 0;
        if (right_limit) *right_limit = size-1;
        // TODO: YIELD ITERATION on all the parts---> IF I iterate, I can filter by h_v and then jield the elements
        return true;
    } else if (size > 0) {
        findEdge = binsearch_edges_in_vertices_inner_loop(e,0,size, size/2, h_e, EDGE_HASH, &inner_found);
    } else {
        inner_found = false;
    }
#ifdef PRINTDEBUG
    std::cout << (inner_found ? "" : "not ") << "edgeFound done at " <<  findEdge << std::endl;
#endif
    if (inner_found) {
        LONG_NUMERIC j = findEdge;
        LONG_NUMERIC i;
        bool decrement = false;
        bool increment = false;
        if (h_v) {
            while (j <= size && e[j].vertexHash != h_v) {
                if (e[j].vertexHash < h_v) {
                    if (decrement) break;
                    else if (!increment) {
                        increment = true;
                    }
                    j++;
                } else if (e[j].vertexHash > h_v) {
                    if (increment) break;
                    else if (!decrement) {
                        decrement = true;
                    }
                    j--;
                }
            }
            inner_found = e[j].vertexHash == h_v;
        } else {
            inner_found = true;
        }
#ifdef PRINTDEBUG
        std::cout << (inner_found ? "" : "not ") <<  "vertexFound done " << j << std::endl;
#endif
        if (inner_found && h_e) {
            i = j;
            // if !h_v then b else true => !(!!h_v && !b) => !h_v || b
            while (j+1 < size && (e[j + 1].edgeHash == h_e) && (!h_v || e[j + 1].vertexHash == h_v)) {
                j++;
                // TODO: YIELD ITERATION
            }
            //std::cout << "j done" << std::endl;
            while (i-1 < size && (e[i-1].edgeHash == h_e) && (!h_v || e[i-1].vertexHash == h_v)) {
                i--;
                // TODO: YIELD ITERATION
            }
            //std::cout << "i done" << std::endl;
            if (left_limit) *left_limit = i;
            if (right_limit) *right_limit = j;
            return true;
        }
    }
    // if it has not found in both cases, then return not found
    return  inner_found;
}

