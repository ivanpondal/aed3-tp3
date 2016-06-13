#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>

template <typename T>
class graph{
	public:
		virtual unsigned int n() const = 0;
		virtual unsigned int m() const = 0;
		virtual const std::vector<T> &neighbours(const T &v) const = 0;
		virtual unsigned int degree(const T &v) const = 0;
		virtual bool adjacent(const T &v1, const T &v2) const = 0;
		virtual void add_node(const T &v) = 0;
		virtual void add_edge(const T &v1, const T &v2) = 0;
        virtual bool contains(const T &v) const = 0;
        virtual std::vector<T> nodes() const = 0;
		virtual graph<T>* complement() const = 0;
};

#endif // GRAPH_H_INCLUDED