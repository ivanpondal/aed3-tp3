#include "./ej5.h"
#include "../mini_test.h"
#include "../framework/structures/adj_list_graph.h"

#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"

/*
**  Exercise 5
**  Unit tests
*/

void test_triangles() {
    graph<int>* graph1 = new adj_list_graph<int>();
    graph1->add_node(1);
    graph1->add_node(2);
    graph1->add_node(3);
    graph1->add_edge(1, 2);
    graph1->add_edge(1, 3);
    graph1->add_edge(2, 3);

    graph<int>* graph2 = new adj_list_graph<int>();
    graph2->add_node(4);
    graph2->add_node(5);
    graph2->add_node(6);
    graph2->add_node(7);
    graph2->add_node(8);
    graph2->add_edge(4, 5);
    graph2->add_edge(4, 6);
    graph2->add_edge(5, 6);
    graph2->add_edge(6, 8);
    graph2->add_edge(7, 8);

    graph<std::pair<int, int>>* start_point = new adj_list_graph<std::pair<int, int>, hash_pair_int>();
    start_point->add_node({1, 7});
    start_point->add_node({2, 6});
    start_point->add_node({3, 8});
    start_point->add_edge({1, 7}, {3, 8});
    start_point->add_edge({2, 6}, {3, 8});

    graph<std::pair<int, int>>* mcs = solve_local_search_1(*graph1, *graph2, *start_point);

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs;
}

void test_crossed_square() {
    graph<int>* graph1 = new adj_list_graph<int>();
    graph1->add_node(6);
    graph1->add_node(7);
    graph1->add_node(8);
    graph1->add_node(9);
    graph1->add_edge(6,7);
    graph1->add_edge(6,8);
    graph1->add_edge(7,8);
    graph1->add_edge(7,9);
    graph1->add_edge(8,9);

    graph<int>* graph2 = new adj_list_graph<int>();
    graph2->add_node(0);
    graph2->add_node(1);
    graph2->add_node(2);
    graph2->add_node(3);
    graph2->add_node(4);
    graph2->add_node(5);
    graph2->add_edge(0,1);
    graph2->add_edge(0,2);
    graph2->add_edge(2,3);
    graph2->add_edge(2,4);
    graph2->add_edge(3,4);
    graph2->add_edge(3,5);
    graph2->add_edge(4,5);

    graph<std::pair<int, int>>* start_point = new adj_list_graph<std::pair<int, int>, hash_pair_int>();
    start_point->add_node({6,2});
    start_point->add_node({7,3});
    start_point->add_node({8,0});
    start_point->add_node({9,1});
    start_point->add_edge({8,0},{9,1});
    start_point->add_edge({8,0},{6,2});
    start_point->add_edge({6,2},{7,3});

    graph<std::pair<int, int>>* mcs = solve_local_search_1(*graph1, *graph2, *start_point);
    ASSERT_EQ(mcs->m(), 5);

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs;
}

void compare_with_greedy() {
    // CYCLES
    std::cout << "CYCLES" << std::endl;
    element_generator_int e_gen;
    e_gen.reset();
    adj_list_graph<int> g1 = graph_factory<int>::cycle_graph(e_gen, 2000);
    adj_list_graph<int> g2 = graph_factory<int>::cycle_graph(e_gen, 6000);

    graph<std::pair<int, int>>* start_point = solve_greedy(g1, g2);
    std::cout << "  GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*start_point), g1, g2) ? " (valid)" : " (invalid)") << std::endl;

    graph<std::pair<int, int>>* h = solve_local_search_1(g1, g2, *start_point, 100, .2);
    std::cout << "  L SRCH: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g1, g2) ? " (valid)" : " (invalid)") << std::endl;

    delete start_point;
    delete h;

    // TREES
    std::cout << "TREES" << std::endl;
    e_gen.reset();
    adj_list_graph<int> g3, g4;
    graph_factory<int>::add_n_tree_vertices(g3, e_gen, 1000);
    graph_factory<int>::add_n_tree_vertices(g4, e_gen, 1500);
    start_point = solve_greedy(g3, g4, true);
    std::cout << "  GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*start_point), g3, g4) ? " (valid)" : " (invalid)") << std::endl;

    h = solve_local_search_1(g3, g4, *start_point, 100, .4);
    std::cout << "  L SRCH: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g3, g4) ? " (valid)" : " (invalid)") << std::endl;

    delete start_point;
    // delete h;
}

void run_unit_tests() {
    // RUN_TEST(test_triangles);
    // RUN_TEST(test_crossed_square);
    compare_with_greedy();
}
