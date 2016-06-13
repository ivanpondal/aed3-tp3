#include <vector>
#include <stack>
#include <iostream>
#include "framework/graph.h"
#include "framework/adj_list_graph.h"

using namespace std;

class subgraph {
 private:
    const graph<int>* parent_graph;
 public:
    int node_count;
    // int edge_count; TODO
    vector<bool> vertices;

    subgraph();
    subgraph(const graph<int>* g);
    subgraph(const graph<int>* g, vector<int> v);
    subgraph(const graph<int>* g, vector<bool> v);

    int get_vertex() const;
    void substract(const subgraph&);

    friend ostream& operator<<(ostream& os, subgraph const& h);
};


enum cotree_operation {join, disj_union};
enum cotree_node_type {temporal, operation, leaf};

class cotree_node {
 private:
    cotree_node* right_child;
    cotree_node* left_child;
    
 public:
    cotree_node* get_right_child();
    cotree_node* get_left_child();
    void set_right_child(cotree_node*);
    void set_left_child(cotree_node*);

    virtual cotree_node_type get_type() const = 0;

    cotree_node() :
        right_child(NULL),
        left_child(NULL)
    {}

    ~cotree_node() {
        delete right_child;
        delete left_child;
    }

    friend ostream& operator<<(ostream& os, const cotree_node& n);
};

cotree_node* cotree_node::get_right_child() {
    return right_child;
}
cotree_node* cotree_node::get_left_child() {
    return left_child;
}

void cotree_node::set_right_child(cotree_node* node) {
    right_child = node;
}
void cotree_node::set_left_child(cotree_node* node) {
    left_child = node;
}

class cotree_node_operation : public cotree_node {
 public:
    cotree_operation op;
    int ind_cograph_size;
    int ind_cograph_edge_count;

    cotree_node_type get_type() const {
        return operation;
    };
};

class cotree_node_leaf : public cotree_node {
 public:
    int vertex;

    cotree_node_leaf(int v) :
        vertex(v) {};

    cotree_node_type get_type() const {
        return leaf;
    };
};

subgraph::subgraph() {}

subgraph::subgraph(const graph<int>* g) : parent_graph(g) {
    node_count = parent_graph->n();
    vertices = vector<bool>(node_count, true);
}

subgraph::subgraph(const graph<int>* g, vector<int> v) : parent_graph(g) {
    node_count = v.size();
    vertices = vector<bool>(parent_graph->n(), false);
    for (int i = 0; i < v.size(); i++) {
        vertices[v[i]] = true;
    }
}

subgraph::subgraph(const graph<int>* g, vector<bool> v) : parent_graph(g), vertices(v) {
    node_count = 0;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]) {
            node_count++;
        }
    }
}

void subgraph::substract(const subgraph& h) {
    for (uint i; i < vertices.size(); i++) {
        if (vertices[i] && h.vertices[i]) {
            vertices[i] = false;
            node_count--;
        }
    }
}

int subgraph::get_vertex() const {
    int res = -1;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]) {
            res = i;
            break;
        }
    }
    return res;
}

ostream& operator<<(ostream& os, subgraph const& h) {
    bool first = true;
    os << "[";
    for (int i = 0; i < h.vertices.size(); i++) {
        if (h.vertices[i]) {
            if (!first) {
                os << ", ";
            } else {
                first = false;
            }
            os << i;
        }
    }
    os << "]";
    return os;
}


subgraph find_connected_comp(const graph<int>& g, const subgraph& h) {
    int initial_vertex = h.get_vertex();

    stack<int> to_explore;
    vector<bool> marked(g.n(), false);
    
    to_explore.push(initial_vertex);
    marked[initial_vertex] = true;

    while (! to_explore.empty()) {
        int current_vertex = to_explore.top();
        to_explore.pop();
        vector<int> neigh = g.neighbours(current_vertex);
        for (int i = 0; i < neigh.size(); i++) {
            int neigh_vertex = neigh[i];
            if (h.vertices[neigh_vertex] &&  !marked[neigh_vertex]) {
                marked[neigh_vertex] = true;
                to_explore.push(neigh_vertex);
            }
        }
    }

    return subgraph(&g, marked);
}

cotree_node* create_cotree(const graph<int>& g) {
    cotree_node* ret;
    graph<int>* gc = g.complement();

    tuple<subgraph, cotree_node_operation*, bool> start(
        subgraph(&g),
        NULL,
        false
    );

    stack<tuple<subgraph, cotree_node_operation*, bool>> to_expand;
    to_expand.push(start);

    while (! to_expand.empty()) {
        subgraph current_subgraph = get<0>(to_expand.top());
        cotree_node_operation* current_parent = get<1>(to_expand.top());
        bool current_is_left_child = get<2>(to_expand.top());
        to_expand.pop();

        if (current_subgraph.node_count == 1) {
            cotree_node* new_node =
                         new cotree_node_leaf(current_subgraph.get_vertex());
            
            if (current_parent == NULL) {
                ret = new_node;
            }
            else {
                if (current_is_left_child) {
                    current_parent->set_left_child(new_node);
                }
                else {
                    current_parent->set_right_child(new_node);
                }
            }
        }
        else {
            subgraph cc1 = find_connected_comp(g, current_subgraph);
            cotree_operation op;

            if (cc1.node_count == current_subgraph.node_count) {
                cc1 = find_connected_comp(*gc, current_subgraph);
                op = join;
            }
            else {
                op = disj_union;
            }
            
            subgraph cc2 = current_subgraph;
            cc2.substract(cc1);

            cotree_node_operation* new_node = new cotree_node_operation;
            new_node->op = op;

            if (current_parent == NULL) {
                ret = new_node;
            }
            else {
                if (current_is_left_child) {
                    current_parent->set_left_child(new_node);
                }
                else {
                    current_parent->set_right_child(new_node);
                }
            }

            if (cc1.node_count == 1) {
                cotree_node* cc1_node = new cotree_node_leaf(cc1.get_vertex());
                new_node->set_left_child(cc1_node);
            }
            else {
                tuple<subgraph, cotree_node_operation*, bool> cc1_node(
                    cc1, new_node, true
                );
                to_expand.push(cc1_node);
            }

            if (cc2.node_count == 1) {
                cotree_node* cc2_node = new cotree_node_leaf(cc2.get_vertex());
                new_node->set_right_child(cc2_node);
            }
            else {
                tuple<subgraph, cotree_node_operation*, bool> cc2_node(
                    cc2, new_node, false
                );
                to_expand.push(cc2_node);
            }
        }
    }

    delete gc;
    return ret;
}


int main() {
    adj_list_graph<int> g;
    g.add_node(0);
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);
    g.add_node(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    cotree_node* cot = create_cotree(g);
    delete cot;

    return 0;
}
