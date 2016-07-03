#include <stdlib.h>  // rand
#include <time.h>    // time
#include "heuristics.h"
// #include "../framework/utils/chronometer.h"

/*
**  Local search heuristic
*/

using namespace std;

graph<pair<int, int>>* solve_local_search_1(
    graph<int>& g1,
    graph<int>& g2,
    graph<pair<int, int>>& start_point,
    int iteration_limit,
    float neighbourhood_proportion,
    bool strict_comparisons
) {
    // We assume #V(g1) < #V(g2), #V(start_point) == #V(g_1)

    unsigned int solution_size = start_point.n();

    // Stores the node in g1 that corresponds to each node in g2
    unordered_map<int, int> g2_to_g1_mapping;

    // Keeps track of g2 vertices which are not mapped to any vertex in g1
    vector<int> unmapped_nodes;
    unordered_set<int> unmapped_nodes_set;

    vector<int> g2_vertices = g2.get_vertices();
    vector<pair<int, int>> solution_vertices = start_point.get_vertices();

    // Solution is a mapping between g1 and g2 nodes
    for (unsigned int i = 0; i < solution_size; i++) {
        g2_to_g1_mapping.insert({
            solution_vertices[i].second,
            solution_vertices[i].first
        });
    }

    for (unsigned int i = 0; i < g2.n(); i++) {
        bool mapped = false;
        for (unsigned int j = 0; j < solution_size; j++) {
            if (solution_vertices[j].second == g2_vertices[i]) {
                mapped = true;
                break;
            }
        }
        if (! mapped) {
            unmapped_nodes.push_back(g2_vertices[i]);
            unmapped_nodes_set.insert(g2_vertices[i]);
        }
    }

    bool stop = false;
    int iteration_count = 0;
    graph<pair<int, int>>* ret = start_point.clone();

    while (! stop && (iteration_limit < 0 || iteration_count < iteration_limit)) {
        // Neighbourhood is of quadratic size
        vector<pair<int, int>> solution_vertices =
            ret->get_vertices();

        bool any_improvement = false;
        pair<int, int> best_to_remove;
        pair<int, int> best_to_add;
        int best_edge_diff = 0;
        vector<int> best_new_edges;

        // This iterates over every pair present in the solution, each of
        // which corresponds to a vertex in g1
        for (unsigned int i = 0; i < solution_size; i++) {
            // This iterates over the possible nodes in g2 to which the
            // current g1 vertex could be associated

            // Allows a limit for the size of neighbourhood
            int neighbourhood_size = unmapped_nodes.size();

            // for (unsigned int j = 0; j < neighbourhood_size; j++) {
            for (unsigned int j = 0; j < neighbourhood_size; j++) {
                if (rand() < neighbourhood_proportion * RAND_MAX) {
                    // Possible new pair. Let's evaluate its potential
                    int node_mapped    = solution_vertices[i].first;   // part of g1
                    int node_to_remove = solution_vertices[i].second;  // part of g2
                    int node_to_add    = unmapped_nodes[j];            // part of g2

                    int lost_edges = ret->degree({node_mapped, node_to_remove});
                    vector<int> new_edges;

                    vector<int> node_to_add_neigh = g2.neighbours(node_to_add);
                    for (unsigned int k = 0; k < node_to_add_neigh.size(); k++) {
                        if (node_to_add_neigh[k] != node_to_remove &&
                            unmapped_nodes_set.find(node_to_add_neigh[k]) ==
                                unmapped_nodes_set.end() &&
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
            ret->remove_node(best_to_remove);
            g2_to_g1_mapping.erase(best_to_remove.second);
            unmapped_nodes.push_back(best_to_remove.second);
            unmapped_nodes_set.insert(best_to_remove.second);

            ret->add_node(best_to_add);
            g2_to_g1_mapping.insert({best_to_add.second, best_to_add.first});
            unmapped_nodes.erase(find(unmapped_nodes.begin(),
                unmapped_nodes.end(), best_to_add.second));
            unmapped_nodes_set.erase(best_to_add.second);

            for (unsigned int i = 0; i < best_new_edges.size(); i++) {
                pair<int, int> new_edge_dest = {
                    g2_to_g1_mapping[best_new_edges[i]],
                    best_new_edges[i]
                };
                ret->add_edge(best_to_add, new_edge_dest);
            }
        } else {
            stop = true;
        }


        iteration_count++;
    }

    return ret;
}
