#ifndef EJ4_H
#define EJ4_H

#include "../main.h"

#include <queue>
#include <unordered_set>
#include <unordered_map>

std::ostream &operator<<(std::ostream& output, const std::pair<int, int>& p);

struct node_degree_pair_compare{
	bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2){
		return p1.second < p2.second;
	}
};

graph< std::pair<int, int>> *solve(graph<int> &g1, graph<int> &g2, bool add_neighbours = false);

#endif // EJ4_H
