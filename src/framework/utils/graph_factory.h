#ifndef GRAPH_FACTORY_H_
#define GRAPH_FACTORY_H_

#include "../structures/graph.h"
#include "element_generator.h"

template <typename T>
class graph_factory{
	public:
		static void add_n_random_vertices(graph<T> &g, element_generator<T>& e_gen, int n, float c);
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

#endif // GRAPH_FACTORY_H_INCLUDED
