#ifndef GRAPH_FACTORY_H_
#define GRAPH_FACTORY_H_

#include "../structures/graph.h"
#include "element_generator.h"

template <typename T>
class graph_factory{
	public:
		static void add_n_random_vertices(graph<T> &g, element_generator<T>& e_gen, int n, float c);
		static adj_list_graph<int> co_graph_with_c_probability_edges(element_generator<T>& e_gen, int n, float c);
		static adj_list_graph<int> random_co_graph(element_generator<T> &e_gen, int n);
		static void add_n_vertices_and_all_edges(graph<T> &g, element_generator<T>& e_gen, int n);
};

template <typename T>
void graph_factory<T>::add_n_random_vertices(graph<T> &g, element_generator<T>& e_gen, int n, float c){
	T new_element = e_gen.generate(g);
	while(n > 0){
		g.add_node(new_element);
		float random_var = std::rand()*1.0f / RAND_MAX;
		for(unsigned int i = 0; i < g.get_vertices().size(); i++){
			if(random_var < c){
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
		if (prob_join < c){
			vec_g[i].join(vec_g[j],e_gen);
			// std::cout << "unite: " << std::endl << vec_g[i] << std::endl;
		}else{
			vec_g[i].unite(vec_g[j],e_gen);
			// std::cout << "join: " << std::endl << vec_g[i] << std::endl;
		}
		vec_g.erase ( vec_g.begin()+ j  );
		n--;
	}
	return vec_g[0];

}

#endif // GRAPH_FACTORY_H_INCLUDED
