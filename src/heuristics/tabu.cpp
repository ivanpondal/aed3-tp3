#include <cassert>

#include "heuristics.h"

/*
**  Tabu metaheuristic
**  IMPORTANT: This algorithm assumes g2 is larger (has more or the same
**  amount of vertices) than g2. Adittionaly, if g1 and g2 have the same size,
**  some neighbourhood types may not work properly.
*/


using namespace std;

graph<pair<int, int>>* solve_tabu(
    graph<int>& g1,
    graph<int>& g2,
    graph<pair<int, int>>& start_point,
    int neighbourhood_type,
    unsigned int tabu_list_size,
    int iteration_limit,
    float neighbourhood_proportion,
    bool strict_comparisons,
    int no_gain_iteration_limit,
    float edges_vs_time,
    float time_delta,
    float aspiration_threshold
) {
    // We need #V(g1) < #V(g2), #V(start_point) == #V(g_1)
    assert(g1.n() <= g2.n());
    assert(start_point.n() == g1.n());

    bool (*improve_solution) (
        graph<pair<int, int>>*,
        graph<int>&,
        graph<int>&,
        unordered_map<int, int>&,
        unordered_set<int>&,
        unordered_set<int>&,
        vector<int>&,
        float,
        bool,
        unsigned int,
        priority_queue<movement,
            vector<movement>,
            movement_compare>&,
        movement_compare&,
        vector<movement>&,
        bool,
        const float,
        int&,
        const float
    ) = &improve_solution_1;

    if (neighbourhood_type == 2) {
        improve_solution = &improve_solution_2;
    }

    unsigned int solution_size = start_point.n();

    // This will store the node in g1 that corresponds to each node in g2
    unordered_map<int, int> g2_to_g1_mapping;

    // This will keep track of g2 vertices which are (not) mapped to any vertex in g1
    unordered_set<int> mapped_nodes;
    unordered_set<int> unmapped_nodes;
    vector<int> unmapped_nodes_vector;

    vector<int> g2_vertices = g2.get_vertices();
    vector<pair<int, int>> solution_vertices = start_point.get_vertices();


    // Read start solution as a mapping between g1 and g2 nodes
    for (unsigned int i = 0; i < solution_size; i++) {
        int g1_node = solution_vertices[i].first;
        int g2_node = solution_vertices[i].second;
        g2_to_g1_mapping.insert({g2_node, g1_node});
        mapped_nodes.insert(g2_node);
    }

    for (unsigned int i = 0; i < g2.n(); i++) {
        if (mapped_nodes.find(g2_vertices[i]) == mapped_nodes.end()) {
            unmapped_nodes.insert(g2_vertices[i]);
            unmapped_nodes_vector.push_back(g2_vertices[i]);
        }
    }

    // Search for max degree
    unsigned int max_degree = 0;
    for (unsigned int i = 0; i < g1.n(); i++) {
        if (g1.degree(g1.get_vertices()[i]) > max_degree) {
            max_degree = g1.degree(g1.get_vertices()[i]);
        }
    }
    cout << "MAX DEGREE " << max_degree << endl;

    bool stop = false;
    int iteration_count = 0;

    vector<movement> tabu_list;

    movement_compare mc(edges_vs_time, max_degree, &tabu_list);

    priority_queue<movement, vector<movement>,
        movement_compare> tabu_queue(mc);

    int max_edge_diff = 0;

    // Here is where the solution will be saved at the end of each iteration
    graph<pair<int, int>>* best_sol;

    best_sol = start_point.clone();

    // Get initial solution
    while (! stop && (iteration_limit < 0 || iteration_count < iteration_limit)) {
        bool any_improvement = improve_solution(
            best_sol,
            g1,
            g2,
            g2_to_g1_mapping,
            mapped_nodes,
            unmapped_nodes,
            unmapped_nodes_vector,
            neighbourhood_proportion,
            strict_comparisons,
            tabu_list_size,
            tabu_queue,
            mc,
            tabu_list,
            false,
            time_delta,
            max_edge_diff,
            aspiration_threshold
        );
        if (! any_improvement) {
            stop = true;
        }

        iteration_count++;
    }

    // std::cout << "LOCAL SEARCH: " << best_sol->n() << " nodes, " << best_sol->m() << " edges\n";

    // This will be the initial solution from which we'll move
    graph<pair<int, int>>* neighbour_sol = best_sol->clone();

    stop = false;
    iteration_count = 0;
    int no_gain_iterations = 0;

    // Move to neighbour solutions in search of a better one
    while (! stop && (iteration_limit < 0 || iteration_count < iteration_limit)
        && no_gain_iteration_limit > no_gain_iterations
    ) {
        bool any_modification = improve_solution(
            neighbour_sol,
            g1,
            g2,
            g2_to_g1_mapping,
            mapped_nodes,
            unmapped_nodes,
            unmapped_nodes_vector,
            neighbourhood_proportion,
            strict_comparisons,
            tabu_list_size,
            tabu_queue,
            mc,
            tabu_list,
            true,
            time_delta,
            max_edge_diff,
            aspiration_threshold
        );
        if (! any_modification) {
            stop = true;
        }
        else {
            // If we find a better solution, we update the best found
            if (neighbour_sol->m() > best_sol->m()) {
                *best_sol = *neighbour_sol;
                no_gain_iterations = 0;
            }
            else {
                no_gain_iterations++;
            }
        }
        iteration_count++;
    }

    delete neighbour_sol;

    return best_sol;
}
