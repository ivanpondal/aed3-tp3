#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>  // std::find

#include "../utils/element_generator.h"

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
		void remove_node(const T &v);
		bool contains(const T &v) const;
		graph<T> *clone() const;
		void join(const graph<T> &g, element_generator<T> &e_gen);
		void unite(const graph<T> &g, element_generator<T> &e_gen);
		const std::vector<T> &get_vertices() const;
		void clear();
	private:
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
void adj_list_graph<T, H>::remove_node(const T &v) {
	n_val--;
	m_val -= degree(v);

	for (unsigned int i = 0; i < degree(v); i++) {
		adj_list[adj_list[v][i]].erase(
			find(
				adj_list[adj_list[v][i]].begin(),
				adj_list[adj_list[v][i]].end(),
				v
			)
		);
	}
	adj_list.erase(v);
	vertices_list.erase(std::find(vertices_list.begin(), vertices_list.end(), v));
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
void adj_list_graph<T, H>::join(const graph<T> &g, element_generator<T> &e_gen){
	std::unordered_map<T, T, H> g2_to_g1;
	std::unordered_set<T, H> g1_new_nodes;
	// union
	for (unsigned int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T new_v = e_gen.generate(*this);
		g2_to_g1.insert(std::make_pair(v, new_v ));
		g1_new_nodes.insert(new_v);
		add_node(new_v);
	}
	for (unsigned int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T v_in_g1 = g2_to_g1.at(v);
		std::vector<T> neighbours = g.neighbours(v);
		for (unsigned int j = 0; j < neighbours.size(); ++j){
			T neighbour_v_in_g1 = g2_to_g1.at(neighbours[j]);
			if ( ( v_in_g1 != neighbour_v_in_g1 ) && (! adjacent(v_in_g1, neighbour_v_in_g1) ) ){
				add_edge(v_in_g1,neighbour_v_in_g1);
			}
		}
	}
	//std::cout << " add others egdes ..." << std::endl;
	// add others egdes
	for (unsigned int i = 0; i < g.n(); ++i){
		T v_g2 = g.get_vertices()[i];
		T v_g2_in_g1 = g2_to_g1.at(v_g2);
		//std::cout << "v_g2_in_g1 :" << v_g2 << " -> " << v_g2_in_g1 << std::endl;
		for (unsigned int j = 0; j < n(); ++j){
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

template <typename T, typename H>
void adj_list_graph<T, H>::unite(const graph<T> &g, element_generator<T> &e_gen){
	std::unordered_map<T, T, H> g2_to_g1;
	// add new nodes
	for (unsigned int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T new_v = e_gen.generate(*this);
		g2_to_g1.insert(std::make_pair(v, new_v ));
		add_node(new_v);
	}
	// add news edge
	for (unsigned int i = 0; i < g.n(); ++i){
		T v = g.get_vertices()[i];
		T v_in_g1 = g2_to_g1.at(v);
		std::vector<T> neighbours = g.neighbours(v);
		for (unsigned int j = 0; j < neighbours.size(); ++j){
			T neighbour_v_in_g1 = g2_to_g1.at(neighbours[j]);
			if ( ( v_in_g1 != neighbour_v_in_g1 ) && (! adjacent(v_in_g1, neighbour_v_in_g1) ) ){
				add_edge(v_in_g1,neighbour_v_in_g1);
			}

		}
	}
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
