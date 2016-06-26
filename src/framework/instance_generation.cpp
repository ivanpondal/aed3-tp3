#include "main.h"

using namespace std;

void save_instance(const graph<int> &g1, const graph<int> &g2, const char *save_name){
	ofstream output_file;
	output_file.open(save_name);

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
}

void run_unknown_solution_instance_generation(){
}

void run_instance_generation(){
	// instances were we know the optimum solution
	run_known_solution_instance_generation();
	// instances were we don't
	run_unknown_solution_instance_generation();
}
