#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <unistd.h>
#include "../main.h"
#include "ej2.h"

using namespace std;

int podas = 0;
int super_podas = 0;

int degree_sum(graph<int> *g, vector<int> remaining_nodes) {
    int sum = 0;
    for (vector<int>::iterator it = remaining_nodes.begin(); it != remaining_nodes.end(); it++) {
        sum += g->degree(*it);
    }
    return sum;
}

bool mcs_backtracking(
        graph<int> *g1,
        graph<int> *g2,
        graph<int> *subgraph,
        unordered_map<int, int> node_map,
        list<int> remaining_g1_nodes,
        list<int> remaining_g2_nodes,
        int &maxEdges,
        unordered_set<tuple<int, int, int, int>, hash_tuple_int> &permutations
) {

    if (subgraph->m() + degree_sum(g1, remaining_g1_nodes) <= maxEdges) {
        podas++;
        return false;
    }

    if (!remaining_g1_nodes.empty() && !remaining_g2_nodes.empty()) {

        graph<int> *max_subgraph = new adj_list_graph<int>();

        for (unsigned int remaining_g1_index = 0; remaining_g1_index < remaining_g1_nodes.size(); remaining_g1_index++) {
            for (unsigned int remaining_g2_index = 0; remaining_g2_index < remaining_g2_nodes.size(); remaining_g2_index++) {

                int g1_node = remaining_g1_nodes[remaining_g1_index];
                int g2_node = remaining_g2_nodes[remaining_g2_index];
                // cout << "(" << setfill(' ') << setw(2) <<  g1_node << "," << setfill(' ') << setw(2) << g2_node << ") " << flush;

                // Verify if actual mapping can be permuted with a previous branch (only if it is the second mapping)
                if (subgraph->n() == 1) {
                    unordered_map<int, int>::iterator it = node_map.begin();
                    tuple<int, int, int, int> permutation(it->first, it->second, g1_node, g2_node);
                    
                    if (permutations.find(permutation) != permutations.end()) {
                        super_podas++;
                        // cout << "\b\b\b\b\b\b\b\b" << flush;
                        continue;
                    }
                    else {
                        tuple<int, int, int, int> reverse_permutation(g1_node, g2_node, it->first, it->second);
                        permutations.insert(reverse_permutation);
                    }
                }

                // Copy remaining nodes and erase actual nodes from the copies
                vector<int> remaining_g1_nodes_copy = remaining_g1_nodes;
                vector<int> remaining_g2_nodes_copy = remaining_g2_nodes;
                remaining_g1_nodes_copy.erase(remaining_g1_nodes_copy.begin() + remaining_g1_index);
                remaining_g2_nodes_copy.erase(remaining_g2_nodes_copy.begin() + remaining_g2_index);

                // Map nodes
                unordered_map<int, int> node_map_copy = node_map;
                pair<int, int> par(g1_node,g2_node);
                node_map_copy.insert(par);

                // Add new node to subgraph
                graph<int> *subgraph_copy = subgraph->clone();
                subgraph_copy->add_node(g1_node);

                // Add edges to the existing neighbours
                vector<int> g1_neighbours = g1->neighbours(g1_node);
                for (unsigned int neighbour_index = 0; neighbour_index < g1_neighbours.size(); neighbour_index++) {

                    int g1_neighbour = g1_neighbours[neighbour_index];

                    // Check if the neighbour is in the subgraph
                    if (subgraph->contains(g1_neighbour)) {
                        // Check if the neighbour is mapped to a neighbour of the remaining_g2 node-to-map
                        int g2_mapped_node = node_map.at(g1_neighbour);
                        if (g2->adjacent(g2_mapped_node, g2_node)) {
                            // Add edge
                            subgraph_copy->add_edge(g1_node, g1_neighbour);
                        }
                    }
                }

                bool valid_subgraph = mcs_backtracking(g1, g2, subgraph_copy, node_map_copy, remaining_g1_nodes_copy, remaining_g2_nodes_copy, maxEdges, permutations);

                if (valid_subgraph && subgraph_copy->m() >= max_subgraph->m()) {
                    *max_subgraph = *subgraph_copy;
                    
                    if (max_subgraph->m() > maxEdges)
                        maxEdges = max_subgraph->m();
                }
                
                delete(subgraph_copy);

                // cout << "\b\b\b\b\b\b\b\b" << flush;
            }
        }

        *subgraph = *max_subgraph;
        delete(max_subgraph);
    }

    return true;
}

graph<int>* mcs(graph<int> *g1, graph<int> *g2) {
    adj_list_graph<int> *empty_graph = new adj_list_graph<int>();
    unordered_map<int, int> empty_map;
    unordered_set<tuple<int, int, int, int>, hash_tuple_int> permutations;
    int edges = 0;

    vector<int> g1_vertices = g1->get_vertices();
    vector<int> g2_vertices = g2->get_vertices();
    list<int> g1_list, g2_list;

    for (vector<int>::iterator it = g1_vertices.begin(); it != g1_vertices.end(); it++)
        g1_list.push_back(*it);

    for (vector<int>::iterator it = g2_vertices.begin(); it != g2_vertices.end(); it++)
        g2_list.push_back(*it);

    mcs_backtracking(g1, g2, empty_graph, empty_map, g1_list, g2_list, edges, permutations);

    cout << endl << "podas: " << podas << endl;
    cout << "super_podas: " << super_podas << endl;
    
    return empty_graph;
}

solution run_solver(graph<int> &g1, graph<int> &g2) {

}raph<int> &g2) {


}