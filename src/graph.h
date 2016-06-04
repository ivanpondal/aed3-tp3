#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>

class graph{
	public:
		virtual int n;
		virtual int m;
		virtual std::vector<int> neighbours(int n);
		virtual int degree(int n);
		virtual bool adjacent(int n1, int n2);
		virtual int add_node();
		virtual void add_edge(int n1, int n2);
		virtual friend &operator<<(std::ostream &output, const &graph);
}

#endif // GRAPH_H_INCLUDED
