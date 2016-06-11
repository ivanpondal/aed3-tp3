#include "../mini_test.h"
#include "ady_list_graph.h"
#include <sstream>

void test_ady_list_graph_add_nodes(){
	ady_list_graph<int> g;

	ASSERT_EQ(g.n(), 0);

	g.add_node(4);

	ASSERT_EQ(g.n(), 1);

	g.add_node(2);

	ASSERT_EQ(g.n(), 2);
}

void test_ady_list_graph_add_edges(){
	ady_list_graph<int> g;

	ASSERT_EQ(g.m(), 0);

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	ASSERT_EQ(g.m(), 0);

	g.add_edge(4, 2);

	ASSERT_EQ(g.m(), 1);

	ASSERT(g.adjacent(4, 2));
}

void test_ady_list_graph_neighbours(){
	ady_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	ASSERT_EQ(g.m(), 0);

	g.add_edge(4, 2);
	g.add_edge(4, 3);

	ASSERT(g.adjacent(4, 2));
	ASSERT(g.adjacent(4, 3));
	ASSERT(!g.adjacent(2, 3));

	std::vector<int> expected = {2, 3};
	ASSERT(g.neighbours(4) == expected);
}

void test_ady_list_graph_degree(){
	ady_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	g.add_edge(4, 2);
	g.add_edge(3, 2);

	ASSERT_EQ(g.degree(4), 1);
	ASSERT_EQ(g.degree(3), 1);
	ASSERT_EQ(g.degree(2), 2);
}

void test_ady_list_graph_istream(){
	ady_list_graph<int> g;

	std::stringstream iss;
	iss << "5 4\n1 2\n2 3\n3 4\n3 5";

	iss >> g;

	ASSERT_EQ(g.n(), 5);
	ASSERT_EQ(g.m(), 4);

	ASSERT(g.adjacent(2, 1));
	ASSERT(g.adjacent(3, 2));
	ASSERT(g.adjacent(3, 4));
	ASSERT(g.adjacent(3, 5));

	std::vector<int> expected = {2, 4, 5};
	ASSERT(g.neighbours(3) == expected);
}

int main(){
	RUN_TEST(test_ady_list_graph_add_nodes);
	RUN_TEST(test_ady_list_graph_add_edges);
	RUN_TEST(test_ady_list_graph_neighbours);
	RUN_TEST(test_ady_list_graph_degree);
	RUN_TEST(test_ady_list_graph_istream);
}
