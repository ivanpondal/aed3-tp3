#ifndef AED3_TP3_HEURISTICS_H
#define AED3_TP3_HEURISTICS_H

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../main.h"

/*
**  Heuristics
*/

struct node_degree_pair_compare{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2){
        return p1.second < p2.second;
    }
};

graph<std::pair<int, int>> *solve_greedy(
    const graph<int> &g1,
    const graph<int> &g2,
    bool add_neighbours = false
);

graph<std::pair<int, int>>* solve_local_search(
    graph<int>& g1,
    graph<int>& g2,
    graph<std::pair<int, int>>& start_point,
    int neighbourhood_type = 0,
    int iteration_limit = -1,
    // int neighbourhood_limit = -1,
    float neighbourhood_proportion = 1,
    bool strict_comparisons = true
);

#endif  // AED3_TP3_HEURISTICS_H
