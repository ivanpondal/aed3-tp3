#include "./ej6.h"
#include "../mini_test.h"
#include "../framework/structures/adj_list_graph.h"

/*
**  Exercise 6
**  Unit tests
*/

using namespace std;

void test_tree_improvement_1() {
	element_generator_int e_gen;
	graph<std::pair<int, int>>* start_point; graph<std::pair<int, int>>* h;
	adj_list_graph<int> g1, g2;

	graph_factory<int>::add_n_tree_vertices(g1, e_gen, 100);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, 200);

	start_point = solve_greedy(g1, g2);

	std::cout << std::endl << "GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges\n";
	ASSERT(check_solution(pairs_to_solution(*start_point), g1, g2));

	h = solve_tabu(g1, g2, *start_point, 1, 10, -1, 1, true, 1000, 0.3, 0.1, 0.7);

	std::cout << "TABU: " << h->n() << " nodes, " << h->m() << " edges\n";
	ASSERT(check_solution(pairs_to_solution(*h), g1, g2));

	delete start_point;
	delete h;
}

void test_tree_improvement_2() {
	element_generator_int e_gen;
	graph<std::pair<int, int>>* start_point; graph<std::pair<int, int>>* h;
	adj_list_graph<int> g1, g2;

	graph_factory<int>::add_n_tree_vertices(g1, e_gen, 100);
	e_gen.reset();
	graph_factory<int>::add_n_tree_vertices(g2, e_gen, 200);

	start_point = solve_greedy(g1, g2);

	std::cout << std::endl << "GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges\n";
	ASSERT(check_solution(pairs_to_solution(*start_point), g1, g2));

	h = solve_tabu(g1, g2, *start_point, 2, 10, -1, 1, true, 1000, 0.3, 0.1, 0.7);

	std::cout << "TABU: " << h->n() << " nodes, " << h->m() << " edges\n";
	ASSERT(check_solution(pairs_to_solution(*h), g1, g2));

	delete start_point;
	delete h;
}

void run_unit_tests() {
	srand(42);

	RUN_TEST(test_tree_improvement_1);
	RUN_TEST(test_tree_improvement_2);
}
