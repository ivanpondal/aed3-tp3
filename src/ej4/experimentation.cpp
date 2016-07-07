#include "ej4.h"

using namespace std;

// Experiment definitions

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

// Experiments

void run_experimentation(){
	experiment_suite quality_exp_suite;
	int repetitions_val = 50;

	quality_exp_greedy known_sol_greedy_exp(
			known_solution_instances, "../exp/ej4/known_sol_greedy_exp", 0, repetitions_val);
	quality_exp_greedy unknown_sol_greedy_exp(
			unknown_solution_instances, "../exp/ej4/unknown_sol_greedy_exp", 0, repetitions_val);

	quality_exp_greedy_add_neighbours known_sol_greedy_add_neighbours_exp(
			known_solution_instances, "../exp/ej4/known_sol_greedy_add_neighbours_exp", 0, repetitions_val);
	quality_exp_greedy_add_neighbours unknown_sol_greedy_add_neighbours_exp(
			unknown_solution_instances, "../exp/ej4/unknown_sol_greedy_add_neighbours_exp", 0, repetitions_val);

	quality_exp_suite.add(&known_sol_greedy_exp);
	quality_exp_suite.add(&unknown_sol_greedy_exp);
	quality_exp_suite.add(&known_sol_greedy_add_neighbours_exp);
	quality_exp_suite.add(&unknown_sol_greedy_add_neighbours_exp);

	quality_exp_suite.run();
}
