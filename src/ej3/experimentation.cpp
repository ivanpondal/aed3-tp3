
#include "../main.h"
#include "./ej3.h"


/*
**  Exercise 3
**  Experimentation
*/
using namespace std;


// Solver DP :

// Kn coograph
void cograph_K_N_dp_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(co_g,e_gen,input->get_delta());
    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>(100 + 1)
    );
    cout << "n :" << co_g.n() << " m: " << co_g.m() << endl;
}

void cograph_K_N_dp_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    solver_dp(dp, vec_cotree, 100);
}

// K1 union coograph
void cograph_K_1_union_dp_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    for (int i = 0; i < input->get_delta(); ++i){
        co_g.add_node(e_gen.generate(co_g));
    }

    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>(100 + 1)
    );
    cout << "n :" << co_g.n() << " m: " << co_g.m() << endl;
}

void cograph_K_1_union_dp_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    solver_dp(dp, vec_cotree, 100);
}

// KN union
void cograph_K_N_union_dp_experiment::load_instance(incremental_experiment_input<int, int> *input){

    adj_list_graph<int> aux_g;
    graph_factory<int>::add_n_vertices_and_all_edges(aux_g,e_gen,input->get_subject());
    e_gen.reset();
    co_g.unite(aux_g,e_gen);
    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>(100 +1)
    );
    cout << "n :" << co_g.n() << " m: " << co_g.m() << endl;
    cout << "size vec co tree :" << vec_cotree.size() << endl;
}

void cograph_K_N_union_dp_experiment::solve_instance(incremental_experiment_input<int, int> *input){
    solver_dp(dp, vec_cotree,100);
}

// Incremental K(n/2) and cograph Kn
void K_N_div_2_and_cograph_K_N_dp_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(co_g,e_gen,input->get_delta());
    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>( (co_g.n()/2) + 1)
    );
}

void K_N_div_2_and_cograph_K_N_dp_experiment::solve_instance(incremental_experiment_input<int,  adj_list_graph<int>> *input){
    solver_dp(dp, vec_cotree,(co_g.n()/2));
}

// Incremental K(log(n)) and cograph Kn
void K_N_log_2_and_cograph_K_N_dp_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(co_g,e_gen,input->get_delta());
    //adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen, input->get_inc_val());
    cotree_node* cotree = generate_cotree(co_g);
    vec_cotree = vectorize(cotree);
    dp = vector<vector<subsolution>>(
        vec_cotree.size(),
        vector<subsolution>(  ((int) (log2(co_g.n()))) + 1)
    );
}

void K_N_log_2_and_cograph_K_N_dp_experiment::solve_instance(incremental_experiment_input<int,  adj_list_graph<int>> *input){
    solver_dp( dp, vec_cotree,(int) log2(co_g.n()) );
}



// Create cotree :

// K1 Union
void cograph_K_1_union_create_cotree_experiment::load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    for (int i = 0; i < input->get_delta(); ++i){
        g.add_node(e_gen.generate(g));
    }
}

void cograph_K_1_union_create_cotree_experiment::solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input){
    cotree_node* cotree = generate_cotree(g);
    vectorize(cotree);
}

// Kn Union
void cograph_K_N_union_create_cotree_experiment::load_instance(incremental_experiment_input<int,int> *input){
   adj_list_graph<int> aux_g;
   graph_factory<int>::add_n_vertices_and_all_edges(aux_g,e_gen,input->get_subject());
   e_gen.reset();
   g.unite(aux_g,e_gen);
   // cout << "n : " << input->get_subject() << endl;
   // cout << "g : " << endl << g << endl;
}

void cograph_K_N_union_create_cotree_experiment::solve_instance(incremental_experiment_input<int,int> *input){
    cotree_node* cotree = generate_cotree(g);
    vectorize(cotree);
}

// Kn
void cograph_K_N_create_cotree_experiment::load_instance(incremental_experiment_input<int,adj_list_graph<int>> *input){
   graph_factory<int>::add_n_vertices_and_all_edges(g,e_gen,input->get_delta());
}

void cograph_K_N_create_cotree_experiment::solve_instance(incremental_experiment_input<int,adj_list_graph<int>> *input){
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
    graph_factory<int>::add_n_vertices_and_all_edges(k_n,e_gen,300);
    // cout << endl << "k_n : " <<  endl <<  k_n << endl;

    experiment_suite exp_suite;


    // generate cotree incremental nodos :

    // k1 Union.
    /*incremental_experiment_input_int< adj_list_graph<int>> exp1_input(0, 300, 25, 35, 100, adj_list_graph<int>(), "../exp/ej3/cograph_k1_union_create_cotree");

    cograph_K_1_union_create_cotree_experiment exp_1 = cograph_K_1_union_create_cotree_experiment(&exp1_input);

    exp_suite.add(&exp_1);*/

    // k3 Union.
    /*incremental_experiment_input_int< int > exp2_input(0, 300, 25, 35, 100, 3, "../exp/ej3/cograph_k3_union_create_cotree");

    cograph_K_N_union_create_cotree_experiment exp_2 = cograph_K_N_union_create_cotree_experiment(&exp2_input);

    exp_suite.add(&exp_2);

    // kn Union.
    incremental_experiment_input_int< adj_list_graph<int>> exp3_input(0, 300, 25, 35, 100, adj_list_graph<int>(), "../exp/ej3/cograph_kn_create_cotree");

    cograph_K_N_create_cotree_experiment exp_3 = cograph_K_N_create_cotree_experiment(&exp3_input);

    exp_suite.add(&exp_3);*/

    // // Solver DP :

    //g1 Kn
    // incremental_experiment_input_int< adj_list_graph<int>> exp4_input(100, 1000, 2, 5, 90, adj_list_graph<int>(), "../exp/ej3/cograph_kn_dp");

    // cograph_K_N_dp_experiment exp_4 = cograph_K_N_dp_experiment(&exp4_input);

    // exp_suite.add(&exp_4);

    // //g1 K1 union
    // incremental_experiment_input_int< adj_list_graph<int>> exp5_input(100, 1000, 2, 5, 90, adj_list_graph<int>(), "../exp/ej3/cograph_k1_union_dp");

    // cograph_K_1_union_dp_experiment exp_5 = cograph_K_1_union_dp_experiment(&exp5_input);

    // exp_suite.add(&exp_5);

    //g1 Kn union
    // incremental_experiment_input_int< int> exp6_input(100, 1000, 2, 5, 90, 10, "../exp/ej3/cograph_k10_union_dp");

    // cograph_K_N_union_dp_experiment exp_6 = cograph_K_N_union_dp_experiment(&exp6_input);

    // exp_suite.add(&exp_6);

    //g1 Kn and g2 K(n/2)
    // incremental_experiment_input_int< adj_list_graph<int>> exp7_input(0, 500, 5, 10, 50, adj_list_graph<int>(), "../exp/ej3/cograph_kn_and_k_n_div_2_dp");

    // K_N_div_2_and_cograph_K_N_dp_experiment exp_7 = K_N_div_2_and_cograph_K_N_dp_experiment(&exp7_input);

    // exp_suite.add(&exp_7);


    //g1 Kn and g2 K(log(n))
    incremental_experiment_input_int< adj_list_graph<int>> exp8_input(0, 1500, 30, 50, 100, adj_list_graph<int>(), "../exp/ej3/cograph_kn_and_k_log_n_dp");

    K_N_log_2_and_cograph_K_N_dp_experiment exp_8 = K_N_log_2_and_cograph_K_N_dp_experiment(&exp8_input);

     exp_suite.add(&exp_8);




    exp_suite.run();

}
