#ifndef AED3_TP3_EJ3_H
#define AED3_TP3_EJ3_H

#include <iostream>

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

#endif  // AED3_TP3_EJ3_H
