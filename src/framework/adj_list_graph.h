#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

#include <unordered_map>
#include "graph.h"

template <typename T>
class adj_list_graph: public graph<T>{
	public:
		adj_list_graph();
		~adj_list_graph();
		unsigned int n() const;
		unsigned int m() const;
		const std::vector<T> &neighbours(const T &v) const;
		unsigned int degree(const T &v) const;
		bool adjacent(const T &v1, const T &v2) const;
		void add_node(const T &v);
		void add_edge(const T &v1, const T &v2);
		bool contains(const T &v) const;
		adj_list_graph<T> *clone() const;
		friend std::istream &operator>>(std::istream &input, adj_list_graph &g){
			input >> g.n_val >> g.m_val;

			T tmp_a, tmp_b;

			for(unsigned int i = 0; i < g.m_val; i++){
				input >> tmp_a >> tmp_b;
				g.adj_list[tmp_a].push_back(tmp_b);
				g.adj_list[tmp_b].push_back(tmp_a);
			}

			return input;
		};
	private:
		unsigned int n_val;
		unsigned int m_val;
		std::unordered_map<T, std::vector<T>> adj_list;
};

template <typename T>
adj_list_graph<T>::adj_list_graph(){
	n_val = 0;
	m_val = 0;
}

template <typename T>
adj_list_graph<T>::~adj_list_graph(){
}

template <typename T>
unsigned int adj_list_graph<T>::n() const{
	return n_val;
}

template <typename T>
unsigned int adj_list_graph<T>::m() const{
	return m_val;
}

template <typename T>
const std::vector<T> &adj_list_graph<T>::neighbours(const T &v) const{
	return adj_list.at(v);
}

template <typename T>
unsigned int adj_list_graph<T>::degree(const T &v) const{
	return adj_list.at(v).size();
}

template <typename T>
bool adj_list_graph<T>::adjacent(const T &v1, const T &v2) const{

	for(unsigned int i = 0; i < degree(v1); i++){
		if(neighbours(v1)[i] == v2){
			return true;
		}
	}

	return false;
}

template <typename T>
void adj_list_graph<T>::add_node(const T &v){
	adj_list.insert(std::make_pair(v, std::vector<int>()));
	n_val++;
}

template <typename T>
void adj_list_graph<T>::add_edge(const T &v1, const T &v2){
	adj_list[v1].push_back(v2);
	adj_list[v2].push_back(v1);
	m_val++;
}

template <typename T>
bool adj_list_graph<T>::contains(const T &v) const{
	return adj_list.find(v) != adj_list.end();
}

template <typename T>
adj_list_graph<T> *adj_list_graph<T>::clone() const{
	return new adj_list_graph<T>(*this);
}

#endif // ADJ_LIST_GRAPH_H_INCLUDED
