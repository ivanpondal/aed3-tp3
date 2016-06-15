#include "../mini_test.h"
#include "test.h"
#include <sstream>

void test_adj_list_graph_add_nodes(){
	adj_list_graph<int> g;

	ASSERT_EQ(g.n(), 0);

	g.add_node(4);

	ASSERT_EQ(g.n(), 1);

	g.add_node(2);

	ASSERT_EQ(g.n(), 2);
}

void test_adj_list_graph_add_edges(){
	adj_list_graph<int> g;

	ASSERT_EQ(g.m(), 0);

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	ASSERT_EQ(g.m(), 0);

	g.add_edge(4, 2);

	ASSERT_EQ(g.m(), 1);

	ASSERT(g.adjacent(4, 2));
}

void test_adj_list_graph_neighbours(){
	adj_list_graph<int> g;

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

void test_adj_list_graph_degree(){
	adj_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	g.add_edge(4, 2);
	g.add_edge(3, 2);

	ASSERT_EQ(g.degree(4), 1);
	ASSERT_EQ(g.degree(3), 1);
	ASSERT_EQ(g.degree(2), 2);
}

void test_adj_list_graph_istream(){
	adj_list_graph<int> g;

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

void test_adj_list_graph_contains(){
	adj_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	ASSERT(g.contains(4));
	ASSERT(g.contains(2));
	ASSERT(g.contains(3));
	ASSERT(!g.contains(7));
}

void test_adj_list_graph_clone(){
	adj_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	g.add_edge(4, 2);
	g.add_edge(3, 2);

	graph<int> *g_clone = g.clone();

	ASSERT(g_clone->contains(4));
	ASSERT(g_clone->contains(2));
	ASSERT(g_clone->contains(3));

	ASSERT(g_clone->adjacent(4, 2));
	ASSERT(g_clone->adjacent(3, 2));

	ASSERT_EQ(g_clone->n(), 3);
	ASSERT_EQ(g_clone->m(), 2);

	delete g_clone;
}

void test_adj_list_graph_vertices(){
	adj_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(3);

	std::vector<int> expected = {4, 2, 3};

	ASSERT(g.get_vertices() == expected);
}

void test_adj_list_n_incremental_experiment(){
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> input_exp(1, 100000, 0, 60, 1000, adj_list_graph<int>());

	adj_list_n_incremental_experiment exp(&input_exp);

	exp.run();
}

void test_adj_list_n_incremental_experiment_suite(){
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> exp1_input(1, 100000, 0, 60, 1000, adj_list_graph<int>());
	incremental_experiment_input_int< adj_list_graph<int>> exp2_input(1, 100, 20, 60, 50, adj_list_graph<int>());

	adj_list_n_incremental_experiment exp1 = adj_list_n_incremental_experiment(&exp1_input);
	adj_list_n_incremental_experiment exp2 = adj_list_n_incremental_experiment(&exp2_input);

	experiment_suite exp_suite;

	exp_suite.add(&exp1);
	exp_suite.add(&exp2);

	exp_suite.run();
}

int main(){
	// adj_list_graph tests
	RUN_TEST(test_adj_list_graph_add_nodes);
	RUN_TEST(test_adj_list_graph_add_edges);
	RUN_TEST(test_adj_list_graph_neighbours);
	RUN_TEST(test_adj_list_graph_degree);
	RUN_TEST(test_adj_list_graph_istream);
	RUN_TEST(test_adj_list_graph_contains);
	RUN_TEST(test_adj_list_graph_clone);
	RUN_TEST(test_adj_list_graph_vertices);

	// experiment tests
	RUN_TEST(test_adj_list_n_incremental_experiment);
	RUN_TEST(test_adj_list_n_incremental_experiment_suite);
}
