#include <unordered_map>
#include <vector>
#include "../framework/structures/graph.h"
#include "../framework/structures/adj_list_graph.h"
#include "../main.h"
#include "./exercise2.h"

using namespace std;

bool mcs_backtracking(
        graph<int> *g1,
        graph<int> *g2,
        graph<int> *subgraph,
        unordered_map<int, int> node_map,
        vector<int> remaining_g1_nodes,
        vector<int> remaining_g2_nodes
) {

    //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << endl;
    if (!remaining_g1_nodes.empty() && !remaining_g2_nodes.empty()) {

        graph<int> *max_subgraph = new adj_list_graph<int>();

        for (unsigned int remaining_g1_index = 0; remaining_g1_index < remaining_g1_nodes.size(); remaining_g1_index++) {
            for (unsigned int remaining_g2_index = 0; remaining_g2_index < remaining_g2_nodes.size(); remaining_g2_index++) {

                //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << endl;
                int g1_node = remaining_g1_nodes[remaining_g1_index];
                int g2_node = remaining_g2_nodes[remaining_g2_index];

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
                //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " cantVecinos " << g1_neighbours.size() << endl;
                for (unsigned int neighbour_index = 0; neighbour_index < g1_neighbours.size(); neighbour_index++) {

                    int g1_neighbour = g1_neighbours[neighbour_index];
                    //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " vecino " << g1_neighbour << endl;

                    // Check if the neighbour is in the subgraph
                    if (subgraph->contains(g1_neighbour)) {
                        // Check if the neighbour is mapped to a neighbour of the remaining_g2 node-to-map
                        int g2_mapped_node = node_map.at(g1_neighbour);
                        //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " es vecino " << endl;
                        if (g2->adjacent(g2_mapped_node, g2_node)) {
                            // Add edge
                            subgraph_copy->add_edge(g1_node, g1_neighbour);
                            //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " Agrega arista" << endl;
                        }
                    }
                }

                //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " sCopyN " << subgraph_copy->n() << " sCopyM " << subgraph_copy->m() << " entrada" << endl;
                mcs_backtracking(g1, g2, subgraph_copy, node_map_copy, remaining_g1_nodes_copy, remaining_g2_nodes_copy);
                //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " sCopyN "<< subgraph_copy->n() << " sCopyM " << subgraph_copy->m() << " salida" << endl;

                //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " r1 " << remaining_g1_index << " r2 " << remaining_g2_index << " subM " <<  subgraph_copy->m() << " maxM " << max_subgraph->m() << endl;
                if (subgraph_copy->m() >= max_subgraph->m()) {
                    *max_subgraph = *subgraph_copy;
                }
            }
        }

        //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " maxSubN " << max_subgraph->n() << " maxSubM " << max_subgraph->m() << endl;
        *subgraph = *max_subgraph;
        //cout << remaining_g1_nodes.size() << " " << remaining_g2_nodes.size() << " subN " << subgraph->n() << " subM " << subgraph->m() << endl;
    }

    return true;
}

void chota(graph<int> *graph1) {
    graph<int> *asd = new adj_list_graph<int>();
    asd->add_node(9);
    asd->add_node(8);
    *graph1 = *asd;
    cout << graph1->n() << endl;
}

graph<int>* mcs(graph<int> *g1, graph<int> *g2) {
    adj_list_graph<int> *empty_graph = new adj_list_graph<int>();
    unordered_map<int, int> empty_map;
     mcs_backtracking(g1, g2, empty_graph, empty_map, g1->get_vertices(), g2->get_vertices());
//    chota(empty_graph);
//    cout << empty_graph->n() << endl;
    return empty_graph;
}

void run_solution() {
    adj_list_graph<int> g1, g2;
    adj_list_graph<int> empty_subgraph;
    unordered_map<int, int> empty_map;

    unsigned int n;
    unsigned int m;

    cout << endl;
    cout << "First graph" << endl;
    cout << "Nodes: ";

    cin >> n;

    for (unsigned int i = 1; i <= n; i++) {
        g1.add_node(i);
    }

    cout << "Edges: ";

    cin >> m;

    cout << "List of edges:" << endl;

    for (unsigned int i = 0; i < m; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        g1.add_edge(node1, node2);
    }

    cout << endl;
    cout << "Second graph" << endl;
    cout << "Nodes: ";

    cin >> n;

    for (unsigned int i = 1; i <= n; i++) {
        g2.add_node(i);
    }

    cout << "Edges: ";

    cin >> m;

    cout << "List of edges:" << endl;

    for (unsigned int i = 0; i < m; i++) {
        int node1, node2;
        cin >> node1 >> node2;
        g2.add_edge(node1, node2);
    }

    mcs(&g1, &g2);
}