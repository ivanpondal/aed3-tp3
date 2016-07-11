#include "./ej2.h"

void equal_complete_vs_complete::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
	graph_factory<int>::add_n_vertices_and_all_edges(
        g1, e_gen1, input->get_delta());
	graph_factory<int>::add_n_vertices_and_all_edges(
        g2, e_gen2, input->get_delta());
}

void equal_complete_vs_complete::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << g1.n() << endl;
    solve_backtracking(&g1, &g2);
}

void equal_tree_vs_tree::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_tree_vertices(g1, e_gen1, input->get_delta());
    graph_factory<int>::add_n_tree_vertices(g2, e_gen2, input->get_delta());
}

void equal_tree_vs_tree::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << g1.n() << endl;
    solve_backtracking(&g1, &g2);
}

void equal_cycle_vs_cycle::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    e_gen1.reset();
    e_gen2.reset();
    g1 = graph_factory<int>::cycle_graph(e_gen1, input->get_delta());
    g2 = graph_factory<int>::cycle_graph(e_gen2, input->get_delta());
}

void equal_cycle_vs_cycle::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << g1.n() << endl;
    solve_backtracking(&g1, &g2);
}

void run_experimentation() {
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> equal_complete_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_complete_vs_complete");
	equal_complete_vs_complete equal_complete = equal_complete_vs_complete(
        &equal_complete_input);
	experiment_suite exp_suite;
	exp_suite.add(&equal_complete);

    incremental_experiment_input_int< adj_list_graph<int>> equal_tree_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_tree_vs_tree");
    equal_tree_vs_tree equal_tree = equal_tree_vs_tree(&equal_tree_input);
    experiment_suite exp_suite;
    exp_suite.add(&equal_tree);

    // ESTE ES EL QUE ESTA JODIENDO, NO AUMENTA LA CANTIDAD DE NODOS
    incremental_experiment_input_int< adj_list_graph<int>> equal_cycle_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_cycle_vs_cycle");
    equal_cycle_vs_cycle equal_cycle = equal_cycle_vs_cycle(&equal_cycle_input);
    experiment_suite exp_suite;
exp_suite.add(&equal_cycle);

	exp_suite.run();
}
