#ifndef AED3_TP3_EJ7_H
#define AED3_TP3_EJ7_H

#include "../main.h"
#include "../heuristics/heuristics.h"
#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/experiments/quality_experiment.h"

/*
**  Exercise 7
*/

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.

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

class quality_exp_ls1: public quality_experiment {
	public:
		quality_exp_ls1(std::vector<std::string> instances, const std::string &output_file_name,
		                const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* start_point;
		graph<std::pair<int, int>>* solution_graph_ptr;
};

class quality_exp_ls2: public quality_experiment {
	public:
		quality_exp_ls2(std::vector<std::string> instances, const std::string &output_file_name,
		                const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* start_point;
		graph<std::pair<int, int>>* solution_graph_ptr;
};

class quality_exp_tabu_ls1: public quality_experiment {
	public:
		quality_exp_tabu_ls1(std::vector<std::string> instances, const std::string &output_file_name,
		                     const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* start_point;
		graph<std::pair<int, int>>* solution_graph_ptr;
};

class quality_exp_tabu_ls2: public quality_experiment {
	public:
		quality_exp_tabu_ls2(std::vector<std::string> instances, const std::string &output_file_name,
							 const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* start_point;
		graph<std::pair<int, int>>* solution_graph_ptr;
};

#endif // AED3_TP3_EJ7_H
