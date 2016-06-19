#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
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
		graph<T> *clone() const;
		void join(const graph<T> &g, element_generator<T> &e_gen);
		void unite(const graph<T> &g, element_generator<T> &e_gen);
		const std::vector<T> &get_vertices() const;
		adj_list_graph<T>* complement() const;
		adj_list_graph<T>* induced_supgraph(std::vector<int> subgraph_vertices) const;
	private:
		void clear();
		unsigned int n_val;
		unsigned int m_val;
		std::unordered_map<T, std::vector<T>> adj_list;
		std::vector<T> vertices_list;
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
	vertices_list.push_back(v);
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
graph<T> *adj_list_graph<T>::clone() const{
	return new adj_list_graph<T>(*this);
}

template <typename T>
void adj_list_graph<T>::join(const graph<T> &g,  element_generator<T> &e_gen){
	std::unordered_map<T,T> g2_to_g1;
	std::unordered_set<T> g1_new_nodes;
	// union
	for (int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T new_v = e_gen.generate(*this);
		g2_to_g1.insert(std::make_pair(v, new_v ));
		g1_new_nodes.insert(new_v);
		add_node(new_v);
	}
	for (int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T v_in_g1 = g2_to_g1.at(v);
		std::vector<T> neighbours = g.neighbours(v);
		for (int j = 0; j < neighbours.size(); ++j){
			T neighbour_v_in_g1 = g2_to_g1.at(neighbours[j]);
			if ( ( v_in_g1 != neighbour_v_in_g1 ) && (! adjacent(v_in_g1, neighbour_v_in_g1) ) ){
				add_edge(v_in_g1,neighbour_v_in_g1);
			}	
		}
	}
	//std::cout << " add others egdes ..." << std::endl;
	// add others egdes 
	for (int i = 0; i < g.n(); ++i){
		T v_g2 = g.get_vertices()[i];
		T v_g2_in_g1 = g2_to_g1.at(v_g2);
		//std::cout << "v_g2_in_g1 :" << v_g2 << " -> " << v_g2_in_g1 << std::endl;
		for (int j = 0; j < n(); ++j){
			T v_g1 = get_vertices()[j];
			//std::cout << "v_g1 :" << v_g1 << std::endl;
			if(g1_new_nodes.find(v_g1) == g1_new_nodes.end()){
				if ( v_g2_in_g1 != v_g1 && ! adjacent(v_g2_in_g1, v_g1 ) ){
					//std::cout << "add_edge :" << v_g2_in_g1 << " -> " << v_g1 << std::endl;
					add_edge(v_g2_in_g1,v_g1);
				}
			}
		}
	}



}

template <typename T>
void adj_list_graph<T>::unite(const graph<T> &g,  element_generator<T> &e_gen){
	std::unordered_map<T,T> g2_to_g1;
	// add new nodes
	for (int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T new_v = e_gen.generate(*this);
		g2_to_g1.insert(std::make_pair(v, new_v ));
		add_node(new_v);
	}
	// add news edge
	for (int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T v_in_g1 = g2_to_g1.at(v);
		std::vector<T> neighbours = g.neighbours(v);
		for (int j = 0; j < neighbours.size(); ++j){
			T neighbour_v_in_g1 = g2_to_g1.at(neighbours[j]);
			if ( ( v_in_g1 != neighbour_v_in_g1 ) && (! adjacent(v_in_g1, neighbour_v_in_g1) ) ){
				add_edge(v_in_g1,neighbour_v_in_g1);
			}
			
		}
	}
}


template <typename T>
const std::vector<T> &adj_list_graph<T>::get_vertices() const{
	return vertices_list;
}

template <typename T>
adj_list_graph<T>* adj_list_graph<T>::complement() const{
	adj_list_graph<T>* ret = new adj_list_graph<T>();

	for (typename std::vector<T>::const_iterator it1 = vertices_list.begin();
		it1 != vertices_list.end();
		it1++)
	{
		T current_node1 = *it1;
		ret->add_node(current_node1);
		for (typename std::vector<T>::const_iterator it2 = vertices_list.begin();
			it2 != vertices_list.end();
			it2++)
		{
			T current_node2 = *it2;
			if (current_node1 != current_node2 &&
				! adjacent(current_node1, current_node2))
			{
				ret->add_edge(current_node1, current_node2);
			}
		}

	}

	return ret;
};

template <typename T>
adj_list_graph<T>* adj_list_graph<T>::induced_supgraph(std::vector<int> subgraph_vertices) const {
	adj_list_graph<T>* ret = new adj_list_graph<T>();
	std::unordered_map<int, int> mapping;

	int i = 0;
	for (typename std::vector<T>::const_iterator it1 = subgraph_vertices.begin();
		it1 != subgraph_vertices.end();
		it1++)
	{
		mapping.insert(std::make_pair(*it1, i));
		ret->add_node(i);
		i++;
	}

	for (typename std::vector<T>::const_iterator it1 = subgraph_vertices.begin();
		it1 != subgraph_vertices.end();
		it1++)
	{
		i = mapping[*it1];
		std::vector<T> neigh = neighbours(*it1);

		for (typename std::vector<T>::const_iterator it2 = neigh.begin();
			it2 != neigh.end();
			it2++)
		{
			if (mapping.find(*it2) != mapping.end()) {
				int j = mapping[*it2];
				ret->add_edge(i, j);				
			}
		}

		mapping.erase(*it1);
	}

	return ret;
}

template <typename T>
void adj_list_graph<T>::clear(){
	n_val = 0;
	m_val = 0;
	adj_list.clear();
	vertices_list.clear();
}

#endif // ADJ_LIST_GRAPH_H_INCLUDED
