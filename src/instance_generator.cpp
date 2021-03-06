#include <cstring>
#include <sstream>
#include <fstream>

#include "framework/structures/adj_list_graph.h"
#include "framework/utils/graph_factory.h"
#include "framework/utils/element_generator_int.h"
#include "exact/exact.h"
#include "heuristics/heuristics.h"

#define MAGIC_SEED 42

using namespace std;

void save_solution_entry(ofstream &output, const char *save_name, int max_common_edges){
	output << save_name << " " << max_common_edges << endl;
	std::cout << "Instancia '" << save_name << "' resuelta!" << std::endl;
}

void save_instance(const graph<int> &g1, const graph<int> &g2, const char *save_name){
	ofstream output_file;

	char file_name[80];
	strcpy(file_name, "generated_instances/");
	output_file.open(strcat(file_name, save_name));

	output_file << g1.n() << " " << g1.m() << " " << g2.n() << " " << g2.m() << endl;

	unordered_set<int> done_vertices;

	int current_node = 0;
	int current_neighbour = 0;

	for(unsigned int i = 0; i < g1.n(); i++){
		current_node = g1.get_vertices()[i];
		for(unsigned int n = 0; n < g1.degree(current_node); n++){
			current_neighbour =  g1.neighbours(current_node)[n];
			if(done_vertices.find(current_neighbour) == done_vertices.end()){
				output_file << current_node << " " << current_neighbour << endl;
			}
		}
		done_vertices.insert(current_node);
	}

	done_vertices.clear();

	for(unsigned int i = 0; i < g2.n(); i++){
		current_node = g2.get_vertices()[i];
		for(unsigned int n = 0; n < g2.degree(current_node); n++){
			current_neighbour =  g2.neighbours(current_node)[n];
			if(done_vertices.find(current_neighbour) == done_vertices.end()){
				output_file << current_node << " " << current_neighbour << endl;
			}
		}
		done_vertices.insert(current_node);
	}

	output_file.close();

	std::cout << "Instancia '" << file_name << "' almacenada correctamente." << std::endl;
}

// these are all instances for which we can calculate the exact MCS
void run_known_solution_instance_generation(){
	ofstream optimal_solutions_file;
	optimal_solutions_file.open("../exp/optimal_solutions");

	element_generator_int e_gen;
	adj_list_graph<int> g1, g2;

	// random
	int n = 5;
	float c = 0.25;
	char instance_name[80] = "aleatorio_n5_c025";
	graph<std::pair<int, int>> *backtracking_solution;

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	backtracking_solution = solve_backtracking(&g1, &g2);
	save_solution_entry(optimal_solutions_file, instance_name, backtracking_solution->m());
	delete backtracking_solution;

	save_instance(g1, g2, instance_name);

	g1.clear();
	g2.clear();
	c = 0.5;
	strncpy(instance_name, "aleatorio_n5_c050", 80);

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	backtracking_solution = solve_backtracking(&g1, &g2);
	save_solution_entry(optimal_solutions_file, instance_name, backtracking_solution->m());
	delete backtracking_solution;

	save_instance(g1, g2, instance_name);

	g1.clear();
	g2.clear();
	c = 0.75;
	strncpy(instance_name, "aleatorio_n5_c075", 80);

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	backtracking_solution = solve_backtracking(&g1, &g2);
	save_solution_entry(optimal_solutions_file, instance_name, backtracking_solution->m());
	delete backtracking_solution;

	save_instance(g1, g2, instance_name);

	// co-graph vs complete
	n = 100;
	int k = 50;
	strncpy(instance_name, "cografo_n100_k50", 80);

	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_co_graph(e_gen, n);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
	e_gen.reset();

	solution cograph_vs_complete_solution = solve_cograph_vs_complete(g1, g2);
	save_solution_entry(optimal_solutions_file, instance_name, cograph_vs_complete_solution.h->m());
	save_instance(g1, g2, instance_name);


	n = 50;
	k = 100;
	strncpy(instance_name, "cografo_n50_k100", 80);

	g2.clear();

	g1 = graph_factory<int>::random_co_graph(e_gen, n);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
	e_gen.reset();

	cograph_vs_complete_solution = solve_cograph_vs_complete(g1, g2);
	save_solution_entry(optimal_solutions_file, instance_name, cograph_vs_complete_solution.h->m());
	save_instance(g1, g2, instance_name);

	// subgraph instances (incremental graphs)
	// these instances are all scenarios were g1 is a subgraph of g2

	// random

	n = 500;
	c = 0.25;
	strncpy(instance_name, "aleatorio_subgrafo_n500_c025", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	c = 0.5;
	strncpy(instance_name, "aleatorio_subgrafo_n500_c050", 80);

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	c = 0.75;
	strncpy(instance_name, "aleatorio_subgrafo_n500_c075", 80);

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// tree

	n = 500;
	strncpy(instance_name, "arbol_subgrafo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n);
	g2 = g1;
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// complete

	n = 500;
	strncpy(instance_name, "completo_subgrafo_n500", 80);
	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_vertices_and_all_edges(g1, e_gen, n);
	g2 = g1;
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// cycle

	n = 500;
	strncpy(instance_name, "ciclo_subgrafo_n500", 80);

	g1 = graph_factory<int>::cycle_graph(e_gen, n);
	e_gen.reset();
	g2 = graph_factory<int>::cycle_graph(e_gen, 2*n);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// vs complete instances
	// these are instances were we compare against a complete graph g2
	// this assures us that g1 will be able to match all its edges

	// bipartite

	strncpy(instance_name, "aleatorio_bipartito_vs_completo_n500_k500_c050", 80);
	c = 0.5;
	n = 500;
	k = 500;

	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	strncpy(instance_name, "aleatorio_bipartito_vs_completo_n250_k500_c050", 80);
	c = 0.5;
	n = 250;
	k = 500;

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// disconnected

	// forest

	strncpy(instance_name, "bosque_vs_completo_n1000_d10", 80);
	int d = 10;
	n = 1000;
	c = 0.0;

	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	// random

	strncpy(instance_name, "aleatorio_vs_completo_n1000_d10_c050", 80);
	d = 10;
	n = 1000;
	c = 0.5;

	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
	save_instance(g1, g2, instance_name);

	optimal_solutions_file.close();
}

// these are instances were no known exact solution is available
void run_unknown_solution_instance_generation(){
	element_generator_int e_gen;
	adj_list_graph<int> g1, g2;

	// random
	int n = 1000;
	float c = 0.25;

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_n1000_c025");

	c = 0.5;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_n1000_c050");

	c = 0.75;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_n1000_c075");

	// tree
	n = 1000;

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n);
	e_gen.reset();

	save_instance(g1, g2, "arbol_n1000");

	// bipartite

	c = 0.5;
	n = 500;
	int	k = 500;

	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_bipartito_n500_k500_c050");

	c = 0.5;
	n = 250;
	k = 500;

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_bipartito_n250_k500_c050");

	// disconnected

	// forest

	int d = 10;
	float v = 0.0;
	n = 1000;
	c = 0.0;

	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c, v);
	e_gen.reset();
	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c, v);
	e_gen.reset();

	save_instance(g1, g2, "bosque_n1000_d10_v025");

	// random

	d = 10;
	v = 0.0;
	n = 1000;
	c = 0.5;

	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c, v);
	e_gen.reset();
	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c, v);
	e_gen.reset();

	save_instance(g1, g2, "aleatorio_n1000_d10_c050_v025");
}


void run_similar_nodes_count_instance_generation(){

	


	element_generator_int e_gen;
	adj_list_graph<int> g1, g2;


	// arbol
	int n1 = 501;
	int n2 = 500;
	char instance_name[80] = "arbol_n501_vs_arbol_n500";


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// ciclo
	n1 = 501;
	n2 = 500;
	strncpy(instance_name, "ciclo_n501_vs_ciclo_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	g1=graph_factory<int>::cycle_graph(e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs ciclo
	n1 = 501;
	n2 = 500;
	strncpy(instance_name, "arbol_n501_vs_ciclo_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);
	// bipartito c 0.1

	n1 = 250;
	n2 = 251;
	strncpy(instance_name, "bipartito_n501_c_0_1_vs_bipartito_n500_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n2, 0.1f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n1, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5

	n1 = 250;
	n2 = 251;
	strncpy(instance_name, "bipartito_n501_c_0_5_vs_bipartito_n500_c_0_5", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n2, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n1, 0.5f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5 vs bipartito c 0.1

	n1 = 250;
	n2 = 251;
	strncpy(instance_name, "bipartito_n501_c_0_5_vs_bipartito_n500_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n2, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n1, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito complete vs complete

	n1 = 250;
	n2 = 251;
	strncpy(instance_name, "bipartito_n501_c_0_5_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n2, 0.5f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 500);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito complete vs complete

	n1 = 250;
	n2 = 251;
	strncpy(instance_name, "bipartito_n501_c_1_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n1, n2, 1.0f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 500);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs completo
	n1 = 501;
	n2 = 500;
	strncpy(instance_name, "arbol_n501_vs_completo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// ciclo vs completo

	n1 = 501;
	n2 = 500;
	strncpy(instance_name, "ciclo_n501_vs_completo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	g1= graph_factory<int>::cycle_graph(e_gen, n1);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);



}

void run_diferents_nodes_count_instance_generation(){

	ofstream diferents_nodes_count_file;
	diferents_nodes_count_file.open("../exp/diferents_nodes_count_instance");

	element_generator_int e_gen;
	adj_list_graph<int> g1, g2;


	int n1 = 500;
	int n2 = 750;

	int k1 = 250;
	int k2 = 500;

	char instance_name[80] = "arbol_n500_vs_arbol_n750";


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// ciclo

	strncpy(instance_name, "ciclo_n500_vs_ciclo_n750", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	g1=graph_factory<int>::cycle_graph(e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs ciclo

	strncpy(instance_name, "arbol_n500_vs_ciclo_n750", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);
	// bipartito c 0.1

	strncpy(instance_name, "bipartito_n750_c_0_1_vs_bipartito_n500_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.1f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5

	strncpy(instance_name, "bipartito_n500_c_0_5_vs_bipartito_n750_c_0_5", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.5f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5 vs bipartito c 0.1

	strncpy(instance_name, "bipartito_n500_c_0_5_vs_bipartito_n750_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito complete vs complete


	strncpy(instance_name, "bipartito_n750_c_0_5_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.5f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito complete vs complete


	strncpy(instance_name, "bipartito_n750_c_1_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 1.0f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs completo

	strncpy(instance_name, "arbol_n750_vs_completo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n2);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// ciclo vs completo

	strncpy(instance_name, "arbol_n750_vs_completo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	g1= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);



	n1 = 500;
	n2 = 1000;

	k1 = 250;
	k2 = 500;


	strncpy(instance_name, "arbol_n500_vs_arbol_n1000", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// ciclo

	strncpy(instance_name, "ciclo_n500_vs_ciclo_n1000", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	g1=graph_factory<int>::cycle_graph(e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs ciclo

	strncpy(instance_name, "arbol_n500_vs_ciclo_n1000", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n1);
	e_gen.reset();
	g2= graph_factory<int>::cycle_graph(e_gen, n2);
	e_gen.reset();

	save_instance(g1, g2, instance_name);
	// bipartito c 0.1

	strncpy(instance_name, "bipartito_n1000_c_0_1_vs_bipartito_n500_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.1f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k2, k2, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5

	strncpy(instance_name, "bipartito_n500_c_0_5_vs_bipartito_n1000_c_0_5", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.5f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito c 0.5 vs bipartito c 0.1

	strncpy(instance_name, "bipartito_n500_c_0_5_vs_bipartito_n1000_c_0_1", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g2 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k1, 0.5f);
	e_gen.reset();
	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k1, k2, 0.1f);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// bipartito complete vs complete


	strncpy(instance_name, "bipartito_n1000_c_0_5_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k2, k2, 0.5f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);
	// bipartito complete vs complete

	

	strncpy(instance_name, "bipartito_n1000_c_1_vs_complete_n500", 80);


	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);

	g1 = graph_factory<int>::random_bipartite_graph(e_gen, k2, k2, 1.0f);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);

	// arbol vs completo

	strncpy(instance_name, "arbol_n1000_vs_completo_n500", 80);

	g1.clear();
	g2.clear();
	srand(MAGIC_SEED);
	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n2);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n1);
	e_gen.reset();

	save_instance(g1, g2, instance_name);




}




// void run_small_known_solution_instance_generation() {
// 	ofstream optimal_solutions_file;
// 	optimal_solutions_file.open("../exp/small_optimal_solutions");
// 	// subgraph instances (incremental graphs)
// 	// these instances are all scenarios were g1 is a subgraph of g2

// 	// co-graph vs complete

// 	srand(MAGIC_SEED);

// 	int n = 100;
// 	int k = 50;
// 	char instance_name[80] = "cografo_n100_k50";

// 	g2.clear();

// 	g1 = graph_factory<int>::random_co_graph(e_gen, n);
// 	e_gen.reset();
// 	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
// 	e_gen.reset();

// 	solution cograph_vs_complete_solution = solve_cograph_vs_complete(g1, g2);
// 	save_solution_entry(optimal_solutions_file, instance_name, cograph_vs_complete_solution.h->m());
// 	save_instance(g1, g2, instance_name);


// 	n = 50;
// 	k = 100;
// 	strncpy(instance_name, "cografo_n50_k100", 80);

// 	g2.clear();

// 	g1 = graph_factory<int>::random_co_graph(e_gen, n);
// 	e_gen.reset();
// 	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
// 	e_gen.reset();

// 	cograph_vs_complete_solution = solve_cograph_vs_complete(g1, g2);
// 	save_solution_entry(optimal_solutions_file, instance_name, cograph_vs_complete_solution.h->m());
// 	save_instance(g1, g2, instance_name);


// 	// random

// 	srand(MAGIC_SEED);

// 	n = 150;
// 	float c = 0.25;
// 	strncpy(instance_name, "aleatorio_subgrafo_n150_c025", 80);

// 	g1.clear();
// 	g2.clear();

// 	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
// 	g2 = g1;
// 	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	c = 0.5;
// 	strncpy(instance_name, "aleatorio_subgrafo_n150_c050", 80);

// 	g1.clear();
// 	g2.clear();

// 	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
// 	g2 = g1;
// 	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	c = 0.75;
// 	strncpy(instance_name, "aleatorio_subgrafo_n150_c075", 80);

// 	g1.clear();
// 	g2.clear();

// 	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
// 	g2 = g1;
// 	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	// tree

// 	srand(MAGIC_SEED);

// 	n = 150;
// 	strncpy(instance_name, "arbol_subgrafo_n150", 80);

// 	g1.clear();
// 	g2.clear();

// 	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n);
// 	g2 = g1;
// 	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	// cycle

// 	srand(MAGIC_SEED);

// 	n = 150;
// 	strncpy(instance_name, "ciclo_subgrafo_n150", 80);

// 	g1 = graph_factory<int>::cycle_graph(e_gen, n);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::cycle_graph(e_gen, 2*n);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	// vs complete instances
// 	// these are instances were we compare against a complete graph g2
// 	// this assures us that g1 will be able to match all its edges

// 	// bipartite

// 	srand(MAGIC_SEED);

// 	c = 0.5;
// 	n = 150;
// 	k = 150;
// 	strncpy(instance_name, "aleatorio_bipartito_vs_completo_n150_k150_c050", 80);

// 	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	c = 0.5;
// 	n = 500;
// 	k = 500;
// 	strncpy(instance_name, "aleatorio_bipartito_vs_completo_n500_k500_c050", 80);

// 	g1 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, c);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	// disconnected

// 	// forest

// 	srand(MAGIC_SEED);

// 	int d = 10;
// 	n = 500;
// 	c = 0.0;
// 	strncpy(instance_name, "bosque_vs_completo_n500_d10", 80);

// 	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1.0);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	// random

// 	srand(MAGIC_SEED);

// 	d = 10;
// 	n = 500;
// 	c = 0.5;
// 	strncpy(instance_name, "aleatorio_vs_completo_n500_d10_c050", 80);

// 	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1.0);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	d = 10;
// 	n = 1000;
// 	c = 0.5;
// 	strncpy(instance_name, "aleatorio_vs_completo_n1000_d10_c050", 80);

// 	g1 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, c);
// 	e_gen.reset();
// 	g2 = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1.0);
// 	e_gen.reset();

// 	save_solution_entry(optimal_solutions_file, instance_name, g1.m());
// 	save_instance(g1, g2, instance_name);

// 	optimal_solutions_file.close();
// }

void run_new_instance_generation(){
	ofstream optimal_solutions_file;
	optimal_solutions_file.open("../exp/new_optimal_solutions");
	char instance_name[80];
	element_generator_int e_gen;

	adj_list_graph<int> g1, g2;

	srand(MAGIC_SEED);

	strncpy(instance_name, "camino_vs_bipartito_n100_k500", 80);

	int n = 100;
	int k = 500;
	int r = 2*n + 2;

	graph_factory<int>::add_n_path_vertices(g1, e_gen, r);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, 2*n + 1);
	save_instance(g1, g2, instance_name);

	strncpy(instance_name, "camino_vs_bipartito_n250_k500", 80);

	n = 250;
	g1.clear();

	graph_factory<int>::add_n_path_vertices(g1, e_gen, r);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, 2*n + 1);
	save_instance(g1, g2, instance_name);

	strncpy(instance_name, "camino_vs_bipartito_n400_k500", 80);

	n = 400;
	g1.clear();

	graph_factory<int>::add_n_path_vertices(g1, e_gen, r);
	e_gen.reset();
	g2 = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 1.0);
	e_gen.reset();

	save_solution_entry(optimal_solutions_file, instance_name, 2*n + 1);
	save_instance(g1, g2, instance_name);
}

int main (int argc, char* argv[]) {
	// instances were we know the optimum solution
	//run_known_solution_instance_generation();
	// instances were we don't
	// run_unknown_solution_instance_generation();
	// similar_nodes_count_instance
	run_similar_nodes_count_instance_generation();
	// diferents_nodes_count_instance
	//run_diferents_nodes_count_instance_generation();
	//run_small_known_solution_instance_generation();
	// run_unknown_solution_instance_generation();
	// small instances for ex6 were we know the optimum solution
	// run_small_known_solution_instance_generation();
	// run_new_instance_generation();
}
