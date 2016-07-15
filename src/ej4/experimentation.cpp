#include "ej4.h"

using namespace std;

// Experiment definitions

// Quality

unsigned int quality_exp_greedy::solve_instance(graph<int> &g1, graph<int> &g2) {
	solution_graph_ptr = solve_greedy(g1, g2);
	return solution_graph_ptr->m();
}

void quality_exp_greedy::clean_solution() {
	delete solution_graph_ptr;
}

unsigned int quality_exp_greedy_add_neighbours::solve_instance(graph<int> &g1, graph<int> &g2) {
	solution_graph_ptr = solve_greedy(g1, g2, true);
	return solution_graph_ptr->m();
}

void quality_exp_greedy_add_neighbours::clean_solution() {
	delete solution_graph_ptr;
}

// Complexity

void inc_exp_add_nodes::load_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	int new_element;
	for (int i = 0; i < input->get_delta(); i++) {
		new_element = e_gen.generate(g1);
		g1.add_node(new_element);
		g2.add_node(new_element);
	}
}

void inc_exp_add_nodes::solve_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	sol = solve_greedy(g1, g2);
}

void inc_exp_add_nodes::clean_solution() {
	delete sol;
}

void inc_exp_add_tree_nodes::load_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	graph_factory<int>::add_n_tree_vertices(g1, e_gen_1, input->get_delta());
	graph_factory<int>::add_n_tree_vertices(g2, e_gen_2, input->get_delta());
}

void inc_exp_add_tree_nodes::solve_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	sol = solve_greedy(g1, g2);
}

void inc_exp_add_tree_nodes::clean_solution() {
	delete sol;
}

void inc_exp_add_complete_nodes::load_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	graph_factory<int>::add_n_vertices_and_all_edges(g1, e_gen_1, input->get_delta());
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen_2, input->get_delta());
}

void inc_exp_add_complete_nodes::solve_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input
) {
	sol = solve_greedy(g1, g2);
}

void inc_exp_add_complete_nodes::clean_solution() {
	delete sol;
}

// Experiments

void run_experimentation(){
	experiment_suite exp_suite;
	int repetitions_val = 50;

	// Quality

	quality_exp_greedy known_sol_greedy_exp(
			known_solution_instances, "../exp/ej4/known_sol_greedy_exp", 0, repetitions_val);
	quality_exp_greedy unknown_sol_greedy_exp(
			unknown_solution_instances, "../exp/ej4/unknown_sol_greedy_exp", 0, repetitions_val);

	quality_exp_greedy_add_neighbours known_sol_greedy_add_neighbours_exp(
			known_solution_instances, "../exp/ej4/known_sol_greedy_add_neighbours_exp", 0, repetitions_val);
	quality_exp_greedy_add_neighbours unknown_sol_greedy_add_neighbours_exp(
			unknown_solution_instances, "../exp/ej4/unknown_sol_greedy_add_neighbours_exp", 0, repetitions_val);

	// Complexity

	incremental_experiment_input_int< adj_list_graph<int>> input_add_nodes_exp(
		1, 30000, 0, 20, 250, adj_list_graph<int>(), "../exp/ej4/add_nodes_exp"
	);

	inc_exp_add_nodes add_nodes_exp(&input_add_nodes_exp);

	incremental_experiment_input_int< adj_list_graph<int>> input_add_tree_nodes_exp(
		1, 55000, 0, 30, 100, adj_list_graph<int>(), "../exp/ej4/add_tree_nodes_exp"
	);

	inc_exp_add_tree_nodes add_tree_nodes_exp(&input_add_tree_nodes_exp);

	incremental_experiment_input_int< adj_list_graph<int>> input_add_complete_nodes_exp(
		1, 1000, 0, 30, 100, adj_list_graph<int>(), "../exp/ej4/add_complete_nodes_exp"
	);

	inc_exp_add_complete_nodes add_complete_nodes_exp(&input_add_complete_nodes_exp);

	exp_suite.add(&known_sol_greedy_exp);
	exp_suite.add(&unknown_sol_greedy_exp);
	exp_suite.add(&known_sol_greedy_add_neighbours_exp);
	exp_suite.add(&unknown_sol_greedy_add_neighbours_exp);

	exp_suite.add(&add_nodes_exp);
	exp_suite.add(&add_tree_nodes_exp);
	exp_suite.add(&add_complete_nodes_exp);

	exp_suite.run();
}
