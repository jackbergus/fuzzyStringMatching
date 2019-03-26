//
// Created by giacomo on 25/01/19.
//

#ifndef INCONSISTENCY_MAIN_MEMORY_LEMON_GRAPH_H
#define INCONSISTENCY_MAIN_MEMORY_LEMON_GRAPH_H

// all the edges are just associated to a numerical number. On the other hand, edges might vary their representation
typedef unsigned int edge_t;

// type associated to the edge cost.
typedef double cost_t;

/// From STL library
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

/// Lemon Graph Library
#include <lemon/list_graph.h>
#include <lemon/smart_graph.h>
#include <lemon/static_graph.h>
#include <lemon/fib_heap.h>
#include <lemon/quad_heap.h>
#include <lemon/radix_heap.h>
#include <lemon/dheap.h>
#include <lemon/bin_heap.h>
#include <lemon/adaptors.h>
#include <lemon/concepts/maps.h>
#include <lemon/dijkstra.h>
#include <lemon/path.h>

// change graph and heap type at compile time
// Don't optimize too much
// -O1 gives better results on static graphs

///////////////////////////////////////////////
// choose ONE graph type from the following: //
///////////////////////////////////////////////

//#define USE_LISTGRAPH
//#define USE_SMARTGRAPH
#define USE_STATICGRAPH

// Using the defines to select the best graph type
#ifdef USE_LISTGRAPH
typedef lemon::ListDigraph graph_t;
#endif
#ifdef USE_SMARTGRAPH
typedef lemon::SmartDigraph graph_t;
#endif
#ifdef USE_STATICGRAPH
typedef lemon::StaticDigraph graph_t;
#endif

// Providing abbreviated names for the properties
typedef graph_t::Arc Arc;
typedef graph_t::Node Node;
typedef graph_t::ArcMap <cost_t> LengthMap;
typedef graph_t::NodeMap<int> NodeMap;

//////////////////////////////////////////////
// choose ONE heap type from the following: //
//////////////////////////////////////////////

//#define USE_BIN_HEAP
//#define USE_QUAD_HEAP
//#define USE_FIBONACCI_HEAP
//#define USE_RADIX_HEAP
//#define USE_DARY_HEAP_D_2
#define USE_DARY_HEAP_D_3
//#define USE_DARY_HEAP_D_4
//#define USE_DARY_HEAP_D_8
//#define USE_DARY_HEAP_D_16

#ifdef USE_FIBONACCI_HEAP
typedef lemon::FibHeap<cost_t, NodeMap> heap_t;
#endif
#ifdef USE_QUAD_HEAP
typedef lemon::QuadHeap<cost_t, NodeMap> heap_t;
#endif
#ifdef USE_RADIX_HEAP
typedef lemon::RadixHeap<NodeMap> heap_t;
#endif
#ifdef USE_DARY_HEAP_D_2
typedef lemon::DHeap<cost_t, NodeMap, 2> heap_t;
#endif
#ifdef USE_DARY_HEAP_D_3
typedef lemon::DHeap<cost_t, NodeMap, 3> heap_t;
#endif
#ifdef USE_DARY_HEAP_D_4
typedef lemon::DHeap<cost_t, NodeMap, 4> heap_t;
#endif
#ifdef USE_DARY_HEAP_D_8
typedef lemon::DHeap<cost_t, NodeMap, 8> heap_t;
#endif
#ifdef USE_DARY_HEAP_D_16
typedef lemon::DHeap<cost_t, NodeMap, 16> heap_t;
#endif
#ifdef USE_BIN_HEAP
// default heap type
typedef lemon::BinHeap<cost_t, NodeMap> heap_t;
#endif


// Internal methods
#include <unordered_set>
#include "../SplitStringIterator.h"
#include "../../utils/fixed_bimap.h"

/**
 *
 * @tparam vertex_t  should override the to_string method in order to be used within the fixed_bimap
 */
template <typename vertex_t> class main_memory_lemon_graph {
    /// Build the graph
    graph_t G;

public:
    // Number of vertices
    unsigned long n = 0;

    // Number of edges
    unsigned long m = 0;

    fixed_bimap<vertex_t, unsigned long> vertexToId;

    /**
     * Converting the string associated to the
     * @param toParse
     * @return
     */
    virtual vertex_t stringToVertex(std::string toParse) const = 0;

    /**
     * Given a tab separated file which path is set in 
     * @param path
     */
    void loadGraph(std::string path) {
        // First, I need to count the number of the variables
        {
            std::ifstream infile(path);
            std::unordered_set<std::string> vertexForCount;
            std::string src, dst;
            cost_t w;
            while (infile >> src >> dst >> w) {
                if (vertexToId.putWithKeyCheck(stringToVertex(src), n+1) == (n+1)) {
                    // increment the vertex if it is a new one
                    n++;
                }
                if (vertexToId.putWithKeyCheck(stringToVertex(dst), n+1) == (n+1)) {
                    // increment the vertex if it is a new one
                    n++;
                }
                m++;
            }
            n = vertexForCount.size();
        }

        {
            std::ifstream infile(path);

#ifndef USE_STATICGRAPH
            // ALERT! TO edit so it resembles the code for the static graph. This version does not match with the one below
            G.reserveNode(n);
            G.reserveArc(m);
            std::vector<Node> vs;
            vs.reserve(n);
            for ( int i = 0; i < n; ++i )
                vs.push_back( G.addNode() );

            int v, w;
            cost_t c;
            cost_t T_dist;
            LengthMap    C(G);
            for ( int i = 0; i < m; i++ ) {
                  infile >> v >> w >> c;
                  Arc a;
                  a = G.addArc(vs[v-1], vs[w-1]);
                  C[a] = c;
            }
#else
            vertex_t v, w;
            std::string cstr;
            cost_t c;
            cost_t T_dist;
            LengthMap C(G);

            {
                std::vector <cost_t> costs(m);
                {
                    //arcs will be built with arcList iterators
                    // populate arcList first
                    std::vector <std::pair<int, int>> arcList(m);
                    std::string line;
                    for (int i = 0; i < m; i++) {
                        if (std::getline(infile, line))
                        {
                            SplitStringIterator splitStringIterator{line, "\t"};
                            v = stringToVertex(*splitStringIterator); splitStringIterator++;
                            w = stringToVertex(*splitStringIterator); splitStringIterator++;
                            cstr = (*splitStringIterator);
                            c = std::stod(cstr);
                            costs.push_back(c);
                        }
                        arcList.push_back(std::make_pair(vertexToId.getValue(v), vertexToId.getValue(w)));
                    }
                    G.build(n, arcList.begin(), arcList.end());
                    // free arcList
                }
                //populate costMap
                for (int i = 0; i < m; i++)
                    C[G.arc(i)] = costs[i];

                // free costs
            }

#endif // USE_STATICGRAPH
        }
    }

};


#endif //INCONSISTENCY_MAIN_MEMORY_LEMON_GRAPH_H
