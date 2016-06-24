#include "./ej2.h"

void mcs_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	graph_factory<int>::add_n_random_vertices(g1, e_gen1, input->get_delta(), 0.5f);
	graph_factory<int>::add_n_random_vertices(g2, e_gen2, input->get_delta(), 0.5f);
}

void mcs_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
	mcs(&g1, &g2);
}

void run_experimentation() {
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> exp1_input(1, 10, 10, 20, 4, adj_list_graph<int>(), "ej2_prune");

	mcs_incremental_experiment exp1 = mcs_incremental_experiment(&exp1_input);

	experiment_suite exp_suite;

	exp_suite.add(&exp1);

	exp_suite.run();
}