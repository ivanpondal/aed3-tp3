#include "./ej6.h"
#include "../framework/structures/adj_list_graph.h"

using namespace std;

/*
**  Exercise 6
**  Experimentation
*/

unsigned int quality_exp::solve_instance(graph<int> &g1, graph<int> &g2) {
    graph<int>* large_graph, * small_graph;

    if (g1.n() <= g2.n()) {
        small_graph = &g1;
        large_graph = &g2;
    }
    else {
        small_graph = &g2;
        large_graph = &g1;
    }

    graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
    solution_graph_ptr = solve_tabu(*small_graph,       // graph<int>& g1,
                                    *large_graph,       // graph<int>& g2,
                                    *start_point,       // graph<pair<int, int>>& start_point,
                                    1,                  // int neighbourhood_type,
                                    20,                  // unsigned int tabu_list_size,
                                    1000,                  // int iteration_limit,
                                    0.01,                // float neighbourhood_proportion,
                                    true,               // bool strict_comparisons,
                                    20,                  // int no_gain_iteration_limit,
                                    0.5,                // float edges_vs_time,
                                    0.1,                  // float time_delta,
                                    1.0);                 // float aspiration_threshold
    return solution_graph_ptr->m();
}

void quality_exp::clean_solution() {
    delete solution_graph_ptr;
}

void run_experimentation() {
    experiment_suite quality_exp_suite;
    int repetitions_val = 10;

    quality_exp known_sol_exp(
            small_known_solution_instances, "../exp/ej6/small_known_sol_exp", 0, repetitions_val);

    quality_exp_suite.add(&known_sol_exp);

    quality_exp_suite.run();
}
