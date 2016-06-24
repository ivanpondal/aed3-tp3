#include "ej4.h"

graph< std::pair<int, int>> *solve(graph<int> &g1, graph<int> &g2, bool add_neighbours){
	/////////////////////////////////////////// add_neighbours
	std::priority_queue<std::pair<int, int>,
	                    std::vector< std::pair<int, int>>,
	                    node_degree_pair_compare> unvisited_unmapped_g1;

	std::priority_queue<std::pair<int, int>,
	                    std::vector< std::pair<int, int>>,
	                    node_degree_pair_compare> unvisited_unmapped_g2;

	std::priority_queue<std::pair<int, int>,
	                    std::vector< std::pair<int, int>>,
	                    node_degree_pair_compare> clear_heap;

	int g1_node_neighbour = 0;
	int g2_node_neighbour = 0;

	std::pair<int, int> mcs_node_neighbour;
	/////////////////////////////////////////// add_neighbours

	std::priority_queue<std::pair<int, int>,
	                    std::vector< std::pair<int, int>>,
	                    node_degree_pair_compare> unvisited_g1;

	std::priority_queue<std::pair<int, int>,
	                    std::vector< std::pair<int, int>>,
	                    node_degree_pair_compare> unvisited_g2;

	std::unordered_map<int, std::pair<int, int>> mapping_g1;
	std::unordered_map<int, std::pair<int, int>> mapping_g2;

	std::unordered_map<int, std::pair<int, int>>::iterator mapping_iterator;

	std::unordered_set< std::pair<int, int>, hash_pair_int> valid_mapping;

	graph< std::pair<int, int>> *g_mcs = new adj_list_graph<std::pair<int, int>, hash_pair_int>();

	for(unsigned int i = 0; i < g1.n(); i++){
		unvisited_g1.push(std::make_pair(g1.get_vertices()[i], g1.degree(g1.get_vertices()[i])));
	}

	for(unsigned int i = 0; i < g2.n(); i++){
		unvisited_g2.push(std::make_pair(g2.get_vertices()[i], g2.degree(g2.get_vertices()[i])));
	}
	int g1_node = 0;
	int g2_node = 0;

	std::pair<int, int> mcs_node;

	while(!unvisited_g1.empty() && !unvisited_g2.empty()){

		g1_node = unvisited_g1.top().first;
		g2_node = unvisited_g2.top().first;

		unvisited_g1.pop();
		unvisited_g2.pop();

		/////////////////////////////////////////// add_neighbours
		if(add_neighbours){
			while((mapping_g1.find(g1_node) != mapping_g1.end() ||
			       mapping_g2.find(g2_node) != mapping_g2.end()) &&
			       !unvisited_g1.empty() && !unvisited_g2.empty()){

				if(mapping_g1.find(g1_node) != mapping_g1.end()){
					g1_node = unvisited_g1.top().first;
					unvisited_g1.pop();
				}
				else{
					g2_node = unvisited_g2.top().first;
					unvisited_g2.pop();
				}
			}

			if(mapping_g1.find(g1_node) != mapping_g1.end() ||
			   mapping_g2.find(g2_node) != mapping_g2.end()){
				break;
			}
		}
		/////////////////////////////////////////// add_neighbours

		mcs_node = std::make_pair(g1_node, g2_node);

		mapping_g1.insert(std::make_pair(g1_node, mcs_node));
		mapping_g2.insert(std::make_pair(g2_node, mcs_node));

		g_mcs->add_node(mcs_node);

		for(unsigned int i = 0; i < g1.neighbours(g1_node).size(); i++){
			mapping_iterator = mapping_g1.find(g1.neighbours(g1_node)[i]);
			if(mapping_iterator != mapping_g1.end()){
				valid_mapping.insert(mapping_iterator->second);
			}
			else{
				/////////////////////////////////////////// add_neighbours
				if(add_neighbours){
					unvisited_unmapped_g1.push(std::make_pair(g1.neighbours(g1_node)[i],
					                           g1.degree(g1.neighbours(g1_node)[i])));
				}
				/////////////////////////////////////////// add_neighbours
			}
		}

		for(unsigned int i = 0; i < g2.neighbours(g2_node).size(); i++){
			mapping_iterator = mapping_g2.find(g2.neighbours(g2_node)[i]);
			if(mapping_iterator != mapping_g2.end() &&
			   valid_mapping.find(mapping_iterator->second) != valid_mapping.end()){
				g_mcs->add_edge(mcs_node, mapping_iterator->second);
			}
			else{
				/////////////////////////////////////////// add_neighbours
				if(add_neighbours && mapping_iterator == mapping_g2.end()){
					unvisited_unmapped_g2.push(std::make_pair(g2.neighbours(g2_node)[i],
					                           g2.degree(g2.neighbours(g2_node)[i])));
				}
				/////////////////////////////////////////// add_neighbours
			}
		}

		/////////////////////////////////////////// add_neighbours
		if(add_neighbours){
			while(!unvisited_unmapped_g1.empty() && !unvisited_unmapped_g2.empty()){
				g1_node_neighbour = unvisited_unmapped_g1.top().first;
				g2_node_neighbour = unvisited_unmapped_g2.top().first;

				unvisited_unmapped_g1.pop();
				unvisited_unmapped_g2.pop();

				mcs_node_neighbour = std::make_pair(g1_node_neighbour, g2_node_neighbour);

				mapping_g1.insert(std::make_pair(g1_node_neighbour, mcs_node_neighbour));
				mapping_g2.insert(std::make_pair(g2_node_neighbour, mcs_node_neighbour));

				g_mcs->add_node(mcs_node_neighbour);
				g_mcs->add_edge(mcs_node, mcs_node_neighbour);
			}

			unvisited_unmapped_g1 = clear_heap;
			unvisited_unmapped_g2 = clear_heap;
		}
		/////////////////////////////////////////// add_neighbours

		valid_mapping.clear();
	}

	return g_mcs;
}

solution run_solver(graph<int>& g1, graph<int>& g2){
	return solution();
}
