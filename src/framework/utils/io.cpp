#include "io.h"

void io::read_input(std::istream &is, graph<int> &g1, graph<int> &g2) {
	unsigned int n1, n2, m1, m2;

	g1.clear();
	g2.clear();

	is >> n1 >> m1 >> n2 >> m2;

	for (unsigned int i = 0; i < n1; i++) {
		g1.add_node(i);
	}
	for (unsigned int i = 0; i < n2; i++) {
		g2.add_node(i);
	}

	int vertex_1, vertex_2;
	for (unsigned int i = 0; i < m1; i++) {
		is >> vertex_1 >> vertex_2;
		g1.add_edge(vertex_1, vertex_2);
	}
	for (unsigned int i = 0; i < m2; i++) {
		is >> vertex_1 >> vertex_2;
		g2.add_edge(vertex_1, vertex_2);
	}
}

void io::print_solution(std::ostream &os, const solution &sol) {
	os << sol.h->n() << " " << sol.h->m() << std::endl;
	print_vector(os, sol.g1_mapping);
	os << std::endl;
	print_vector(os, sol.g2_mapping);
	os << std::endl;
	print_edges(os, sol.h);
}

void io::print_vector(std::ostream &os, const std::vector<int> &v) {
	bool first = true;
	for (typename std::vector<int>::const_iterator it = v.begin();
	    it != v.end();
	    it++)
	{
		if (first) {
			first = false;
			os << *it;
		}
		else {
			os << " " << *it;
		}
	}
}

void io::print_edges(std::ostream &os, const graph<int> *g) {
	std::vector<int> vertices_list = g->get_vertices();
	std::unordered_set<int> vertices;

	for (typename std::vector<int>::const_iterator it1 = vertices_list.begin();
	    it1 != vertices_list.end();
	    it1++)
	{
		vertices.insert(*it1);
	}

	for (typename std::vector<int>::const_iterator it1 = vertices_list.begin();
	    it1 != vertices_list.end();
	    it1++)
	{
		std::vector<int> neigh = g->neighbours(*it1);

		for (typename std::vector<int>::const_iterator it2 = neigh.begin();
		    it2 != neigh.end();
		    it2++)
		{
			if (vertices.find(*it2) != vertices.end()) {
				os << *it1 << " " << *it2 << std::endl;
			}
		}

		vertices.erase(*it1);
	}
}
