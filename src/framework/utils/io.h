#ifndef IO_H_
#define IO_H_

#include <vector>
#include <fstream>
#include <unordered_set>

#include "../structures/graph.h"

struct solution;

class io{
	public:
		static void read_input(std::istream &is, graph<int> &g1, graph<int> &g2);
		static void print_solution(std::ostream &os, const solution &sol);
	private:
		static void print_vector(std::ostream &os, const std::vector<int> &v);
		static void print_edges(std::ostream &os, const graph<int> *g);
};

struct solution {
	graph<int>* h;
	std::vector<int> g1_mapping;
	std::vector<int> g2_mapping;

	~solution() {
		if (h != NULL) {
			delete h;
		}
	}

	solution& operator=(const solution &s) {
		if (h != NULL) {
			delete h;
		}
		this->h = s.h->clone();
		this->g1_mapping = s.g1_mapping;
		this->g2_mapping = s.g2_mapping;
		return *this;
	}
};

#endif // IO_H_INCLUDED
