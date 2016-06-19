
#include "../main.h"
#include "./ej3.h"


/*
**  Exercise 3
**  Experimentation
*/
using namespace std;

void cograph_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    
}

void cograph_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    run_solver(g,input->get_subject());
}

void complete_graph_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    int n = input->get_inc_val();
    int step = n - g.n(); 
    graph_factory<int>::add_n_vertices_and_all_edges(g,e_gen,step);
}

void complete_graph_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    run_solver(input->get_subject(),g);
}

void complete_graph_and_cograph_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    int n = input->get_inc_val();
    // cout << "n de g_1 :" << g_1.n() << endl;
    // cout << "new n de g_1 :" << n << endl;
    g_1 = graph_factory<int>::random_co_graph(e_gen, n);
    e_gen.reset();
    int n_k = n/2;
    int step = n_k - g_2.n(); 
    // cout << "new n de g_2 :" << n_k << endl;
    // cout << "n de g_2 :" << g_2.n() << endl;
    graph_factory<int>::add_n_vertices_and_all_edges(g_2,e_gen,step);
}

void complete_graph_and_cograph_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    run_solver(g_1,g_2);
}

void run_experimentation() {
    element_generator_int e_gen;
    adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, 100);
    // cout << "co_g: " << endl;
    // cout << co_g << endl;

    // cotree_node* co_tree_node = generate_cotree(co_g);
    // cout << "cotree : " <<  endl <<*co_tree_node << endl;

    adj_list_graph<int> k_n;
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(k_n,e_gen,100);
    // cout << endl << "k_n : " <<  endl <<  k_n << endl;

    // load min, load max, discard, repetitions, samples and initial subject values

    incremental_experiment_input_int< adj_list_graph<int>> exp1_input(100, 200, 30, 50, 50, k_n, "../exp/ej3/cograph_incremental_nodes");
 
    cograph_n_incremental_experiment exp_1 = cograph_n_incremental_experiment(&exp1_input);

    experiment_suite exp_suite;

    //  exp_suite.add(&exp_1);


    incremental_experiment_input_int< adj_list_graph<int>> exp2_input(1, 100, 30, 50, 50, co_g, "../exp/ej3/complete_graph_incremental_nodes");
 
    complete_graph_n_incremental_experiment exp_2 = complete_graph_n_incremental_experiment(&exp2_input);

    //exp_suite.add(&exp_2);


    incremental_experiment_input_int< adj_list_graph<int>> exp3_input(1, 100, 30, 50, 50, adj_list_graph<int>(), "../exp/ej3/complete_graph_and_cograph_incremental_nodes");
 
    complete_graph_and_cograph_n_incremental_experiment exp_3 = complete_graph_and_cograph_n_incremental_experiment(&exp3_input);

    exp_suite.add(&exp_3);

    exp_suite.run();

}
