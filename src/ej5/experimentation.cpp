#include "./ej5.h"
#include "../framework/structures/adj_list_graph.h"

/*
**  Exercise 5
**  Experimentation
*/

// graph<std::pair<int, int>>* solve_local_search(
//     graph<int>& g1,
//     graph<int>& g2,
//     graph<std::pair<int, int>>& start_point,
//     int neighbourhood_type,                   // 1 or 2
//     int iteration_limit = -1,                 // -1 indicates no limit
//     // int neighbourhood_limit = -1,          // discarded parameter
//     float neighbourhood_proportion = 1,       // between 0 and 1
//     bool strict_comparisons = true
// );

using namespace std;

unsigned int quality_exp_local_search_without_swap::solve_instance(graph<int> &g1, graph<int> &g2) {
	graph<pair<int, int>> *start_point = solve_greedy(g1, g2);
    solution_graph_ptr= solve_local_search(g1, g2, *start_point, 1);

	return solution_graph_ptr->m();
}

void quality_exp_local_search_without_swap::clean_solution() {
	delete solution_graph_ptr;

}



// Experiments

void run_experimentation(){
	experiment_suite quality_exp_suite;
	int repetitions_val = 50;

	quality_exp_local_search_without_swap greedy_vs_local_search_1_exp(
			greedy_solution_instances, "../exp/ej5/greedy_vs_local_search_1_exp", 0, repetitions_val);

	quality_exp_suite.add(&greedy_vs_local_search_1_exp);

	quality_exp_suite.run();
	

}
