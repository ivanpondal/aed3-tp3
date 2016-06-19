#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

#include <unordered_map>
#include "graph.h"

template <typename T, typename H = std::hash<T>>
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
		graph<T> *clone() const;
		void join(const graph<T> &g);
		void unite(const graph<T> &g);
		const std::vector<T> &get_vertices() const;
	private:
		void clear();
		unsigned int n_val;
		unsigned int m_val;
		std::unordered_map<T, std::vector<T>, H> adj_list;
		std::vector<T> vertices_list;
};

template <typename T, typename H>
adj_list_graph<T, H>::adj_list_graph(){
	n_val = 0;
	m_val = 0;
}

template <typename T, typename H>
adj_list_graph<T, H>::~adj_list_graph(){
}

template <typename T, typename H>
unsigned int adj_list_graph<T, H>::n() const{
	return n_val;
}

template <typename T, typename H>
unsigned int adj_list_graph<T, H>::m() const{
	return m_val;
}

template <typename T, typename H>
const std::vector<T> &adj_list_graph<T, H>::neighbours(const T &v) const{
	return adj_list.at(v);
}

template <typename T, typename H>
unsigned int adj_list_graph<T, H>::degree(const T &v) const{
	return adj_list.at(v).size();
}

template <typename T, typename H>
bool adj_list_graph<T, H>::adjacent(const T &v1, const T &v2) const{

	for(unsigned int i = 0; i < degree(v1); i++){
		if(neighbours(v1)[i] == v2){
			return true;
		}
	}

	return false;
}

template <typename T, typename H>
void adj_list_graph<T, H>::add_node(const T &v){
	adj_list.insert(std::make_pair(v, std::vector<T>()));
	vertices_list.push_back(v);
	n_val++;
}

template <typename T, typename H>
void adj_list_graph<T, H>::add_edge(const T &v1, const T &v2){
	adj_list[v1].push_back(v2);
	adj_list[v2].push_back(v1);
	m_val++;
}

template <typename T, typename H>
bool adj_list_graph<T, H>::contains(const T &v) const{
	return adj_list.find(v) != adj_list.end();
}

template <typename T, typename H>
graph<T> *adj_list_graph<T, H>::clone() const{
	return new adj_list_graph<T, H>(*this);
}

template <typename T, typename H>
void adj_list_graph<T, H>::join(const graph<T> &g){
	// MAXI COMPLETAME
}

template <typename T, typename H>
void adj_list_graph<T, H>::unite(const graph<T> &g){
	// MAXI COMPLETAME
}


template <typename T, typename H>
const std::vector<T> &adj_list_graph<T, H>::get_vertices() const{
	return vertices_list;
}

template <typename T, typename H>
void adj_list_graph<T, H>::clear(){
	n_val = 0;
	m_val = 0;
	adj_list.clear();
	vertices_list.clear();
}

#endif // ADJ_LIST_GRAPH_H_INCLUDED
