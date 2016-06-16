#include "graph_factory_int.h"

int graph_factory_int::next_element(const graph<int> *g) const{
	int candidate = 0;
	if(g->n() > 0){
		candidate = g->n();
		while (g->contains(candidate)){
			candidate++;
		}
	}
	return candidate;
}
