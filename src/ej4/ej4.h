#ifndef AED3_TP3_EJ4_H
#define AED3_TP3_EJ4_H

#include "../main.h"
#include "../heuristics/heuristics.h"
#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/experiments/quality_experiment.h"

/*
**  Exercise 4
*/

// Greedy algorithm without adding neighbours

class quality_exp_greedy: public quality_experiment {
	public:
		quality_exp_greedy(std::vector<std::string> instances, const std::string &output_file_name,
		                   const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* solution_graph_ptr;
};

// Greedy algorithm adding neighbours

class quality_exp_greedy_add_neighbours: public quality_experiment {
	public:
		quality_exp_greedy_add_neighbours(std::vector<std::string> instances, const std::string &output_file_name,
		                                  const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* solution_graph_ptr;
};

// Greedy algorithm complexity experiments

class inc_exp_add_nodes: public incremental_experiment<int, adj_list_graph<int>> {
	public:
		inc_exp_add_nodes(const incremental_experiment_input<int, adj_list_graph<int>> *input):
		                  incremental_experiment(input){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void clean_solution();
		graph<std::pair<int, int>>* sol;
		adj_list_graph<int> g1, g2;
		element_generator_int e_gen;
};

class inc_exp_add_tree_nodes: public incremental_experiment<int, adj_list_graph<int>> {
	public:
		inc_exp_add_tree_nodes(const incremental_experiment_input<int, adj_list_graph<int>> *input):
		                       incremental_experiment(input){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void clean_solution();
		graph<std::pair<int, int>>* sol;
		adj_list_graph<int> g1, g2;
		element_generator_int e_gen_1, e_gen_2;
};

class inc_exp_add_complete_nodes: public incremental_experiment<int, adj_list_graph<int>> {
	public:
		inc_exp_add_complete_nodes(const incremental_experiment_input<int, adj_list_graph<int>> *input):
		                           incremental_experiment(input){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void clean_solution();
		graph<std::pair<int, int>>* sol;
		adj_list_graph<int> g1, g2;
		element_generator_int e_gen_1, e_gen_2;
};
#endif  // AED3_TP3_EJ4_H
