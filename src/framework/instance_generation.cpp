#include "main.h"

using namespace std;

void save_instance(const graph<int> &g1, const graph<int> &g2, const char *save_name){
	ofstream output_file;

	char file_name[80];
	strcpy(file_name, "framework/generated_instances/");
	output_file.open(strcat(file_name, save_name));

	std::cout << "Guardando instancia " << file_name << std::endl;

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
}

void run_known_solution_instance_generation(){
	element_generator_int e_gen;
	adj_list_graph<int> g1, g2;

	// random
	int n = 10;
	float c = 0.25;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_n10_c025.ins");

	c = 0.5;

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_n10_c050.ins");

	c = 0.75;

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	e_gen.reset();
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_n10_c075.ins");

	// co-graph vs complete
	n = 100;
	int k = 50;

	g2.clear();

	g1 = graph_factory<int>::random_co_graph(e_gen, n);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
	e_gen.reset();

	save_instance(g1, g2, "cograph_n100_k50.ins");

	n = 50;
	k = 100;

	g2.clear();

	g1 = graph_factory<int>::random_co_graph(e_gen, n);
	e_gen.reset();
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, k);
	e_gen.reset();

	save_instance(g1, g2, "cograph_n50_k100.ins");

	// subgraph instances (incremental graphs)

	// random
	n = 500;
	c = 0.25;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_subgraph_n500_c025.ins");

	c = 0.5;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_subgraph_n500_c050.ins");

	c = 0.75;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_random_vertices(g1, e_gen, n, c);
	g2 = g1;
	graph_factory<int>::add_n_random_vertices(g2, e_gen, n, c);
	e_gen.reset();

	save_instance(g1, g2, "random_subgraph_n500_c075.ins");

	// tree

	n = 500;

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_tree_vertices(g1, e_gen, n);
	g2 = g1;
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, n);
	e_gen.reset();

	save_instance(g1, g2, "tree_subgraph_n500.ins");

	// complete

	g1.clear();
	g2.clear();

	graph_factory<int>::add_n_vertices_and_all_edges(g1, e_gen, n);
	g2 = g1;
	graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, n);
	e_gen.reset();

	save_instance(g1, g2, "complete_subgraph_n500.ins");

	// cycle

	n = 500;

	g1 = graph_factory<int>::cycle_graph(e_gen, n);
	e_gen.reset();
	g2 = graph_factory<int>::cycle_graph(e_gen, 2*n);
	e_gen.reset();

	save_instance(g1, g2, "cycle_subgraph_n500.ins");
}

void run_unknown_solution_instance_generation(){
}

void run_instance_generation(){
	// instances were we know the optimum solution
	run_known_solution_instance_generation();
	// instances were we don't
	run_unknown_solution_instance_generation();
}
