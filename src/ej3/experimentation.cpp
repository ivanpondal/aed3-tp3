
#include "../main.h"
#include "./ej3.h"


/*
**  Exercise 3
**  Experimentation
*/
using namespace std;


// Incremental cograph

void cograph_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
}

void cograph_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    run_solver(g,input->get_subject());
}

// Incremental Kn

void complete_graph_n_incremental_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    // g_1 = graph_factory<int>::co_graph_with_c_probability_edges(e_gen, 110,0.5f);
    // std::cout << input->get_inc_val() << " aristas en cografo: " << g_1.m() << std::endl;
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(g_2,e_gen,input->get_delta());
}

void complete_graph_n_incremental_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    run_solver(input->get_subject(),g_2);
}

// DP incremental Kn

void complete_graph_n_incremental_dp_experiment::load_instance(incremental_experiment_input<int, vector<info_cotree_node>> *input){
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(g_2,e_gen,input->get_delta());
    dp = vector<vector<subsolution>>(
        input->get_subject().size(),
        vector<subsolution>(g_2.n() + 1)
    );
}

void complete_graph_n_incremental_dp_experiment::solve_instance(incremental_experiment_input<int, vector<info_cotree_node>> *input){
    solver_dp(dp,input->get_subject(),g_2.n());
}

// DP incremental cograph

void cograph_n_incremental_dp_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    adj_list_graph<int> co_g = graph_factory<int>::co_graph_with_c_probability_edges(e_gen, input->get_inc_val(),0.5f);
    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>(input->get_subject().n() + 1)
    );
}

void cograph_n_incremental_dp_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    solver_dp(dp, vec_cotree, input->get_subject().n());
}

// Incremental Kn and cograph

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

// Incremental edges of cograph

void cograph_n_incremental_edges_experiment::load_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
    e_gen.reset();
    g = graph_factory<int>::co_graph_with_c_probability_edges(e_gen, 100, input->get_inc_val());
}

void cograph_n_incremental_edges_experiment::solve_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
    run_solver(g,input->get_subject());
}

// Create cotree incremental edges of cograph 

void cograph_n_incremental_edges_create_cotree_experiment::load_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
    e_gen.reset();
    float c = input->get_inc_val();
    g = graph_factory<int>::co_graph_with_c_probability_edges(e_gen, 200, c );
    cout << " c : "<< c << endl;
    cout << "Aristas del nuevo cotree : "<< g.m()<< endl << endl << endl;
}

void cograph_n_incremental_edges_create_cotree_experiment::solve_instance(incremental_experiment_input<float, adj_list_graph<int>> *input){
    cotree_node* cotree = generate_cotree(g);
    vectorize(cotree);
}


void run_experimentation() {
    element_generator_int e_gen;
    adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, 200);
    // cout << "co_g: " << endl;
    // cout << co_g << endl;

    cotree_node* co_tree_node = generate_cotree(co_g);
    vector<info_cotree_node> vec_cotree = vectorize(co_tree_node);
   // cout << "cotree : " <<  endl <<*co_tree_node << endl;

    adj_list_graph<int> k_n;
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(k_n,e_gen,200);
    // cout << endl << "k_n : " <<  endl <<  k_n << endl;

    experiment_suite exp_suite;

    // load min, load max, discard, repetitions, samples and initial subject values

    incremental_experiment_input_int< adj_list_graph<int>> exp1_input(200, 400, 25, 30, 75, k_n, "../exp/ej3/cograph_incremental_nodes");

    cograph_n_incremental_experiment exp_1 = cograph_n_incremental_experiment(&exp1_input);

    exp_suite.add(&exp_1);


    // incremental_experiment_input_int< adj_list_graph<int>> exp2_input(1, 200, 0, 20, 40, co_g, "../exp/ej3/complete_graph_incremental_nodes");

    // complete_graph_n_incremental_experiment exp_2 = complete_graph_n_incremental_experiment(&exp2_input);

    // exp_suite.add(&exp_2);


    // incremental_experiment_input_int< adj_list_graph<int>> exp3_input(1, 250, 25, 30, 75, adj_list_graph<int>(), "../exp/ej3/complete_graph_and_cograph_incremental_nodes");

    // complete_graph_and_cograph_n_incremental_experiment exp_3 = complete_graph_and_cograph_n_incremental_experiment(&exp3_input);

    // exp_suite.add(&exp_3);


    // incremental_experiment_input_float< adj_list_graph<int>> exp4_input(0.0f, 1.0f, 30, 50, 50, k_n, "../exp/ej3/cograph_incremental_edges");

    // cograph_n_incremental_edges_experiment exp_4 = cograph_n_incremental_edges_experiment(&exp4_input);

    // exp_suite.add(&exp_4);


    // DP experimentation incremental Kn

    // incremental_experiment_input_int< vector<info_cotree_node> > exp5_input(1, 350, 25, 35, 75, vec_cotree , "../exp/ej3/complete_graph_incremental_nodes_dp");

    // complete_graph_n_incremental_dp_experiment exp_5 = complete_graph_n_incremental_dp_experiment(&exp5_input);

    // exp_suite.add(&exp_5);


    // DP experimentation incremental cograph nodes

    //incremental_experiment_input_int< adj_list_graph<int>> exp6_input(300, 600, 10, 15, 50, adj_list_graph<int>(), "../exp/ej3/cograph_incremental_nodes_dp");

    //cograph_n_incremental_dp_experiment exp_6 = cograph_n_incremental_dp_experiment(&exp6_input);
    
    //exp_suite.add(&exp_6);


    // generate cotree incremental edges

    // incremental_experiment_input_float< adj_list_graph<int>> exp7_input(0.0f, 1.0f, 15, 20, 50, adj_list_graph<int>(), "../exp/ej3/cograph_incremental_edges_create_cotree");

    // cograph_n_incremental_edges_create_cotree_experiment exp_7 = cograph_n_incremental_edges_create_cotree_experiment(&exp7_input);

    // exp_suite.add(&exp_7);


    exp_suite.run();

}
