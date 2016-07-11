#include <stdlib.h>  // rand
#include <time.h>    // time
#include <cassert>
#include "heuristics.h"
#include "../framework/utils/chronometer.h"

/*
**  Local search heuristic
**  IMPORTANT: This algorithm assumes g2 is larger (has more or the same
**  amount of vertices) than g2. Adittionaly, if g1 and g2 have the same size,
**  some neighbourhood types may not work properly.
*/

using namespace std;


// Forward declarations
// --------------------

bool improve_solution_1(
    graph<pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    unordered_map<int, int>& g2_to_g1_mapping,
    unordered_set<int>& mapped_nodes,
    unordered_set<int>& unmapped_nodes,
    vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
);

bool improve_solution_2(
    graph<pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    unordered_map<int, int>& g2_to_g1_mapping,
    unordered_set<int>& mapped_nodes,
    unordered_set<int>& unmapped_nodes,
    vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
);


// Main heuristic structure
// ------------------------

graph<pair<int, int>>* solve_local_search(
    graph<int>& g1,
    graph<int>& g2,
    graph<pair<int, int>>& start_point,
    int neighbourhood_type,
    int iteration_limit,
    float neighbourhood_proportion,
    bool strict_comparisons
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
        bool
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

    bool stop = false;
    int iteration_count = 0;

    // Here is where the solution will be saved at the end of each iteration
    graph<pair<int, int>>* ret;

    ret = start_point.clone();

    while (! stop && (iteration_limit < 0 || iteration_count < iteration_limit)) {
        // cout<< "iteration_count: " << iteration_count << endl;
        bool any_improvement = improve_solution(
            ret,
            g1,
            g2,
            g2_to_g1_mapping,
            mapped_nodes,
            unmapped_nodes,
            unmapped_nodes_vector,
            neighbourhood_proportion,
            strict_comparisons
        );
        if (! any_improvement) {
            stop = true;
        }

        iteration_count++;
    }

    return ret;
}


// Neighbourhood type 1
// --------------------

// Each iteration exchanges one node of g2 in the mapping for one that is not
// mapped to any node of g1

bool improve_solution_1(
    graph<pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    unordered_map<int, int>& g2_to_g1_mapping,
    unordered_set<int>& mapped_nodes,
    unordered_set<int>& unmapped_nodes,
    vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
) {
    vector<pair<int, int>> solution_vertices =
        solution->get_vertices();


    bool any_improvement = false;
    pair<int, int> best_to_remove;
    pair<int, int> best_to_add;
    int best_edge_diff = 0;
    vector<int> best_new_edges;

    // This iterates over every pair present in the solution, each of
    // which corresponds to a vertex in g1
    for (unsigned int i = 0; i < solution->n(); i++) {
        // This iterates over the possible nodes in g2 to which the
        // current g1 vertex could be associated

        unsigned int neighbourhood_size = unmapped_nodes_vector.size();

        for (unsigned int j = 0; j < neighbourhood_size; j++) {
            if (rand() < neighbourhood_proportion * RAND_MAX) {
                // Possible new pair. Let's evaluate its potential
                int node_mapped    = solution_vertices[i].first;   // part of g1
                int node_to_remove = solution_vertices[i].second;  // part of g2
                int node_to_add    = unmapped_nodes_vector[j];     // part of g2

                int lost_edges = solution->degree({node_mapped, node_to_remove});
                vector<int> new_edges;

                vector<int> node_to_add_neigh = g2.neighbours(node_to_add);
                for (unsigned int k = 0; k < node_to_add_neigh.size(); k++) {
                    if (node_to_add_neigh[k] != node_to_remove &&
                        unmapped_nodes.find(node_to_add_neigh[k]) ==
                            unmapped_nodes.end() &&
                        g1.adjacent(node_mapped,
                            g2_to_g1_mapping[node_to_add_neigh[k]])
                    )
                    {
                        new_edges.push_back(node_to_add_neigh[k]);
                    }
                }

                int edge_diff = new_edges.size() - lost_edges;
                bool is_improvement = strict_comparisons
                                        ? edge_diff > best_edge_diff
                                        : edge_diff >= best_edge_diff;

                if (is_improvement) {
                    any_improvement = true;
                    best_to_add = {node_mapped, node_to_add};
                    best_to_remove = {node_mapped, node_to_remove};
                    best_edge_diff = edge_diff;
                    best_new_edges = new_edges;
                }

            }
        }
    }


    if (any_improvement) {
        solution->remove_node(best_to_remove);
        g2_to_g1_mapping.erase(best_to_remove.second);
        unmapped_nodes_vector.push_back(best_to_remove.second);
        unmapped_nodes.insert(best_to_remove.second);

        solution->add_node(best_to_add);
        g2_to_g1_mapping.insert({best_to_add.second, best_to_add.first});
        unmapped_nodes_vector.erase(find(unmapped_nodes_vector.begin(),
            unmapped_nodes_vector.end(), best_to_add.second));
        unmapped_nodes.erase(best_to_add.second);

        for (unsigned int i = 0; i < best_new_edges.size(); i++) {
            pair<int, int> new_edge_dest = {
                g2_to_g1_mapping[best_new_edges[i]],
                best_new_edges[i]
            };
            solution->add_edge(best_to_add, new_edge_dest);
        }

        return true;
    } else {
        return false;
    }
}


// Neighbourhood type 2
// --------------------

// Each iteration either exchanges one node of g2 in the mapping for one that
// is not mapped to any node of g1, or swaps two nodes of g2 in the mapping

bool improve_solution_2(
    graph<pair<int, int>>* solution,
    graph<int>& g1,
    graph<int>& g2,
    unordered_map<int, int>& g2_to_g1_mapping,
    unordered_set<int>& mapped_nodes,
    unordered_set<int>& unmapped_nodes,
    vector<int>& unmapped_nodes_vector,
    float neighbourhood_proportion,
    bool strict_comparisons
) {
    enum action_type {none, swap, exchange};

    vector<pair<int, int>> solution_vertices = solution->get_vertices();
    vector<int> g2_vertices = g2.get_vertices();

    bool any_improvement = false;
    int best_edge_diff = 0;
    action_type best_action = none;
    pair<int, int> best_node_1;
    pair<int, int> best_node_2;
    vector<int> best_new_edges_1;
    vector<int> best_new_edges_2;

    for (unsigned int i = 0; i < g2.n(); i++) {
        bool i_mapped = mapped_nodes.find(g2_vertices[i]) != mapped_nodes.end();
        for (unsigned int j = 0; j < i; j++) {
            if (rand() < neighbourhood_proportion * RAND_MAX) {
                bool j_mapped = mapped_nodes.find(g2_vertices[j]) != mapped_nodes.end();

                action_type action;
                int node_1;  // to add if exchange
                int node_2;  // to remove if exchange
                int node_1_mapped;
                int node_2_mapped;
                int lost_edges;
                vector<int> new_edges_1;
                vector<int> new_edges_2;
                int edge_diff = -1;  // to avoid trying to make invalid moves

                if (i_mapped && j_mapped) {
                    // cout << "  try SWAP  " << g2_vertices[i] << " <-> " << g2_vertices[j] << endl;
                    action = swap;

                    node_1 = g2_vertices[i];
                    node_2 = g2_vertices[j];
                    node_1_mapped = g2_to_g1_mapping[node_1];
                    node_2_mapped = g2_to_g1_mapping[node_2];

                    lost_edges =
                        solution->degree({node_1_mapped, node_1}) +
                        solution->degree({node_2_mapped, node_2});
                    if (solution->adjacent({node_1_mapped, node_1}, {node_2_mapped, node_2})) {
                        lost_edges -= 2;
                    }

                    vector<int> node_1_neigh = g2.neighbours(node_1);
                    for (unsigned int k = 0; k < node_1_neigh.size(); k++) {
                        if (node_1_neigh[k] != node_2 &&
                            unmapped_nodes.find(node_1_neigh[k]) ==
                                unmapped_nodes.end() &&
                            g1.adjacent(node_2_mapped,
                                g2_to_g1_mapping[node_1_neigh[k]])
                        )
                        {
                            new_edges_1.push_back(node_1_neigh[k]);
                        }
                    }

                    vector<int> node_2_neigh = g2.neighbours(node_2);
                    for (unsigned int k = 0; k < node_2_neigh.size(); k++) {
                        if (node_2_neigh[k] != node_1 &&
                            unmapped_nodes.find(node_2_neigh[k]) ==
                                unmapped_nodes.end() &&
                            g1.adjacent(node_1_mapped,
                                g2_to_g1_mapping[node_2_neigh[k]])
                        )
                        {
                            new_edges_2.push_back(node_2_neigh[k]);
                        }
                    }
                    // cout << "      lost edges:  " << lost_edges  << endl;
                    // cout << "      new edges 1: " << new_edges_1 << endl;
                    // cout << "      new edges 2: " << new_edges_2 << endl;

                    edge_diff = new_edges_1.size() + new_edges_2.size() - lost_edges;
                    // cout << "    edge diff: " << edge_diff << endl;
                }
                else if (i_mapped || j_mapped) {
                    unsigned int mapped_node = i_mapped ? i : j;
                    unsigned int unmapped_node = i_mapped ? j : i;
                    // cout << "  try EXCHG " << g2_vertices[mapped_node] << " --> " << g2_vertices[unmapped_node] << endl;
                    action = exchange;

                    node_1        = g2_vertices[unmapped_node]; // to add, part of g2
                    node_2        = g2_vertices[mapped_node];   // to remove, part of g2
                    node_2_mapped = g2_to_g1_mapping[node_2];   // part of g1
                    node_1_mapped = node_2_mapped;

                    lost_edges = solution->degree({node_2_mapped, node_2});

                    vector<int> node_1_neigh = g2.neighbours(node_1);
                    for (unsigned int k = 0; k < node_1_neigh.size(); k++) {
                        if (node_1_neigh[k] != node_2 &&
                            unmapped_nodes.find(node_1_neigh[k]) ==
                                unmapped_nodes.end() &&
                            g1.adjacent(node_1_mapped,
                                g2_to_g1_mapping[node_1_neigh[k]])
                        )
                        {
                            new_edges_1.push_back(node_1_neigh[k]);
                        }
                    }

                    // cout << "      lost edges: " << lost_edges  << endl;
                    // cout << "      new edges:  " << new_edges_1 << endl;

                    edge_diff = new_edges_1.size() - lost_edges;
                    // cout << "    edge diff: " << edge_diff << endl;
                }

                bool is_improvement = strict_comparisons
                                        ? edge_diff > best_edge_diff
                                        : edge_diff >= best_edge_diff;

                if (is_improvement) {
                    any_improvement = true;
                    best_edge_diff = edge_diff;
                    best_action = action;
                    best_node_1 = {node_1_mapped, node_1};
                    best_node_2 = {node_2_mapped, node_2};
                    best_new_edges_1 = new_edges_1;
                    best_new_edges_2 = new_edges_2;
                }
            }
        }
    }

    if (any_improvement) {
        if (best_action == swap) {
            // cout << "best action SWAP  " << best_node_1 << " <-> " << best_node_2 << " (" << best_edge_diff << ")" << endl;

            bool swapping_adjacents = solution->adjacent(best_node_1, best_node_2);
            solution->remove_node(best_node_1);
            solution->remove_node(best_node_2);

            pair<int, int> new_node_1 = {best_node_2.first, best_node_1.second};
            pair<int, int> new_node_2 = {best_node_1.first, best_node_2.second};

            solution->add_node(new_node_1);
            solution->add_node(new_node_2);

            if (swapping_adjacents) {
                solution->add_edge(new_node_1, new_node_2);
            }

            for (unsigned int i = 0; i < best_new_edges_1.size(); i++) {
                pair<int, int> new_edge_dest = {
                    g2_to_g1_mapping[best_new_edges_1[i]],
                    best_new_edges_1[i]
                };
                solution->add_edge(new_node_1, new_edge_dest);
            }

            for (unsigned int i = 0; i < best_new_edges_2.size(); i++) {
                pair<int, int> new_edge_dest = {
                    g2_to_g1_mapping[best_new_edges_2[i]],
                    best_new_edges_2[i]
                };
                solution->add_edge(new_node_2, new_edge_dest);
            }

            g2_to_g1_mapping[new_node_1.second] = new_node_1.first;
            g2_to_g1_mapping[new_node_2.second] = new_node_2.first;
        }

        else if (best_action == exchange) {
            // cout << "best action EXCHG " << best_node_2 << " --> " << best_node_1 << " (" << best_edge_diff << ")" << endl;
            solution->remove_node(best_node_2);
            g2_to_g1_mapping.erase(best_node_2.second);
            mapped_nodes.erase(best_node_2.second);
            unmapped_nodes.insert(best_node_2.second);
            unmapped_nodes_vector.push_back(best_node_2.second);

            solution->add_node(best_node_1);
            g2_to_g1_mapping.insert({best_node_1.second, best_node_1.first});
            mapped_nodes.insert(best_node_1.second);
            unmapped_nodes.erase(best_node_1.second);
            unmapped_nodes_vector.erase(find(unmapped_nodes_vector.begin(),
                unmapped_nodes_vector.end(), best_node_1.second));

            for (unsigned int i = 0; i < best_new_edges_1.size(); i++) {
                pair<int, int> new_edge_dest = {
                    g2_to_g1_mapping[best_new_edges_1[i]],
                    best_new_edges_1[i]
                };
                solution->add_edge(best_node_1, new_edge_dest);
            }
        }

        return true;
    } else {
        // cout << "no improvements are possible" << endl;
        return false;
    }
}
