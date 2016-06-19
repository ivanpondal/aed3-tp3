
#include "../main.h"
#include "./ej3.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/experiments/incremental_experiment.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"

/*
**  Exercise 3
**  Experimentation
*/
using namespace std;


void run_experimentation() {
    element_generator_int e_gen;
    adj_list_graph<int> co_g = graph_factory<int>::random_co_graph(e_gen,5);
    cout << "co_g: " << endl;
    cout << co_g << endl;

    cotree_node* co_tree_node = generate_cotree(co_g);
    cout << "cotree : " <<  endl <<*co_tree_node << endl;

    adj_list_graph<int> k_n;
    e_gen.reset();
    graph_factory<int>::add_n_vertices_and_all_edges(k_n,e_gen,10);
    cout << endl << "k_n : " <<  endl <<  k_n << endl;
}
