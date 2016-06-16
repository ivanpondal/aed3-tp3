#include "ej3.h"

#include "../framework/structures/adj_list_graph.h"

using namespace std;

/*
**  Implementation of cographs and cotrees for Exercise 3 solver
*/

//  Subgraphs (implemented as vector of booleans)
//  ---------

subgraph::subgraph() {}

subgraph::subgraph(int graph_size) :
    node_count_val(graph_size)
{
    vertices = vector<bool>(graph_size, true);
}

subgraph::subgraph(vector<int> v, int graph_size) {
    node_count_val = v.size();
    vertices = vector<bool>(graph_size, false);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        vertices[*it] = true;
    }
}

subgraph::subgraph(vector<bool> v) : vertices(v) {
    node_count_val = 0;
    for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
        if (*it) {
            node_count_val++;
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

vector<int> subgraph::get_vertices() const {
    vector<int> ret;
    for (int i = 0; i < vertices.size(); i++) {
        ret.push_back(i);
    }
    return ret;
}

int subgraph::node_count() const {
    return node_count_val;
}

bool subgraph::contains(int vertex) const {
    return vertices[vertex];
}

void subgraph::substract(const subgraph& h) {
    for (uint i; i < vertices.size(); i++) {
        if (vertices[i] && h.vertices[i]) {
            vertices[i] = false;
            node_count_val--;
        }
    }
}

subgraph subgraph::find_connected_comp(const graph<int>& g) const {
    int initial_vertex = get_vertex();

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
            if (vertices[neigh_vertex] && !marked[neigh_vertex]) {
                marked[neigh_vertex] = true;
                to_explore.push(neigh_vertex);
            }
        }
    }

    return subgraph(marked);
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


//  Cotrees and cotree nodes
//  ------------------------

cotree_node::cotree_node() :
    right_child(NULL),
    left_child(NULL)
{}

cotree_node::~cotree_node() {
    if (right_child != NULL) {
        delete right_child;
    }
    if (left_child != NULL) {
        delete left_child;
    }
}

cotree_node* cotree_node::get_right_child() const {
    return right_child;
}
cotree_node* cotree_node::get_left_child() const {
    return left_child;
}

void cotree_node::set_right_child(cotree_node* node) {
    right_child = node;
}
void cotree_node::set_left_child(cotree_node* node) {
    left_child = node;
}

ostream& operator<<(ostream& os, cotree_node& n) {
    if (n.get_type() == leaf) {
        cotree_node_leaf& n2 = (cotree_node_leaf&) n;
        os << n2.get_vertex();
    }
    else if (n.get_type() == operation) {
        cotree_node_operation& n2 = (cotree_node_operation&) n;
        if (n2.get_operation() == join) {
            os << "[" << *(n2.get_left_child()) << "] × ["
               << *(n2.get_right_child()) << "]";
        } else if (n2.get_operation() == disj_union) {
            os << "[" << *(n2.get_left_child()) << "] ∪ ["
               << *(n2.get_right_child()) << "]";
        }
    }
    return os;
}

cotree_node_operation::cotree_node_operation(cotree_operation op) :
    op(op)
{}

cotree_node_operation::cotree_node_operation(
    cotree_operation op,
    cotree_node* lc,
    cotree_node* rc
) :
    op(op)
{
    set_left_child(lc);
    set_right_child(rc);
}

cotree_node_type cotree_node_operation::get_type() const {
    return operation;
}

cotree_operation cotree_node_operation::get_operation() const {
    return op;
}

int cotree_node_operation::get_node_count() const {
    return node_count;
}

int cotree_node_operation::get_edge_count() const {
    return edge_count;
}

void cotree_node_operation::set_node_count(int count) {
    node_count = count;
}

void cotree_node_operation::set_edge_count(int count) {
    edge_count = count;
}


cotree_node_leaf::cotree_node_leaf(int v) :
    vertex(v)
{}

cotree_node_type cotree_node_leaf::get_type() const {
    return leaf;
}

int cotree_node_leaf::get_vertex() const {
    return vertex;
}


cotree_node* generate_cotree(const graph<int>& g) {
    cotree_node* ret;

    if (g.n() == 1) {
        ret = new cotree_node_leaf(0);
        return ret;
    }

    graph<int>* gc = g.complement();

    enum direction {left, right, none};
    struct pending_node {
        subgraph sg;
        cotree_node_operation* parent;
        direction child_type;
    };

    pending_node start = {subgraph(g.n()), NULL, none};
    stack<pending_node> to_expand;
    stack<cotree_node_operation*> to_compute_size;
    to_expand.push(start);

    while (! to_expand.empty()) {
        subgraph current_subgraph = to_expand.top().sg;
        cotree_node_operation* current_parent = to_expand.top().parent;
        direction current_child_type = to_expand.top().child_type;
        to_expand.pop();

        cotree_operation op;
        subgraph cc1 = current_subgraph.find_connected_comp(g);

        if (cc1.node_count() == current_subgraph.node_count()) {
            cc1 = current_subgraph.find_connected_comp(*gc);
            op = join;
        }
        else {
            op = disj_union;
        }

        subgraph cc2 = current_subgraph;
        cc2.substract(cc1);

        cotree_node_operation* new_node = new cotree_node_operation(op);
        to_compute_size.push(new_node);

        if (current_parent == NULL) {
            ret = new_node;
        }
        else {
            if (current_child_type == left) {
                current_parent->set_left_child(new_node);
            }
            else if (current_child_type == right) {
                current_parent->set_right_child(new_node);
            }
        }

        // Left child
        if (cc1.node_count() == 1) {
            // If it is a leaf
            cotree_node* cc1_node = new cotree_node_leaf(cc1.get_vertex());
            new_node->set_left_child(cc1_node);
        }
        else {
            // If it is an operation
            pending_node cc1_node = {cc1, new_node, left};
            to_expand.push(cc1_node);
        }

        // Right child
        if (cc2.node_count() == 1) {
            // If it is a leaf
            cotree_node* cc2_node = new cotree_node_leaf(cc2.get_vertex());
            new_node->set_right_child(cc2_node);
        }
        else {
            // If it is an operation
            pending_node cc2_node = {cc2, new_node, right};
            to_expand.push(cc2_node);
        }
    }

    delete gc;

    // Counting nodes and edges
    cotree_node_operation* current_node;
    while (! to_compute_size.empty()) {
        current_node = to_compute_size.top();
        to_compute_size.pop();

        // Left child size
        int left_child_node_count = 1;
        int left_child_edge_count = 0;
        if (current_node->get_left_child()->get_type() == operation) {
            cotree_node_operation* left_child =
                      (cotree_node_operation*) current_node->get_left_child();
            left_child_node_count = left_child->get_node_count();
            left_child_edge_count = left_child->get_edge_count();
        }

        // Right child size
        int right_child_node_count = 1;
        int right_child_edge_count = 0;
        if (current_node->get_right_child()->get_type() == operation) {
            cotree_node_operation* right_child =
                      (cotree_node_operation*) current_node->get_right_child();
            right_child_node_count = right_child->get_node_count();
            right_child_edge_count = right_child->get_edge_count();
        }

        current_node->set_node_count(
            left_child_node_count + right_child_node_count);

        if (current_node->get_operation() == join) {
            current_node->set_edge_count(
                left_child_edge_count + right_child_edge_count +
                (left_child_node_count * right_child_node_count));
        }
        else if (current_node->get_operation() == disj_union) {
            current_node->set_edge_count(
                left_child_edge_count + right_child_edge_count);
        }
    }

    return ret;
}

vector<info_cotree_node> vectorize(cotree_node* cotree) {
    vector<info_cotree_node> ret;
    if (cotree->get_type() == leaf) {
        ret = {{cotree, -1, -1}};
    } else {
        cotree_node_operation* cotree_root = (cotree_node_operation*) cotree;
        int i = cotree_root->get_node_count() * 2 - 1;
        ret = vector<info_cotree_node>(i);

        enum direction {left, right, none};
        struct pending_node {
            cotree_node* addr;
            int parent_index;
            direction child_type;
        };

        stack<pending_node> to_explore;
        to_explore.push({cotree, -1, none});

        while (! to_explore.empty()) {
            cotree_node* current_node = to_explore.top().addr;
            int current_parent_index = to_explore.top().parent_index;
            direction current_child_type = to_explore.top().child_type;
            to_explore.pop();
            i--;

            if (current_node->get_type() == leaf) {
                ret[i] = {current_node, -1, -1};
            } else {
                to_explore.push({current_node->get_left_child(), i, left});
                to_explore.push({current_node->get_right_child(), i, right});
                ret[i] = {current_node, -1, -1};
            }

            if (current_parent_index != -1) {
                if (current_child_type == left) {
                    ret[current_parent_index].left_child_index = i;
                } else if (current_child_type == right) {
                    ret[current_parent_index].right_child_index = i;
                }
            }
        }
    }

    return ret;
}

// int main() {
//     adj_list_graph<int>* g = new adj_list_graph<int>();
//     g->add_node(0);
//     g->add_node(1);
//     g->add_node(2);
//     g->add_node(3);
//     g->add_node(4);
//     g->add_node(5);
//     g->add_edge(0, 1);
//     g->add_edge(0, 2);
//     g->add_edge(1, 2);
//     g->add_edge(4, 5);

//     cotree_node* cot = generate_cotree(*g);
//     cout << (*cot) << endl;

//     vectorize(cot);

//     delete cot;
//     delete g;

//     return 0;
// }
