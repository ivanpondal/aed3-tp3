#ifndef AED3_TP3_EJ2_H
#define AED3_TP3_EJ2_H

#include <unordered_map>
#include <sstream>

#include "../main.h"
#include "../exact/exact.h"

#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/structures/graph.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/utils/element_generator_int.h"

using namespace std;

class equal_complete_vs_complete: public incremental_experiment<int, adj_list_graph<int>>{
	public:
		equal_complete_vs_complete(const incremental_experiment_input<int, adj_list_graph<int>> *input):
		                           incremental_experiment(input){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		adj_list_graph<int> g1, g2;
		element_generator_int e_gen1, e_gen2;
};

class equal_tree_vs_tree: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_tree_vs_tree(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class equal_cycle_vs_cycle: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_cycle_vs_cycle(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

#endif  // AED3_TP3_EJ2_H
