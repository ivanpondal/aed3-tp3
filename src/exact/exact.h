#ifndef EXACT_H
#define EXACT_H

#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../main.h"

/*
**  Exact algorithms
*/

graph<std::pair<int, int> >* solve_backtracking(graph<int> *g1, graph<int> *g2);

solution solve_cograph_vs_complete(graph<int>& g1, graph<int>& g2);

struct hash_tuple_int{
	size_t operator()(const std::tuple<int, int, int, int> &t) const{
		size_t seed = 0;
		seed ^= std::hash<int>()(std::get<0>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(std::get<1>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(std::get<2>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= std::hash<int>()(std::get<3>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		return seed;
	}
};

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.


//  Subgraphs (implemented as vector of booleans)
//  ---------

class subgraph {
 private:
    uint vertex_count_val;
    std::vector<bool> vertices;
 public:
    subgraph();
    subgraph(uint graph_size);
    subgraph(std::vector<int> v, uint graph_size);
    subgraph(std::vector<bool> v);

    // Yields a random vertex that belongs to the subgraph
    int get_vertex() const;

    // Returns a list of all nodes belonging to the subgraph
    std::vector<int> get_vertices() const;

    // Returns the amount of nodes that conform the subgraph
    uint vertex_count() const;

    // Decides if a certain node belongs to the subgraph
    bool contains(int vertex) const;

    // Computes the difference with another subgraph
    void substract(const subgraph&);

    // Finds and returns a connected component in the induced subgraph
    // (recieves as parameter the underlying graph)
    subgraph find_connected_comp(const graph<int>& g) const;

    // Prints a subgraph to an output stream
    friend std::ostream& operator<<(std::ostream& os, subgraph const& h);
};


//  Cotrees and cotree nodes
//  ------------------------

enum cotree_node_type {operation, leaf};

class cotree_node {
 private:
    cotree_node* right_child;
    cotree_node* left_child;

 public:
    cotree_node();
    virtual ~cotree_node();

    cotree_node* get_right_child() const;
    cotree_node* get_left_child() const;
    void set_right_child(cotree_node*);
    void set_left_child(cotree_node*);
    virtual cotree_node_type get_type() const = 0;
    virtual uint get_vertex_count() const = 0;
    virtual uint get_edge_count() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const cotree_node& n);
};


enum cotree_operation {join, disj_union};

class cotree_node_operation : public cotree_node {
 private:
    cotree_operation op;
    uint vertex_count;
    uint edge_count;
 public:
    cotree_node_operation();
    cotree_node_operation(cotree_operation op);
    cotree_node_operation(
        cotree_operation op,
        cotree_node* lc,
        cotree_node* rc
    );

    cotree_node_type get_type() const;
    cotree_operation get_operation() const;
    uint get_vertex_count() const;
    uint get_edge_count() const;
    void set_vertex_count(uint count);
    void set_edge_count(uint count);
};


class cotree_node_leaf : public cotree_node {
 private:
    int vertex;
 public:
    cotree_node_leaf();
    cotree_node_leaf(int v);

    cotree_node_type get_type() const;
    int get_vertex() const;
    uint get_vertex_count() const;
    uint get_edge_count() const;
};

// Prints a cotree
std::ostream& operator<<(std::ostream& os, cotree_node& n);

// Generates a cotree from a graph (requires graph to be cograph)
cotree_node* generate_cotree(const graph<int>&);

// Constructs a vector out of a cotree using BFS
struct info_cotree_node {
    cotree_node* node;
    int left_child_index;
    int right_child_index;
};

std::vector<info_cotree_node> vectorize(cotree_node* cotree);

graph<int>* complement(const graph<int>& g);

graph<int>* induced_supgraph(
    const graph<int>& g,
    const std::vector<int>& subgraph_vertices
);

#endif	// EXACT_H
