#include "exact.h"

using namespace std;

/*
**  Cograph vs complete algorithm
*/

solution solve_cograph_vs_complete(const graph<int>& g1, const graph<int>& g2){
	if (g2.n() >= g1.n()) {
		vector<int> g1_mapping = g1.get_vertices();

		vector<int> g2_mapping(g1.n());
		iota(g2_mapping.begin(), g2_mapping.end(), 0);

		return {g1.clone(), g1_mapping, g2_mapping};
	}

	// Calculate cotree
	cotree_node* cotree = generate_cotree(g1);
	vector<info_cotree_node> vec_cotree = vectorize(cotree);

	vector<vector<subsolution>> dp(
		vec_cotree.size(),
		vector<subsolution>(g2.n() + 1)
	);

	solver_dp(dp,vec_cotree,g2.n());

	vector<int> g1_mapping = dp[vec_cotree.size() - 1][g2.n()].vertices;
	vector<int> g2_mapping(g2.n());
	iota(g2_mapping.begin(), g2_mapping.end(), 0);

	return {induced_supgraph(g1, g1_mapping), g1_mapping, g2_mapping};
}

void solver_dp(std::vector<std::vector<subsolution>> &dp,std::vector<info_cotree_node> &vec_cotree, uint g2_n){

    for (uint i = 0; i < vec_cotree.size(); i++) {
        info_cotree_node current_info = vec_cotree[i];

        for (uint j = 0; j <= g2_n; j++) {
            // si pido 0 nodos
            if (j == 0) {
                dp[i][j] = {0, vector<int>()};
            }
            else {
                // si es una hoja
                if (current_info.node->get_type() == leaf) {
                    cotree_node_leaf* current_node =
                        (cotree_node_leaf*) current_info.node;

                    // si pido 1 nodo
                    if (j == 1) {
                        dp[i][j] = {0, {current_node->get_vertex()}};
                    }
                    else {
                        dp[i][j] = {-1, vector<int>()};
                    }
                }
                else {
                    cotree_node_operation* current_node =
                        (cotree_node_operation*) current_info.node;

                    // si le pido más nodos de los que tiene el cotree
                    if (j > current_node->get_vertex_count()) {
                        dp[i][j] = {-1, vector<int>()};
                    }
                    // si pido exactamente la cantidad de nodos que tiene el cotree
                    else if (j == current_node->get_vertex_count()) {
                        uint left_vertex_count =
                            current_node->get_left_child()->get_vertex_count();
                        uint right_vertex_count =
                            current_node->get_right_child()->get_vertex_count();

                        subsolution left_subsolution =
                            dp[current_info.left_child_index][left_vertex_count];
                        subsolution right_subsolution =
                            dp[current_info.right_child_index][right_vertex_count];

                        int current_edge_count;
                        if (current_node->get_operation() == join) {
                            current_edge_count = left_subsolution.edge_count +
                                right_subsolution.edge_count +
                                left_vertex_count * right_vertex_count;
                        }
                        else {
                            current_edge_count = left_subsolution.edge_count +
                                right_subsolution.edge_count;
                        }

                        vector<int> current_vertices = left_subsolution.vertices;
                        current_vertices.insert(
                            current_vertices.end(),
                            right_subsolution.vertices.begin(),
                            right_subsolution.vertices.end()
                        );
                        dp[i][j] = {current_edge_count, current_vertices};
                    }
                    else {
                        // pruebo combinando tomando de 1 a i y de i a 1 en
                        // los hijos del co-tree
                        int best_edge_count = -1;

                        for (uint k = 0; k <= j; k++) {
                            subsolution left_subsolution =
                                dp[current_info.left_child_index][j - k];
                            subsolution right_subsolution =
                                dp[current_info.right_child_index][k];

                            int current_edge_count;
                            // si es un caso válido
                            if (left_subsolution.edge_count != -1
                                && right_subsolution.edge_count != -1)
                            {
                                if (current_node->get_operation() == join) {
                                    current_edge_count =
                                        left_subsolution.edge_count +
                                        right_subsolution.edge_count +
                                        k * (j - k);
                                }
                                else {
                                    current_edge_count =
                                        left_subsolution.edge_count +
                                        right_subsolution.edge_count;
                                }

                                if (current_edge_count > best_edge_count) {
                                    best_edge_count = current_edge_count;
                                    vector<int> current_vertices =
                                        left_subsolution.vertices;
                                    current_vertices.insert(
                                        current_vertices.end(),
                                        right_subsolution.vertices.begin(),
                                        right_subsolution.vertices.end()
                                    );
                                    dp[i][j] =
                                        {current_edge_count, current_vertices};
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

/*
**  Implementation of cographs and cotrees for Exercise 3 solver
*/

//  Subgraphs (implemented as vector of booleans)
//  ---------

subgraph::subgraph() {}

subgraph::subgraph(uint graph_size) :
    vertex_count_val(graph_size)
{
    vertices = vector<bool>(graph_size, true);
}

subgraph::subgraph(vector<int> v, uint graph_size) {
    vertex_count_val = v.size();
    vertices = vector<bool>(graph_size, false);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        vertices[*it] = true;
    }
}

subgraph::subgraph(vector<bool> v) : vertices(v) {
    vertex_count_val = 0;
    for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
        if (*it) {
            vertex_count_val++;
        }
    }
}

int subgraph::get_vertex() const {
    int res = -1;
    for (uint i = 0; i < vertices.size(); i++) {
        if (vertices[i]) {
            res = i;
            break;
        }
    }
    return res;
}

vector<int> subgraph::get_vertices() const {
    vector<int> ret;
    for (uint i = 0; i < vertices.size(); i++) {
        ret.push_back(i);
    }
    return ret;
}

uint subgraph::vertex_count() const {
    return vertex_count_val;
}

bool subgraph::contains(int vertex) const {
    return vertices[vertex];
}

void subgraph::substract(const subgraph& h) {
    for (uint i = 0; i < vertices.size(); i++) {
        if (vertices[i] && h.vertices[i]) {
            vertices[i] = false;
            vertex_count_val--;
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
        for (uint i = 0; i < neigh.size(); i++) {
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
    for (uint i = 0; i < h.vertices.size(); i++) {
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

uint cotree_node_operation::get_vertex_count() const {
    return vertex_count;
}

uint cotree_node_operation::get_edge_count() const {
    return edge_count;
}

void cotree_node_operation::set_vertex_count(uint count) {
    vertex_count = count;
}

void cotree_node_operation::set_edge_count(uint count) {
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

uint cotree_node_leaf::get_vertex_count() const {
    return 1;
}

uint cotree_node_leaf::get_edge_count() const {
    return 0;
}


cotree_node* generate_cotree(const graph<int>& g) {
    cotree_node* ret = NULL;

    if (g.n() == 1) {
        ret = new cotree_node_leaf(0);
        return ret;
    }

    graph<int>* gc = complement(g);

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

        if (cc1.vertex_count() == current_subgraph.vertex_count()) {
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
        if (cc1.vertex_count() == 1) {
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
        if (cc2.vertex_count() == 1) {
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
        int left_child_vertex_count = 1;
        int left_child_edge_count = 0;
        if (current_node->get_left_child()->get_type() == operation) {
            cotree_node_operation* left_child =
                      (cotree_node_operation*) current_node->get_left_child();
            left_child_vertex_count = left_child->get_vertex_count();
            left_child_edge_count = left_child->get_edge_count();
        }

        // Right child size
        int right_child_vertex_count = 1;
        int right_child_edge_count = 0;
        if (current_node->get_right_child()->get_type() == operation) {
            cotree_node_operation* right_child =
                      (cotree_node_operation*) current_node->get_right_child();
            right_child_vertex_count = right_child->get_vertex_count();
            right_child_edge_count = right_child->get_edge_count();
        }

        current_node->set_vertex_count(
            left_child_vertex_count + right_child_vertex_count);

        if (current_node->get_operation() == join) {
            current_node->set_edge_count(
                left_child_edge_count + right_child_edge_count +
                (left_child_vertex_count * right_child_vertex_count));
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
        int i = cotree_root->get_vertex_count() * 2 - 1;
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

graph<int>* complement(const graph<int>& g) {
    graph<int>* ret = new adj_list_graph<int>();

    for (typename vector<int>::const_iterator it1 = g.get_vertices().begin();
        it1 != g.get_vertices().end();
        it1++)
    {
        int current_node1 = *it1;
        ret->add_node(current_node1);
        for (typename vector<int>::const_iterator it2 = g.get_vertices().begin();
            it2 != g.get_vertices().end();
            it2++)
        {
            int current_node2 = *it2;
            if (current_node1 != current_node2 &&
                ! g.adjacent(current_node1, current_node2))
            {
                ret->add_edge(current_node1, current_node2);
            }
        }

    }

    return ret;
};

graph<int>* induced_supgraph(
    const graph<int>& g,
    const vector<int>& subgraph_vertices
) {
    adj_list_graph<int>* ret = new adj_list_graph<int>();
    unordered_map<int, int> mapping;

    int i = 0;
    for (typename vector<int>::const_iterator it1 = subgraph_vertices.begin();
        it1 != subgraph_vertices.end();
        it1++)
    {
        mapping.insert(make_pair(*it1, i));
        ret->add_node(i);
        i++;
    }

    for (typename vector<int>::const_iterator it1 = subgraph_vertices.begin();
        it1 != subgraph_vertices.end();
        it1++)
    {
        i = mapping[*it1];
        vector<int> neigh = g.neighbours(*it1);

        for (typename vector<int>::const_iterator it2 = neigh.begin();
            it2 != neigh.end();
            it2++)
        {
            if (mapping.find(*it2) != mapping.end()) {
                int j = mapping[*it2];
                ret->add_edge(i, j);
            }
        }

        mapping.erase(*it1);
    }

    return ret;
}
