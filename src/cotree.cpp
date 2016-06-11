#include <vector>
#include <stack>
#include <iostream>
#include <graph.h>

using namespace std;

enum cotree_operation {join, disj_union};
enum cotree_node_type {temporal, operation, vertex};

class cotree {

};

class cotree_node {
 private:
    cotree_node* parent;
    cotree_node* right_child;
    cotree_node* left_child;
    
 public:
    cotree_node* get_parent();
    cotree_node* get_right_child();
    cotree_node* get_left_child();
    virtual cotree_node_type get_type();

    cotree_node() :
        parent(NULL),
        right_child(NULL),
        left_child(NULL),
    {}

    cotree_node* get_parent() {
        return parent;
    }
    cotree_node* get_right_child() {
        return right_child;
    }
    cotree_node* get_left_child() {
        return left_child;
    }

};

class cotree_node_temporal : public cotree_node {
 public:
    vector<bool> vertices;
    int ind_cograph_size;

    cotree_node_type get_type() {
        return temporal;
    }
};

class cotree_node_operation : public cotree_node {
 public:
    cotree_operation op;
    int ind_cograph_size;
    int ind_cograph_edge_count;

    cotree_node_type get_type() {
        return operation;
    }
};

class cotree_node_vertex : public cotree_node {
 public:
    int vertex;

    cotree_node_type get_type() {
        return vertex;
    }
};

typedef vector<vector<int>> graph;

class subgraph {
 private:
    const graph& parent_graph;
 public:
    int node_count;
    // int edge_count; TODO
    vector<bool> vertices;

    subgraph(const graph& g) : parent_graph(g) {
        node_count = parent_graph.size();
        vertices = vector<bool>(node_count, true);
    }

    subgraph(const graph& g, vector<int> v) : parent_graph(g) {
        node_count = v.size();
        vertices = vector<bool>(parent_graph.size(), false);
        for (int i = 0; i < v.size(); i++) {
            vertices[v[i]] = true;
        }
    }

    subgraph(const graph& g, vector<bool> v) : parent_graph(g), vertices(v) {
        node_count = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i]) {
                node_count++;
            }
        }
    }

    int get_vertex() const {
        int res = -1;
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i]) {
                res = i;
                break;
            }
        }
        return res;
    }

    friend ostream& operator<<(ostream& os, subgraph const& h) {
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
    };
};

subgraph find_connected_comp(const graph& g, const subgraph& h) {
    int initial_vertex = h.get_vertex();

    stack<int> to_explore;
    vector<bool> marked(g.size(), false);
    
    to_explore.push(initial_vertex);
    marked[initial_vertex] = true;

    while (! to_explore.empty()) {
        int current_vertex = to_explore.top();
        to_explore.pop();
        vector<int> neigh = g[current_vertex];
        for (int i = 0; i < neigh.size(); i++) {
            int neigh_vertex = neigh[i];
            if (h.vertices[neigh_vertex] &&  !marked[neigh_vertex]) {
                marked[neigh_vertex] = true;
                to_explore.push(neigh_vertex);
            }
        }
    }

    return subgraph(g, marked);
}



int main() {
    graph g = {
        {1,2},
        {0,2},
        {0,1},
        {4},
        {3}
    };

    // subgraph h(&g);
    subgraph h(g);

    subgraph cc1 = find_connected_comp(g, h);

    cout << cc1 << endl;

    return 0;
}
