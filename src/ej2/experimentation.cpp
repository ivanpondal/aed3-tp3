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
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void equal_tree_vs_tree::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_tree_vertices(g1, e_gen1, input->get_delta());
    graph_factory<int>::add_n_tree_vertices(g2, e_gen2, input->get_delta());
}

void equal_tree_vs_tree::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void equal_cycle_vs_cycle::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    g1 = graph_factory<int>::cycle_graph(e_gen1, input->get_inc_val());
    g2 = graph_factory<int>::cycle_graph(e_gen2, input->get_inc_val());
}

void equal_cycle_vs_cycle::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void equal_complete_bipartite_vs_complete_bipartite::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    int n = input->get_inc_val() / 2;
    int k = input->get_inc_val() - n;
    g1 = graph_factory<int>::random_bipartite_graph(e_gen1, n, k, 1.0f);
    g2 = graph_factory<int>::random_bipartite_graph(e_gen2, n, k, 1.0f);
}

void equal_complete_bipartite_vs_complete_bipartite::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void lineal_complete_vs_complete::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_vertices_and_all_edges(
        g1, e_gen1, input->get_delta());
    graph_factory<int>::add_n_vertices_and_all_edges(
        g2, e_gen2, SLOPE_VALUE * input->get_delta());
}

void lineal_complete_vs_complete::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void lineal_tree_vs_tree::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_tree_vertices(g1, e_gen1, input->get_delta());
    graph_factory<int>::add_n_tree_vertices(g2, e_gen2, SLOPE_VALUE * input->get_delta());
}

void lineal_tree_vs_tree::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void lineal_cycle_vs_cycle::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    g1 = graph_factory<int>::cycle_graph(e_gen1, input->get_inc_val());
    g2 = graph_factory<int>::cycle_graph(e_gen2, SLOPE_VALUE * input->get_inc_val());
}

void lineal_cycle_vs_cycle::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void lineal_complete_bipartite_vs_complete_bipartite::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    int n = input->get_inc_val() / 2;
    int k = input->get_inc_val() - n;
    g1 = graph_factory<int>::random_bipartite_graph(e_gen1, n, k, 1.0f);
    g2 = graph_factory<int>::random_bipartite_graph(e_gen2,
        input->get_inc_val(), input->get_inc_val(), 1.0f);
}

void lineal_complete_bipartite_vs_complete_bipartite::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void fixed_complete_vs_complete::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_vertices_and_all_edges(
        g1, e_gen1, input->get_delta());
}

void fixed_complete_vs_complete::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void fixed_tree_vs_tree::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    graph_factory<int>::add_n_tree_vertices(g1, e_gen1, input->get_delta());
}

void fixed_tree_vs_tree::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void fixed_cycle_vs_cycle::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    g1 = graph_factory<int>::cycle_graph(e_gen1, input->get_inc_val());
}

void fixed_cycle_vs_cycle::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void fixed_complete_bipartite_vs_complete_bipartite::load_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    int n = input->get_inc_val() / 2;
    int k = input->get_inc_val() - n;
    g1 = graph_factory<int>::random_bipartite_graph(e_gen1, n, k, 1.0f);
}

void fixed_complete_bipartite_vs_complete_bipartite::solve_instance(
    incremental_experiment_input<int, adj_list_graph<int>> *input) {
    cout << "g1 " << g1.n() << "\tg2 " << g2.n() << endl;
    solve_backtracking(&g1, &g2);
}

void run_experimentation() {

    experiment_suite exp_suite;

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

    incremental_experiment_input_int< adj_list_graph<int>> equal_tree_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_tree_vs_tree");
    equal_tree_vs_tree equal_tree = equal_tree_vs_tree(&equal_tree_input);

    incremental_experiment_input_int< adj_list_graph<int>> equal_cycle_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_cycle_vs_cycle");
    equal_cycle_vs_cycle equal_cycle = equal_cycle_vs_cycle(&equal_cycle_input);

    incremental_experiment_input_int< adj_list_graph<int>> equal_bipartite_input(
        1,
        7,
        0,
        3,
        7,
        adj_list_graph<int>(),
        "../exp/ej2/equal_complete_bipartite_vs_complete_bipartite");
    equal_complete_bipartite_vs_complete_bipartite equal_bipartite =
        equal_complete_bipartite_vs_complete_bipartite(&equal_bipartite_input);

    incremental_experiment_input_int< adj_list_graph<int>> lineal_complete_input(
        1,
        5,
        1,
        4,
        5,
        adj_list_graph<int>(),
        "../exp/ej2/lineal_complete_vs_complete");
    lineal_complete_vs_complete lineal_complete = lineal_complete_vs_complete(
        &lineal_complete_input);

    incremental_experiment_input_int< adj_list_graph<int>> lineal_tree_input(
        1,
        5,
        1,
        4,
        5,
        adj_list_graph<int>(),
        "../exp/ej2/lineal_tree_vs_tree");
    lineal_tree_vs_tree lineal_tree = lineal_tree_vs_tree(&lineal_tree_input);

    incremental_experiment_input_int< adj_list_graph<int>> lineal_cycle_input(
        1,
        5,
        1,
        4,
        5,
        adj_list_graph<int>(),
        "../exp/ej2/lineal_cycle_vs_cycle");
    lineal_cycle_vs_cycle lineal_cycle = lineal_cycle_vs_cycle(&lineal_cycle_input);

    incremental_experiment_input_int< adj_list_graph<int>> lineal_bipartite_input(
        1,
        5,
        1,
        4,
        5,
        adj_list_graph<int>(),
        "../exp/ej2/lineal_complete_bipartite_vs_complete_bipartite");
    lineal_complete_bipartite_vs_complete_bipartite lineal_bipartite =
        lineal_complete_bipartite_vs_complete_bipartite(&lineal_bipartite_input);

    incremental_experiment_input_int< adj_list_graph<int>> fixed_complete_input(
        FIXED_VALUE,
        13,
        1,
        3,
        13 - FIXED_VALUE,
        adj_list_graph<int>(),
        "../exp/ej2/fixed_complete_vs_complete");
    fixed_complete_vs_complete fixed_complete = fixed_complete_vs_complete(
        &fixed_complete_input);

    incremental_experiment_input_int< adj_list_graph<int>> fixed_tree_input(
        FIXED_VALUE,
        13,
        1,
        3,
        13 - FIXED_VALUE,
        adj_list_graph<int>(),
        "../exp/ej2/fixed_tree_vs_tree");
    fixed_tree_vs_tree fixed_tree = fixed_tree_vs_tree(&fixed_tree_input);

    incremental_experiment_input_int< adj_list_graph<int>> fixed_cycle_input(
        FIXED_VALUE,
        13,
        2,
        5,
        13 - FIXED_VALUE,
        adj_list_graph<int>(),
        "../exp/ej2/fixed_cycle_vs_cycle");
    fixed_cycle_vs_cycle fixed_cycle = fixed_cycle_vs_cycle(&fixed_cycle_input);

    incremental_experiment_input_int< adj_list_graph<int>> fixed_bipartite_input(
        FIXED_VALUE,
        13,
        2,
        5,
        13 - FIXED_VALUE,
        adj_list_graph<int>(),
        "../exp/ej2/fixed_complete_bipartite_vs_complete_bipartite");
    fixed_complete_bipartite_vs_complete_bipartite fixed_bipartite =
        fixed_complete_bipartite_vs_complete_bipartite(&fixed_bipartite_input);

    // exp_suite.add(&equal_complete);
    // exp_suite.add(&equal_tree);
    // exp_suite.add(&equal_cycle);
    // exp_suite.add(&equal_bipartite);

    // exp_suite.add(&lineal_complete);
    // exp_suite.add(&lineal_tree);
    // exp_suite.add(&lineal_cycle);
    // exp_suite.add(&lineal_bipartite);

    // exp_suite.add(&fixed_complete);
    // exp_suite.add(&fixed_tree);
    exp_suite.add(&fixed_cycle);
    exp_suite.add(&fixed_bipartite);

    exp_suite.run();
}
