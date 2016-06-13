#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

#include <unordered_map>
#include "graph.h"

template <typename T>
class adj_list_graph: public graph<T>{
	public:
		adj_list_graph();
		unsigned int n() const;
		unsigned int m() const;
		const std::vector<T> &neighbours(const T &v) const;
		unsigned int degree(const T &v) const;
		bool adjacent(const T &v1, const T &v2) const;
		void add_node(const T &v);
		void add_edge(const T &v1, const T &v2);
		bool contains(const T &v) const;
		std::vector<T> nodes() const;
		adj_list_graph<T>* complement() const;
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
		std::vector<T> node_list;
};

template <typename T>
adj_list_graph<T>::adj_list_graph(){
	n_val = 0;
	m_val = 0;
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
	node_list.push_back(v);
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
	//return std::equal(adj_list.find(v), std::unordered_map<T, std::vector<T>>::end);
	return true;
}

template <typename T>
std::vector<T> adj_list_graph<T>::nodes() const {
	return node_list;
}

template <typename T>
adj_list_graph<T>* adj_list_graph<T>::complement() const{
	adj_list_graph<T>* ret = new adj_list_graph<T>();

	for (typename std::vector<T>::const_iterator it1 = node_list.begin();
		it1 != node_list.end();
		it1++)
	{
		T current_node1 = *it1;
		ret->add_node(current_node1);
		for (typename std::vector<T>::const_iterator it2 = node_list.begin();
			it2 != node_list.end();
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


#endif // ADJ_LIST_GRAPH_H_INCLUDED
