#ifndef GRAPH_FACTORY_H_
#define GRAPH_FACTORY_H_

#include "../structures/graph.h"
#include "element_generator.h"

template <typename T>
class graph_factory{
	public:
		// incremental graph generators
		static void add_n_random_vertices(graph<T> &g, element_generator<T>& e_gen, int n, float c);
		static void add_n_tree_vertices(graph<T> &g, element_generator<T>& e_gen, int n);
		static void add_n_vertices_and_all_edges(graph<T> &g, element_generator<T>& e_gen, int n);
		static void add_n_path_vertices(graph<T> &g, element_generator<T>& e_gen, int n);

		// full graph generators
		static adj_list_graph<T> random_bipartite_graph(element_generator<T>& e_gen, int n, int k, float c);
		static adj_list_graph<T> cycle_graph(element_generator<T>& e_gen, int n);
		static adj_list_graph<T> random_disconnected_graph(element_generator<T>& e_gen, int n, int d, float c, float v = 0);
		static adj_list_graph<int> co_graph_with_c_probability_edges(element_generator<T>& e_gen, int n, float c);
		static adj_list_graph<int> random_co_graph(element_generator<T> &e_gen, int n);
};

// incremental graph generators

template <typename T>
void graph_factory<T>::add_n_random_vertices(graph<T> &g, element_generator<T>& e_gen, int n, float c){
	T new_element = e_gen.generate(g);
	while(n > 0){
		g.add_node(new_element);
		float random_var = std::rand()*1.0f / RAND_MAX;
		for(unsigned int i = 0; i < g.get_vertices().size(); i++){
			if(random_var <= c){
				if(!g.adjacent(new_element, g.get_vertices()[i]) && new_element != g.get_vertices()[i]){
					g.add_edge(new_element, g.get_vertices()[i]);
				}
			}
			random_var = std::rand()*1.0f / RAND_MAX;
		}
		new_element = e_gen.generate(g);
		n--;
	}
}

template <typename T>
void graph_factory<T>::add_n_tree_vertices(graph<T> &g, element_generator<T>& e_gen, int n){
	T new_element = e_gen.generate(g);

	if(g.n() == 0){
		g.add_node(new_element);

		new_element = e_gen.generate(g);
		n--;
	}

	while(n > 0){
		int random_var = std::rand() % g.n();

		g.add_node(new_element);
		g.add_edge(new_element, g.get_vertices()[random_var]);

		new_element = e_gen.generate(g);
		n--;
	}
}

template <typename T>
void graph_factory<T>::add_n_vertices_and_all_edges(graph<T> &g, element_generator<T>& e_gen, int n){
	T new_node;
	while(n > 0){
		new_node = e_gen.generate(g);
		g.add_node(new_node);
		for (unsigned int i = 0; i < g.n(); ++i){
			T node = g.get_vertices()[i];
			if (node != new_node){
				g.add_edge(node, new_node);
			}
		}
		n--;
	}
}

template <typename T>
void graph_factory<T>::add_n_path_vertices(graph<T> &g, element_generator<T>& e_gen, int n) {
	T new_node;
	T tail_node;

	if (g.n() > 0) {
		tail_node = g.get_vertices()[g.n() - 1];
	}

	while(n > 0){
		new_node = e_gen.generate(g);
		g.add_node(new_node);
		if (g.n() > 1) {
			g.add_edge(new_node, tail_node);
		}
		tail_node = new_node;
		n--;
	}
}

// full graph generators

template <typename T>
adj_list_graph<T> graph_factory<T>::random_bipartite_graph(element_generator<T>& e_gen, int n, int k, float c){
	adj_list_graph<T> g;

	T new_element = e_gen.generate(g);

	for(int i = 0; i < n + k; i++){
		g.add_node(new_element);
		new_element = e_gen.generate(g);
	}

	for(int i = 0; i < n; i++){
		float random_var = 0;
		for(int j = 0; j < k; j++){
			random_var = std::rand()*1.0f / RAND_MAX;
			if(random_var <= c){
				g.add_edge(g.get_vertices()[i], g.get_vertices()[n + j]);
			}
		}
	}

	return g;
}

template <typename T>
adj_list_graph<T> graph_factory<T>::cycle_graph(element_generator<T>& e_gen, int n){
	adj_list_graph<T> g;

	T new_element = e_gen.generate(g);

	T previous_element = new_element;
	T first_element = new_element;

	g.add_node(new_element);
	n--;

	while(n > 0){
		new_element = e_gen.generate(g);

		g.add_node(new_element);
		g.add_edge(new_element, previous_element);

		previous_element = new_element;
		n--;
	}

	g.add_edge(previous_element, first_element);

	return g;
}

template <typename T>
adj_list_graph<T> graph_factory<T>::random_disconnected_graph(element_generator<T>& e_gen, int n, int d, float c, float v){
	adj_list_graph<T> g;

	std::vector<int> partition_size = std::vector<int>(d, 0);

	int remaining_partition = n;
	int partition = 0;

	// precalculate component sizes

	float random_var = std::rand()*v / RAND_MAX;

	for(int i = 0; i < d; i++){
		partition = remaining_partition / (d - i);

		partition_size[i] = partition + (remaining_partition - partition - d + i + 1)*random_var;

		remaining_partition -= partition_size[i];

		random_var = std::rand()*v / RAND_MAX;
	}

	// add edges to each component

	int partition_offset = 0;
	int partition_random_node = 0;
	T new_element = e_gen.generate(g);

	for(int i = 0; i < d; i++){
		g.add_node(new_element);

		new_element = e_gen.generate(g);
		for(int j = 1; j < partition_size[i]; j++){
			partition_random_node = partition_offset + std::rand() % j;

			g.add_node(new_element);
			g.add_edge(new_element, g.get_vertices()[partition_random_node]);

			random_var = std::rand()*1.0f / RAND_MAX;
			for(int k = partition_offset; k < partition_offset + j; k++){
				if(random_var <= c && k != partition_random_node){
					g.add_edge(new_element, g.get_vertices()[k]);
				}
				random_var = std::rand()*1.0f / RAND_MAX;
			}
			new_element = e_gen.generate(g);
		}
		partition_offset += partition_size[i];
	}

	return g;
}

template <typename T>
adj_list_graph<int> graph_factory<T>::random_co_graph(element_generator<T> &e_gen, int n){
	// genero n grafos triviales
	std::vector < adj_list_graph<int> > vec_g (
		n,
		adj_list_graph<int>()
	);
	for (int i = 0; i < n; ++i){
		vec_g[i].add_node(0);
	}

	while(n > 1){
		e_gen.reset();
		int i;
		int j;
		do{
			i = rand() % n ;
			j = rand() % n ;
		}while(i == j);
		// std::cout << "i: " << i << std::endl << vec_g[i] << std::endl;
		// std::cout << "j: " << j << std::endl << vec_g[j] << std::endl;
		int unite_o_join = rand() % 2 ;
		if (unite_o_join == 0){
			vec_g[i].unite(vec_g[j],e_gen);
			// std::cout << "unite: " << std::endl << vec_g[i] << std::endl;
		}else{
			vec_g[i].join(vec_g[j],e_gen);
			// std::cout << "join: " << std::endl << vec_g[i] << std::endl;
		}
		vec_g.erase ( vec_g.begin()+ j  );
		n--;
	}
	return vec_g[0];
}

template <typename T>
adj_list_graph<int> graph_factory<T>::co_graph_with_c_probability_edges
	(element_generator<T>& e_gen, int n, float c){

	// genero n grafos triviales
	std::vector < adj_list_graph<int> > vec_g (
		n,
		adj_list_graph<int>()
	);
	for (int i = 0; i < n; ++i){
		vec_g[i].add_node(0);
	}

	int expected_joins = (int) ( ((float) n )* c); 
	int joins = 0; 

	while(n > 1){
		e_gen.reset();
		int i;
		int j;
		do{
			i = rand() % n ;
			j = rand() % n ;
		}while(i == j);
		// std::cout << "i: " << i << std::endl << vec_g[i] << std::endl;
		// std::cout << "j: " << j << std::endl << vec_g[j] << std::endl;
		float prob_join = std::rand()*1.0f / RAND_MAX;
		if (prob_join <= c){
			vec_g[i].join(vec_g[j],e_gen);
			// std::cout << "unite: " << std::endl << vec_g[i] << std::endl;
			joins ++ ;
		}else{
			vec_g[i].unite(vec_g[j],e_gen);
			// std::cout << "join: " << std::endl << vec_g[i] << std::endl;
		}
		vec_g.erase ( vec_g.begin()+ j  );
		n--;
	}
	std::cout << "cantidad de joins echos : " << joins << std::endl;
	std::cout << "cantidad de joins esperados : " << expected_joins << std::endl;
	return vec_g[0];

}

#endif // GRAPH_FACTORY_H_INCLUDED
