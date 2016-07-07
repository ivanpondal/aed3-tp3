#ifndef AED3_TP3_EJ4_H
#define AED3_TP3_EJ4_H

#include "../main.h"
#include "../heuristics/heuristics.h"
#include "../framework/experiments/experiment_suite.h"
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

#endif  // AED3_TP3_EJ4_H
