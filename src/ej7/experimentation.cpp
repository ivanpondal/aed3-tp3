#include "./ej7.h"

/*
**  Exercise 7
**  Experimentation
*/

using namespace std;

unsigned int quality_exp_greedy::solve_instance(graph<int> &g1, graph<int> &g2) {
	solution_graph_ptr = solve_greedy(g1, g2);
	return solution_graph_ptr->m();
}

void quality_exp_greedy::clean_solution() {
	delete solution_graph_ptr;
}

unsigned int quality_exp_ls1::solve_instance(graph<int> &g1, graph<int> &g2) {
	start_point = solve_greedy(g1, g2);

	solution_graph_ptr = solve_local_search(g1, g2, *start_point, 1, 150, .10 );
	return solution_graph_ptr->m();
}

void quality_exp_ls1::clean_solution() {
	delete solution_graph_ptr;
	delete start_point;
}

unsigned int quality_exp_ls2::solve_instance(graph<int> &g1, graph<int> &g2) {
	start_point = solve_greedy(g1, g2);

	solution_graph_ptr = solve_local_search(g1, g2, *start_point, 2, 150, .10 );
	return solution_graph_ptr->m();
}

void quality_exp_ls2::clean_solution() {
	delete solution_graph_ptr;
	delete start_point;
}

unsigned int quality_exp_tabu_ls1::solve_instance(graph<int> &g1, graph<int> &g2) {
	start_point = solve_greedy(g1, g2);

	solution_graph_ptr = solve_tabu(g1, g2, *start_point, 1, 60, 2000, 0.01, true, 100, 0.5, 0.1, 0.3);
	return solution_graph_ptr->m();
}

void quality_exp_tabu_ls1::clean_solution() {
	delete solution_graph_ptr;
}

unsigned int quality_exp_tabu_ls2::solve_instance(graph<int> &g1, graph<int> &g2) {
	start_point = solve_greedy(g1, g2);

	solution_graph_ptr = solve_tabu(g1, g2, *start_point, 1, 60, 2000, 0.01, true, 2000, 0.5, 0.1, 0.3);
	return solution_graph_ptr->m();
}

void quality_exp_tabu_ls2::clean_solution() {
	delete solution_graph_ptr;
}
void run_experimentation() {
	experiment_suite exp_suite;
	int repetitions_val = 10;

	quality_exp_greedy new_known_sol_greedy_exp(
			new_known_solution_instances, "../exp/ej7/new_known_sol_greedy_exp", 0, repetitions_val);
	quality_exp_ls1 new_known_sol_ls1_exp(
			new_known_solution_instances, "../exp/ej7/new_known_sol_ls1_exp", 0, repetitions_val);
	quality_exp_ls2 new_known_sol_ls2_exp(
			new_known_solution_instances, "../exp/ej7/new_known_sol_ls2_exp", 0, repetitions_val);
	quality_exp_tabu_ls1 new_known_sol_tabu_ls1_exp(
			new_known_solution_instances, "../exp/ej7/new_known_sol_tabu_ls1_exp", 0, repetitions_val);
	quality_exp_tabu_ls2 new_known_sol_tabu_ls2_exp(
			new_known_solution_instances, "../exp/ej7/new_known_sol_tabu_ls2_exp", 0, repetitions_val);

	exp_suite.add(&new_known_sol_greedy_exp);
	exp_suite.add(&new_known_sol_ls1_exp);
	exp_suite.add(&new_known_sol_ls2_exp);
	exp_suite.add(&new_known_sol_tabu_ls1_exp);
	exp_suite.add(&new_known_sol_tabu_ls2_exp);
	exp_suite.run();
}
