#ifndef MAIN_H_
#define MAIN_H_

#include <sstream>
#include <unistd.h>

#include "../mini_test.h"
#include "experiments/incremental_experiment.h"
#include "experiments/experiment_suite.h"
#include "experiments/input/incremental_experiment_input_int.h"
#include "experiments/input/incremental_experiment_input_float.h"
#include "structures/adj_list_graph.h"
#include "utils/graph_factory.h"
#include "utils/element_generator_int.h"

#define MAGIC_SEED 42

enum mode {test, instance_generation};

class adj_list_n_incremental_experiment: public incremental_experiment<int, adj_list_graph<int>>{
	public:
		adj_list_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int>> *input):
		                                  incremental_experiment(input, false){};
	private:
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
};

void adj_list_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	input->get_subject().add_node(input->get_inc_val());
}

void adj_list_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	input->get_subject().contains(-1);
}

class adj_list_c_incremental_experiment: public incremental_experiment<float, adj_list_graph<int>>{
	public:
		adj_list_c_incremental_experiment(const incremental_experiment_input<float, adj_list_graph<int>> *input):
		                                  incremental_experiment(input, false){};
	private:
		void load_instance(incremental_experiment_input<float, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<float, adj_list_graph<int>> *input);
		element_generator_int e_gen;
};

void adj_list_c_incremental_experiment::load_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
	graph_factory<int>::add_n_random_vertices(input->get_subject(), e_gen, 1, input->get_inc_val());
}

void adj_list_c_incremental_experiment::solve_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
	input->get_subject().contains(-1);
}

#endif // MAIN_H_INCLUDED
