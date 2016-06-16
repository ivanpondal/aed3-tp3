#ifndef GRAPH_FACTORY_H_
#define GRAPH_FACTORY_H_

#include "../structures/graph.h"

template <typename T>
class graph_factory{
	public:
		void add_n_random_vertices(graph<T> *g, int n, float c) const;
	private:
		virtual T next_element(const graph<T> *g) const;
};

template <typename T>
void graph_factory<T>::add_n_random_vertices(graph<T> *g, int n, float c) const{
	T new_element = next_element(g);
	while(n > 0){
		g->add_node(new_element);
		float random_var = std::rand()*1.0f / RAND_MAX;
		for(unsigned int i = 0; i < g->get_vertices().size(); i++){
			if(random_var < c){
				if(!g->adjacent(new_element, g->get_vertices()[i]) && new_element != g->get_vertices()[i]){
					g->add_edge(new_element, g->get_vertices()[i]);
				}
			}
			random_var = std::rand()*1.0f / RAND_MAX;
		}
		new_element = next_element(g);
		n--;
	}
}

#endif // GRAPH_FACTORY_H_INCLUDED
