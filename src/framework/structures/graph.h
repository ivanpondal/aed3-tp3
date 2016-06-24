#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>

template <typename T>
class element_generator;

template <typename T>
class graph{
	public:
		virtual ~graph(){};
			virtual unsigned int n() const = 0;
		virtual unsigned int m() const = 0;
		virtual const std::vector<T> &neighbours(const T &v) const = 0;
		virtual unsigned int degree(const T &v) const = 0;
		virtual bool adjacent(const T &v1, const T &v2) const = 0;
		virtual void add_node(const T &v) = 0;
		virtual void remove_node(const T &v) = 0;
		virtual void add_edge(const T &v1, const T &v2) = 0;
		virtual bool contains(const T &v) const = 0;
		virtual graph<T> *clone() const = 0;
		virtual void join(const graph<T> &g, element_generator<T> &ele_g) = 0;
		virtual void unite(const graph<T> &g, element_generator<T> &ele_g) = 0;
		virtual const std::vector<T> &get_vertices() const = 0;
		graph<T> &operator=(const graph<T> &g);
	private:
		virtual void clear() = 0;
};

template <typename T>
std::ostream &operator<<(std::ostream &output, graph<T> &g){
	T tmp_node_val = T();
	for(unsigned int n = 0; n < g.get_vertices().size(); n++){
		tmp_node_val = g.get_vertices()[n];
		output << tmp_node_val << ":";
		for(unsigned int i = 0; i < g.neighbours(tmp_node_val).size(); i++){
			output << " " << g.neighbours(tmp_node_val)[i];
		}
		output << std::endl;
	}

	return output;
}

template <typename T>
std::istream &operator>>(std::istream &input, graph<T> &g){
	int m = 0;
	input >> m >> m;

	T tmp_a, tmp_b;

	for(int i = 0; i < m; i++){
		input >> tmp_a >> tmp_b;
		if(!g.contains(tmp_a)){
			g.add_node(tmp_a);
		}
		if(!g.contains(tmp_b)){
			g.add_node(tmp_b);
		}
		g.add_edge(tmp_a, tmp_b);
	}

	return input;
}

template <typename T>
graph<T> &graph<T>::operator=(const graph<T> &g){
	clear();

	for(unsigned int n = 0; n < g.get_vertices().size(); n++){
		add_node(g.get_vertices()[n]);
	}

	T tmp_val = T();
	for(unsigned int n = 0; n < get_vertices().size(); n++){
		tmp_val = get_vertices()[n];
		for(unsigned int i = 0; i < g.neighbours(tmp_val).size(); i++){
			if(!adjacent(tmp_val, g.neighbours(tmp_val)[i])){
				add_edge(tmp_val, g.neighbours(tmp_val)[i]);
			}
		}
	}

	return *this;
}
#endif // GRAPH_H_INCLUDED
