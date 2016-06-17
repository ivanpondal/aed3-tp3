#ifndef TEST_H_
#define TEST_H_

#include <sstream>

#include "../mini_test.h"
#include "experiments/incremental_experiment.h"
#include "experiments/experiment_suite.h"
#include "experiments/input/incremental_experiment_input_int.h"
#include "structures/adj_list_graph.h"
#include "utils/graph_factory_int.h"

class adj_list_n_incremental_experiment: public incremental_experiment<int, adj_list_graph<int>>{
	public:
		adj_list_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int>> *input): incremental_experiment(input){};
	private:
		const char *get_experiment_name() const;
		void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
		void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
};

const char *adj_list_n_incremental_experiment::get_experiment_name() const{
	return "adj_list_n";
}

void adj_list_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	input->get_subject().add_node(input->get_inc_val());
}

void adj_list_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	input->get_subject().contains(-1);
}

#endif // TEST_H_INCLUDED
