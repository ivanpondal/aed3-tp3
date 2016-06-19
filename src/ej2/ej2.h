#ifndef SRC_EJ2_H
#define SRC_EJ2_H

#include <unordered_map>

using namespace std;

#include <sstream>

#include "../mini_test.h"
#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/structures/graph.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/utils/element_generator_int.h"

class adj_list_n_incremental_experiment: public incremental_experiment<int, adj_list_graph<int>>{
	public:
		adj_list_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int>> *input): incremental_experiment(input){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		adj_list_graph<int> g1, g2;
};

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

graph<int>* mcs(
        graph<int> *g1,
        graph<int> *g2
);

#endif //SRC_EJ2_H
