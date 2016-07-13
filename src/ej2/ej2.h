#ifndef AED3_TP3_EJ2_H
#define AED3_TP3_EJ2_H

#define SLOPE_VALUE 2
#define FIXED_VALUE 4

#include <unordered_map>
#include <sstream>

#include "../main.h"
#include "../exact/exact.h"

#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/structures/graph.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/utils/element_generator_int.h"

using namespace std;

class equal_complete_vs_complete: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_complete_vs_complete(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class equal_tree_vs_tree: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_tree_vs_tree(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class equal_cycle_vs_cycle: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_cycle_vs_cycle(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class equal_complete_bipartite_vs_complete_bipartite: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        equal_complete_bipartite_vs_complete_bipartite(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class lineal_complete_vs_complete: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        lineal_complete_vs_complete(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class lineal_tree_vs_tree: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        lineal_tree_vs_tree(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class lineal_cycle_vs_cycle: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        lineal_cycle_vs_cycle(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class lineal_complete_bipartite_vs_complete_bipartite: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        lineal_complete_bipartite_vs_complete_bipartite(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){};
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class fixed_complete_vs_complete: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        fixed_complete_vs_complete(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){
                                    graph_factory<int>::add_n_vertices_and_all_edges(g1, e_gen1, FIXED_VALUE);
                                    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen2, FIXED_VALUE);
                                   };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class fixed_tree_vs_tree: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        fixed_tree_vs_tree(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){
                                    graph_factory<int>::add_n_tree_vertices(g1, e_gen1, FIXED_VALUE);
                                    graph_factory<int>::add_n_tree_vertices(g2, e_gen2, FIXED_VALUE);
                                   };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class fixed_cycle_vs_cycle: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        fixed_cycle_vs_cycle(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){
                                    g1 = graph_factory<int>::cycle_graph(e_gen1, FIXED_VALUE);
                                    g2 = graph_factory<int>::cycle_graph(e_gen2, FIXED_VALUE);
                                   };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

class fixed_complete_bipartite_vs_complete_bipartite: public incremental_experiment<int, adj_list_graph<int>>{
    public:
        fixed_complete_bipartite_vs_complete_bipartite(const incremental_experiment_input<int, adj_list_graph<int>> *input):
                                   incremental_experiment(input){
                                    g1 = graph_factory<int>::random_bipartite_graph(e_gen1,FIXED_VALUE / 2, FIXED_VALUE - (FIXED_VALUE / 2), 1.0f);
                                    g2 = graph_factory<int>::random_bipartite_graph(e_gen2,FIXED_VALUE / 2, FIXED_VALUE - (FIXED_VALUE / 2), 1.0f);
                                   };
    private:
        void load_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        void solve_instance(incremental_experiment_input<int, adj_list_graph<int>> *input);
        adj_list_graph<int> g1, g2;
        element_generator_int e_gen1, e_gen2;
};

#endif  // AED3_TP3_EJ2_H
