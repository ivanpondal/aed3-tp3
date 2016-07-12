#ifndef AED3_TP3_EJ3_H
#define AED3_TP3_EJ3_H

#include <iostream>
#include <math.h>

#include "../main.h"
#include "../exact/exact.h"

#include "../framework/structures/graph.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/experiments/input/incremental_experiment_input_float.h"

/*
**  Exercise 3
*/
class cograph_n_incremental_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        cograph_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g;
        element_generator_int e_gen;
};

class complete_graph_n_incremental_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        complete_graph_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g_1;
        adj_list_graph<int> g_2;
        element_generator_int e_gen;
};

class complete_graph_and_cograph_n_incremental_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        complete_graph_and_cograph_n_incremental_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g_1;
        adj_list_graph<int> g_2;
        element_generator_int e_gen;
};

class cograph_n_incremental_edges_experiment:public incremental_experiment<float, adj_list_graph<int> > {
    public:
        cograph_n_incremental_edges_experiment(const incremental_experiment_input<float, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<float, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<float, adj_list_graph<int>> *input);
        adj_list_graph<int> g;
        element_generator_int e_gen;
};


// probe n1 lineal dependecy
class cograph_K_1_union_dp_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        cograph_K_1_union_dp_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input)
        : incremental_experiment(input){
            for (int i = 0; i < 100; ++i)
            {
                co_g.add_node(e_gen.generate(co_g));
            }
        };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int> > *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int> > *input);
        adj_list_graph<int> co_g;
        std::vector<std::vector<subsolution>> dp;
        std::vector<info_cotree_node> vec_cotree;
        element_generator_int e_gen;
};
// probe n1 lineal dependecy
class cograph_K_N_dp_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        cograph_K_N_dp_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){
            graph_factory<int>::add_n_vertices_and_all_edges(co_g,e_gen,100);
        };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int> > *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int> > *input);
        adj_list_graph<int> co_g;
        std::vector<std::vector<subsolution>> dp;
        std::vector<info_cotree_node> vec_cotree;
        element_generator_int e_gen;
};

// probe n1 lineal dependecy
class cograph_K_N_union_dp_experiment:public incremental_experiment<int, int > {
    public:
        cograph_K_N_union_dp_experiment(const incremental_experiment_input<int, int > *input): incremental_experiment
        (input){
            while(co_g.n() < 100){
                adj_list_graph<int> aux_g;
                graph_factory<int>::add_n_vertices_and_all_edges(aux_g,e_gen,10);
                e_gen.reset();
                co_g.unite(aux_g,e_gen);
            }

        };
    private:
        void load_instance(incremental_experiment_input<int, int > *input);
        void solve_instance(incremental_experiment_input<int, int > *input);
        adj_list_graph<int> co_g;
        std::vector<std::vector<subsolution>> dp;
        std::vector<info_cotree_node> vec_cotree;
        element_generator_int e_gen;
};


//  probe n1 lineal and n2 cuadratic dependecy
class K_N_div_2_and_cograph_K_N_dp_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        K_N_div_2_and_cograph_K_N_dp_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> co_g;
        std::vector<std::vector<subsolution>> dp;
        std::vector<info_cotree_node> vec_cotree;
        adj_list_graph<int> k_n;
        element_generator_int e_gen;
};
//  probe n1 lineal and n2 cuadratic dependecy
class K_N_log_2_and_cograph_K_N_dp_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        K_N_log_2_and_cograph_K_N_dp_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> co_g;
        std::vector<std::vector<subsolution>> dp;
        std::vector<info_cotree_node> vec_cotree;
        adj_list_graph<int> k_n;
        element_generator_int e_gen;
};


// generate cotree

// probe n1 cuadratic dependecy

class cograph_K_1_union_create_cotree_experiment:public incremental_experiment<int, adj_list_graph<int> > {
    public:
        cograph_K_1_union_create_cotree_experiment(const incremental_experiment_input<int, adj_list_graph<int> > *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        element_generator_int e_gen;
        adj_list_graph<int> g;
};

// probe m1 lineal dependecy

class cograph_K_N_union_create_cotree_experiment:public incremental_experiment<int, int> {
    public:
        cograph_K_N_union_create_cotree_experiment(const incremental_experiment_input<int, int> *input): incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, int> *input);
        void solve_instance(incremental_experiment_input<int, int> *input);
        element_generator_int e_gen;
        adj_list_graph<int> g;
};

// probe m1 lineal and n1 cuadratic dependecy

class cograph_K_N_create_cotree_experiment:public incremental_experiment<int, adj_list_graph<int>> {
    public:
        cograph_K_N_create_cotree_experiment(const incremental_experiment_input<int, adj_list_graph<int>> *input)
        : incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        element_generator_int e_gen;
        adj_list_graph<int> g;
};



#endif  // AED3_TP3_EJ3_H