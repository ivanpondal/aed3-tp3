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

// Forward declarations
// --------------------

struct movement {
    std::pair<int, int> mapping;
    int added_edges;
    float time;
    int pos;
    bool is_swap;

    movement(std::pair<int, int> mapping,
        int added_edges,
        float time,
        bool is_swap
    ) {
        this->mapping = mapping;
        this->added_edges = added_edges;
        this->time = time;
        this->is_swap = is_swap;
    };

    movement(std::pair<int, int> mapping,
        int added_edges,
        float time
    ) {
        movement(mapping, added_edges, time, false);
    };

};

struct movement_compare {
    const std::vector<movement>* movements;
    int max_degree;
    float c;

    movement_compare() {};
    movement_compare(const float c, const int max_degree,
        const std::vector<movement>* movements
    ) {
        this->max_degree = max_degree;
        this->c = c;
        this->movements = movements;
    };

    bool operator()(const movement &m1, const movement &m2){
        float m1_weight = ((max_degree + m1.added_edges)*1.0f/(2*max_degree))*c +
            (1 - c)/(1 + (*movements)[m1.pos].time);
        float m2_weight = ((max_degree + m2.added_edges)*1.0f/(2*max_degree))*c +
            (1 - c)/(1 + (*movements)[m2.pos].time);
        return m1_weight > m2_weight;
    };
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
    int neighbourhood_type,                   // 1 or 2
    int iteration_limit = -1,                 // -1 indicates no limit
    // int neighbourhood_limit = -1,          // discarded parameter
    float neighbourhood_proportion = 1,       // between 0 and 1
    bool strict_comparisons = true
);

graph<std::pair<int, int>>* solve_tabu(
    graph<int>& g1,
    graph<int>& g2,
    graph<std::pair<int, int>>& start_point,
    int neighbourhood_type,                   // 1 or 2
    unsigned int tabu_list_size,              // how many movements to save as tabu
    int iteration_limit = -1,                 // -1 indicates no limit
    // int neighbourhood_limit = -1,          // discarded parameter
    float neighbourhood_proportion = 1,       // between 0 and 1
    bool strict_comparisons = true,
    int no_gain_iteration_limit = 100,        // how many iterations to allow with no gain
    float edges_vs_time = 0.75,               // how much each parameter weighs
    float time_delta = 0.1,                   // how much time increases on each step
    float aspiration_threshold = 0.9          // threshold used to compare with max edge swap
);

// Greedy declarations
// --------------------

struct node_degree_pair_compare {
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return p1.second < p2.second;
    }
};

// Local search declarations
// --------------------

bool improve_solution_1(
    graph<std::pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    std::unordered_map<int, int>& g2_to_g1_mapping,
    std::unordered_set<int>& mapped_nodes,
    std::unordered_set<int>& unmapped_nodes,
    std::vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons,
    unsigned int tabu_list_size,
    std::priority_queue<movement, std::vector<movement>,
        movement_compare>& tabu_queue,
    movement_compare& mc,
    std::vector<movement>& tabu_list,
    bool allow_worse,
    const float time_delta,
    int& max_edge_diff,
    const float aspiration_threshold
);

bool improve_solution_1(
    graph<std::pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    std::unordered_map<int, int>& g2_to_g1_mapping,
    std::unordered_set<int>& mapped_nodes,
    std::unordered_set<int>& unmapped_nodes,
    std::vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
);

bool improve_solution_2(
    graph<std::pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    std::unordered_map<int, int>& g2_to_g1_mapping,
    std::unordered_set<int>& mapped_nodes,
    std::unordered_set<int>& unmapped_nodes,
    std::vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons,
    unsigned int tabu_list_size,
    std::priority_queue<movement, std::vector<movement>,
        movement_compare>& tabu_queue,
    movement_compare& mc,
    std::vector<movement>& tabu_list,
    bool allow_worse,
    const float time_delta,
    int& max_edge_diff,
    const float aspiration_threshold
);

bool improve_solution_2(
    graph<std::pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    std::unordered_map<int, int>& g2_to_g1_mapping,
    std::unordered_set<int>& mapped_nodes,
    std::unordered_set<int>& unmapped_nodes,
    std::vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
);

#endif  // AED3_TP3_HEURISTICS_H
