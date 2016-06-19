#include "ej4.h"
#include "../mini_test.h"

std::ostream &operator<<(std::ostream& output, const std::pair<int, int>& p){
	output << "(" << p.first << ", " << p.second << ")";
	return output;
}

void test_path_mcs(){
	adj_list_graph<int> g1;
	g1.add_node(1);
	g1.add_node(2);
	g1.add_edge(1, 2);

	adj_list_graph<int> g2 = g1;

	graph< std::pair<int, int>> *g_mcs = solve(g1, g2);

	ASSERT_EQ(g_mcs->m(), 1);

	delete g_mcs;

	g1.add_node(3);
	g1.add_node(4);
	g1.add_edge(3, 4);

	g2 = g1;
	g2.add_edge(2, 3);

	g_mcs = solve(g1, g2);

	ASSERT_EQ(g_mcs->m(), 2);

	delete g_mcs;

	g1.add_node(5);
	g1.add_edge(2, 3);
	g1.add_edge(4, 5);

	g_mcs = solve(g1, g2);

	// example of a bad solution (chooses suboptimal mapping for path endings)
	ASSERT_EQ(g_mcs->m(), 1);

	delete g_mcs;
}

void test_path_mcs_alt(){
	adj_list_graph<int> g1;
	g1.add_node(1);
	g1.add_node(2);
	g1.add_edge(1, 2);

	adj_list_graph<int> g2 = g1;

	graph< std::pair<int, int>> *g_mcs = solve(g1, g2, true);

	ASSERT_EQ(g_mcs->m(), 1);

	delete g_mcs;

	g1.add_node(3);
	g1.add_node(4);
	g1.add_edge(3, 4);

	g2 = g1;
	g2.add_edge(2, 3);

	g_mcs = solve(g1, g2, true);

	ASSERT_EQ(g_mcs->m(), 1);

	delete g_mcs;

	g1.add_node(5);
	g1.add_edge(2, 3);
	g1.add_edge(4, 5);

	g_mcs = solve(g1, g2, true);

	ASSERT_EQ(g_mcs->m(), 3);

	delete g_mcs;
}

void test_star_mcs(){
	adj_list_graph<int> g1;
	g1.add_node(1);
	g1.add_node(2);
	g1.add_node(3);
	g1.add_node(4);
	g1.add_node(5);
	g1.add_node(6);

	adj_list_graph<int> g2 = g1;

	g1.add_edge(1, 2);
	g1.add_edge(1, 3);
	g1.add_edge(1, 4);
	g1.add_edge(2, 5);
	g1.add_edge(4, 6);

	g2.add_edge(2, 6);
	g2.add_edge(2, 5);
	g2.add_edge(2, 4);
	g2.add_edge(6, 1);
	g2.add_edge(4, 3);

	graph< std::pair<int, int>> *g_mcs = solve(g1, g2);

	ASSERT_EQ(g_mcs->m(), 2);

	delete g_mcs;
}

void test_star_mcs_alt(){
	adj_list_graph<int> g1;
	g1.add_node(1);
	g1.add_node(2);
	g1.add_node(3);
	g1.add_node(4);
	g1.add_node(5);
	g1.add_node(6);

	adj_list_graph<int> g2 = g1;

	g1.add_edge(1, 2);
	g1.add_edge(1, 3);
	g1.add_edge(1, 4);
	g1.add_edge(2, 5);
	g1.add_edge(4, 6);

	g2.add_edge(2, 6);
	g2.add_edge(2, 5);
	g2.add_edge(2, 4);
	g2.add_edge(6, 1);
	g2.add_edge(4, 3);

	graph< std::pair<int, int>> *g_mcs = solve(g1, g2, true);

	ASSERT_EQ(g_mcs->m(), 5);

	delete g_mcs;
}

void run_unit_tests(){
	RUN_TEST(test_path_mcs);
	RUN_TEST(test_path_mcs_alt);
	RUN_TEST(test_star_mcs);
	RUN_TEST(test_star_mcs_alt);
}
