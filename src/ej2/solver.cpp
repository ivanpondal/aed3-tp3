#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <unistd.h>
#include "../main.h"
#include "ej2.h"

using namespace std;

std::ostream &operator<<(std::ostream &output, list<int> &lista){
    for (list<int>::iterator it = lista.begin(); it != lista.end(); it++)
        output << *it << " ";
    output << endl;

    return output;
}

unsigned int degree_sum(graph<int> *g, list<int> remaining_nodes) {
    int sum = 0;
    for (list<int>::iterator it = remaining_nodes.begin(); it != remaining_nodes.end(); it++) {
        sum += g->degree(*it);
    }
    return sum;
}

bool mcs_backtracking(
        graph<int> *g1,
        graph<int> *g2,
        // graph<int> *subgraph,
        graph<pair<int, int> > *subgraph,
        unordered_map<int, int> node_map,
        list<int> &g1_remaining_nodes,
        list<int> &g2_remaining_nodes,
        // list<int>::iterator &g1_insert_it,
        // list<int>::iterator &g2_insert_it,
        // unsigned int g1_insert_it_pos,
        // unsigned int g2_insert_it_pos,
        unsigned int &maxEdges,
        unordered_set<tuple<int, int, int, int>, hash_tuple_int> &permutations
) {

    if (subgraph->m() + degree_sum(g1, g1_remaining_nodes) <= maxEdges)
        return false;

    if (!g1_remaining_nodes.empty() && !g2_remaining_nodes.empty()) {

        graph<pair<int, int> > *max_subgraph = new adj_list_graph<pair<int, int> >();

        // This indexes will be used to prevent losing the reference to the iterator when an element is erased and re-inserted
        list<int>::iterator g1_remaining_nodes_it = g1_remaining_nodes.begin();
        unsigned int g1_remaining_nodes_index = 0;
        while (g1_remaining_nodes_it != g1_remaining_nodes.end()) {
            
            list<int>::iterator g2_remaining_nodes_it = g2_remaining_nodes.begin();
            unsigned int g2_remaining_nodes_index = 0;
            while (g2_remaining_nodes_it != g2_remaining_nodes.end()) {

                int g1_node = *g1_remaining_nodes_it;
                int g2_node = *g2_remaining_nodes_it;

                // Verify if actual mapping can be permuted with a previous branch (only if it is the second mapping)
                if (subgraph->n() == 1) {
                    unordered_map<int, int>::iterator map_it = node_map.begin();
                    tuple<int, int, int, int> permutation(map_it->first, map_it->second, g1_node, g2_node);
                    // pair<int, int> first_mapping = subgraph->get_vertices[0];
                    // tuple<int, int, int, int> permutation(first_mapping.first, first_mapping.second, g1_node, g2_node);
                    
                    // If actual mapping is a permutation of a already traversed mapping, it skips it
                    if (permutations.find(permutation) != permutations.end()) {
                        g2_remaining_nodes_it++;
                        g2_remaining_nodes_index++;
                        continue;
                    }
                    else {
                        tuple<int, int, int, int> reverse_permutation(g1_node, g2_node, map_it->first, map_it->second);
                        permutations.insert(reverse_permutation);
                    }
                }

                // Erase mapped nodes from list of remaining
                g1_remaining_nodes.erase(g1_remaining_nodes_it);
                g2_remaining_nodes.erase(g2_remaining_nodes_it);

                pair<int, int> actual_mapping(g1_node,g2_node);

                // Copy unordered_map and map nodes
                unordered_map<int, int> node_map_copy = node_map;
                node_map_copy.insert(actual_mapping);

                // Copy subgraph and dd new node
                graph<pair<int, int> > *subgraph_copy = subgraph->clone();
                // subgraph_copy->add_node(g1_node);
                subgraph_copy->add_node(actual_mapping);

                // Add edges to the existing neighbours
                vector<int> g1_neighbours = g1->neighbours(g1_node);
                for (unsigned int neighbour_index = 0; neighbour_index < g1_neighbours.size(); neighbour_index++) {

                    int g1_neighbour = g1_neighbours[neighbour_index];

                    // Check if the neighbour is in the subgraph
                    if (node_map.find(g1_neighbour) != node_map.end()) {
                        int g2_mapped_node = node_map.at(g1_neighbour);
                        
                        // Check if the neighbour is mapped to a neighbour of the remaining_g2 node-to-map
                        if (g2->adjacent(g2_mapped_node, g2_node)) {
                            // Add edge
                            pair<int, int> subgraph_neighbour_node(g1_neighbour, g2_mapped_node);
                            subgraph_copy->add_edge(actual_mapping, subgraph_neighbour_node);
                        }
                    }
                }

                bool valid_subgraph = mcs_backtracking( g1,
                                                        g2,
                                                        subgraph_copy,
                                                        node_map_copy,
                                                        g1_remaining_nodes,
                                                        g2_remaining_nodes,
                                                        // g1_remaining_nodes_it,
                                                        // g2_remaining_nodes_it,
                                                        // g1_remaining_nodes_index,
                                                        // g2_remaining_nodes_index,
                                                        maxEdges,
                                                        permutations);
                
                if (valid_subgraph && subgraph_copy->m() >= max_subgraph->m()) {
                    *max_subgraph = *subgraph_copy;
                    
                    if (max_subgraph->m() > maxEdges)
                        maxEdges = max_subgraph->m();
                }

                delete(subgraph_copy);

                // Move iterator to position
                g1_remaining_nodes_it = g1_remaining_nodes.begin();
                for (unsigned int i = 0; i < g1_remaining_nodes_index; i++)
                    g1_remaining_nodes_it++;

                
                g2_remaining_nodes_it = g2_remaining_nodes.begin();
                for (unsigned int i = 0; i < g2_remaining_nodes_index; i++)
                    g2_remaining_nodes_it++;

                // Re-insert previously erased nodes to remaining nodes lists
                g1_remaining_nodes.insert(g1_remaining_nodes_it, g1_node);
                g1_remaining_nodes_it--;
                g2_remaining_nodes.insert(g2_remaining_nodes_it, g2_node);

                // The indexes are necessary to track which position was erased in the previous call of the function
                // If the element that is being re-inserted matches that position, then the iterator is stored in the iterator passed by refference
                // if (g1_remaining_nodes_index == g1_insert_it_pos)
                //     g1_insert_it = g1_remaining_nodes.insert(g1_remaining_nodes_it, g1_node);
                // else
                //     g1_remaining_nodes.insert(g1_remaining_nodes_it, g1_node);

                // if (g2_remaining_nodes_index == g2_insert_it_pos)
                //     g2_insert_it = g2_remaining_nodes.insert(g2_remaining_nodes_it, g2_node);
                // else
                //     g2_remaining_nodes.insert(g2_remaining_nodes_it, g2_node);

                g2_remaining_nodes_index++;
            }

            g1_remaining_nodes_it++;
            g1_remaining_nodes_index++;
        }

        *subgraph = *max_subgraph;
        delete(max_subgraph);
    }

    return true;
}

graph<pair<int, int> >* mcs(graph<int> *g1, graph<int> *g2) {
    adj_list_graph<pair<int, int> > *empty_graph = new adj_list_graph<pair<int, int> >();
    unordered_map<int, int> empty_map;
    unordered_set<tuple<int, int, int, int>, hash_tuple_int> permutations;
    unsigned int edges = 0;

    vector<int> g1_vertices = g1->get_vertices();
    vector<int> g2_vertices = g2->get_vertices();
    list<int> g1_list, g2_list;

    for (vector<int>::iterator it = g1_vertices.begin(); it != g1_vertices.end(); it++) {
        g1_list.push_back(*it);
    }

    for (vector<int>::iterator it = g2_vertices.begin(); it != g2_vertices.end(); it++)
        g2_list.push_back(*it);

    mcs_backtracking(   g1,
                        g2,
                        empty_graph,
                        empty_map,
                        g1_list,
                        g2_list,
                        // g1_begining_it,
                        // g2_begining_it,
                        // 0,
                        // 0,
                        edges,
                        permutations);
    
    return empty_graph;
}

solution run_solver(graph<int> &g1, graph<int> &g2) {
    graph<std::pair<int, int>> *maxComSub = mcs(&g1, &g2);
    return pairs_to_solution(maxComSub);
}