#ifndef GRAPH_FACTORY_INT_H_
#define GRAPH_FACTORY_INT_H_

#include "graph_factory.h"

class graph_factory_int: public graph_factory<int>{
	private:
		int next_element(const graph<int> *g) const;
};

#endif // GRAPH_FACTORY_INT_H_INCLUDED
