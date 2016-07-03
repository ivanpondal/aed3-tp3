#ifndef EXACT_H
#define EXACT_H

#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../main.h"

/*
**  Exact algorithms
*/

graph<std::pair<int, int> >* solve_backtracking(graph<int> *g1, graph<int> *g2);

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

#endif	// EXACT_H
