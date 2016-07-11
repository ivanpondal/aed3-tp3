#ifndef AED3_TP3_EJ5_H
#define AED3_TP3_EJ5_H

#include "../main.h"
#include "../heuristics/heuristics.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/quality_experiment.h"

/*
**  Exercise 5
*/

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.

#endif  // AED3_TP3_EJ5_H

// Local search , neighbourhood without swap

class quality_exp_local_search_without_swap: public quality_experiment {
	public:
		quality_exp_local_search_without_swap(std::vector<std::string> instances, const std::string &output_file_name,
		                   const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* solution_graph_ptr;
};
