/**
 * @file
 * @brief
 *  
 * @details
 * Traveling salesman problem asks:
 * Given a list of cities and the distances between each pair of cities
 * What is the shortest possible route that visits each city exactly once and returns to the origin
 * TSP can be modeled as an undirected weighted graph, such that cities are the 
 * graph's vertices, paths are the graph's edges, and a path's distance is the edge's weight.
 * It is a minimization problem starting and finishing at a 
 * specified vertex after having visited each other vertex exactly once.
 * This is a naive implementation of the problem.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

/**
 * @namespace graph
 * @brief Graph Algorithm
 */

namespace graph {
/**
 * @brief Function calculates minimum path distance that will cover all cities starting from source
 *
 * @param cities matrix representating cities
 * @param src Point where salesman is starting
 * @param V number of verticies in the graph
 */
  int TravellingSalesmanProblem(std::vector<std::vector<uint32_t>> *cities,
                              int32_t src,
                              uint32_t V) {
    std::vector<uint32_t> vtx;
    for (uint32_t i = 0; i < V; i++) {
      if (i != src) {
        vtx.push_back(i);
      }
    }
    int32_t min_path = 2147483647;
    do {
      int32_t curr_weight = 0;
      int k = src;
      for (int i:vtx) {
        curr_weight += (*cities)[k][i];
      }
      curr_weight += (*cities)[k][src];
      min_path = std::min(min_path, curr_weight);

    } while (next_permutation(vtx.begin(), vtx.end()));
    return min_path;
  }

}
