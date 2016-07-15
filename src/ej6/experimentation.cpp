#include "./ej6.h"
#include "../framework/structures/adj_list_graph.h"

using namespace std;

/*
**  Exercise 6
**  Experimentation
*/
unsigned int quality_exp_greedy::solve_instance(graph<int> &g1, graph<int> &g2) {
    solution_graph_ptr = solve_greedy(g1, g2);
    return solution_graph_ptr->m();
}

void quality_exp_greedy::clean_solution() {
    delete solution_graph_ptr;
}


unsigned int quality_exp_local_search::solve_instance(graph<int> &g1, graph<int> &g2) {

    graph<int>* large_graph, * small_graph;

    // Local search solver assumes g1 has at most as many nodes as g2. If that
    // is not the case, we have to exchange both graphs before passing them
    // to the function, and remember this fact so that we can read correctly
    // the obtained solution

    if (g1.n() <= g2.n()) {
        small_graph = &g1;
        large_graph = &g2;
    } else {
        small_graph = &g2;
        large_graph = &g1;
    }

    graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
    h = solve_local_search(*small_graph, *large_graph, *start_point, 1, 2000, 0.01, true);

    delete start_point;

    return h->m();
}



void quality_exp_local_search::clean_solution() {
    delete h;
}


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
                                    60,                  // unsigned int tabu_list_size,
                                    2000,                  // int iteration_limit,
                                    0.01,                // float neighbourhood_proportion,
                                    true,               // bool strict_comparisons,
                                    2000,                  // int no_gain_iteration_limit,
                                    0.9,                // float edges_vs_time,
                                    0.1,                  // float time_delta,
                                    0.3);                 // float aspiration_threshold

    delete start_point;

    return solution_graph_ptr->m();
}

void quality_exp::clean_solution() {
    delete solution_graph_ptr;
}

void run_experimentation() {
    experiment_suite quality_exp_suite;
    int repetitions_val = 10;

    quality_exp_greedy known_sol_greedy_exp(
        small_known_solution_instances,
        "../exp/ej6/known_sol_greedy_exp",
        0,
        repetitions_val);

    quality_exp_local_search known_sol_local_search_exp(
        small_known_solution_instances,
        "../exp/ej6/known_sol_local_search_exp",
        0,
        repetitions_val);

    quality_exp known_sol_exp(
        small_known_solution_instances,
        "../exp/ej6/known_sol_exp",
        0,
        repetitions_val);

    // quality_exp_suite.add(&known_sol_greedy_exp);
    // quality_exp_suite.add(&known_sol_local_search_exp);
    quality_exp_suite.add(&known_sol_exp);

    quality_exp_suite.run();
}
