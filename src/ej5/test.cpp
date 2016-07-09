#include "./ej5.h"
#include "../mini_test.h"
#include "../framework/structures/adj_list_graph.h"

#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/utils/chronometer.h"

#include "../exact/exact.h"

/*
**  Exercise 5
**  Unit tests
*/

void test_c5() {
    graph<int>* graph1 = new adj_list_graph<int>();
    graph1->add_node(1);
    graph1->add_node(2);
    graph1->add_node(3);
    graph1->add_node(4);
    graph1->add_node(5);
    graph1->add_edge(1, 2);
    graph1->add_edge(2, 3);
    graph1->add_edge(3, 4);
    graph1->add_edge(4, 5);
    graph1->add_edge(5, 1);

    graph<int>* graph2 = new adj_list_graph<int>();
    graph2->add_node(11);
    graph2->add_node(12);
    graph2->add_node(13);
    graph2->add_node(14);
    graph2->add_node(15);
    graph2->add_node(16);
    graph2->add_edge(11, 12);
    graph2->add_edge(12, 13);
    graph2->add_edge(13, 14);
    graph2->add_edge(14, 15);
    graph2->add_edge(15, 11);

    graph<std::pair<int, int>>* start_point = new adj_list_graph<std::pair<int, int>, hash_pair_int>();
    start_point->add_node({1, 11});
    start_point->add_node({2, 12});
    start_point->add_node({3, 14});
    start_point->add_node({4, 13});
    start_point->add_node({5, 15});
    start_point->add_edge({1, 11}, {2, 12});
    start_point->add_edge({3, 14}, {4, 13});
    start_point->add_edge({5, 15}, {1, 11});

    graph<std::pair<int, int>>* mcs1 = solve_local_search(*graph1, *graph2, *start_point, 1);
    graph<std::pair<int, int>>* mcs2 = solve_local_search(*graph1, *graph2, *start_point, 2);

    ASSERT_EQ(mcs1->n(), 5);
    ASSERT_EQ(mcs1->m(), 3);

    ASSERT_EQ(mcs2->n(), 5);
    ASSERT_EQ(mcs2->m(), 5);

    ASSERT(check_solution(pairs_to_solution(*mcs1), *graph1, *graph2));
    ASSERT(check_solution(pairs_to_solution(*mcs2), *graph1, *graph2));

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs1;
    delete mcs2;
}

void test_c8() {
    graph<int>* graph1 = new adj_list_graph<int>();
    graph1->add_node(1);
    graph1->add_node(2);
    graph1->add_node(3);
    graph1->add_node(4);
    graph1->add_node(5);
    graph1->add_node(6);
    graph1->add_node(7);
    graph1->add_node(8);
    graph1->add_edge(1, 2);
    graph1->add_edge(2, 3);
    graph1->add_edge(3, 4);
    graph1->add_edge(4, 5);
    graph1->add_edge(5, 6);
    graph1->add_edge(6, 7);
    graph1->add_edge(7, 8);
    graph1->add_edge(8, 1);

    graph<int>* graph2 = new adj_list_graph<int>();
    graph2->add_node(11);
    graph2->add_node(12);
    graph2->add_node(13);
    graph2->add_node(14);
    graph2->add_node(15);
    graph2->add_node(16);
    graph2->add_node(17);
    graph2->add_node(18);
    graph2->add_node(19);
    graph2->add_edge(11, 12);
    graph2->add_edge(12, 13);
    graph2->add_edge(13, 14);
    graph2->add_edge(14, 15);
    graph2->add_edge(15, 16);
    graph2->add_edge(16, 17);
    graph2->add_edge(17, 18);
    graph2->add_edge(18, 11);

    graph<std::pair<int, int>>* start_point = new adj_list_graph<std::pair<int, int>, hash_pair_int>();
    start_point->add_node({1, 11});
    start_point->add_node({2, 12});
    start_point->add_node({3, 14});
    start_point->add_node({4, 13});
    start_point->add_node({5, 15});
    start_point->add_node({6, 17});
    start_point->add_node({7, 16});
    start_point->add_node({8, 19});
    start_point->add_edge({1, 11}, {2, 12});
    start_point->add_edge({3, 14}, {4, 13});
    start_point->add_edge({6, 17}, {7, 16});

    graph<std::pair<int, int>>* mcs1 = solve_local_search(*graph1, *graph2, *start_point, 1);
    graph<std::pair<int, int>>* mcs2 = solve_local_search(*graph1, *graph2, *start_point, 2);

    ASSERT_EQ(mcs1->n(), 8);
    ASSERT_EQ(mcs1->m(), 5);

    ASSERT_EQ(mcs2->n(), 8);
    ASSERT_EQ(mcs2->m(), 8);

    ASSERT(check_solution(pairs_to_solution(*mcs1), *graph1, *graph2));
    ASSERT(check_solution(pairs_to_solution(*mcs2), *graph1, *graph2));

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs1;
    delete mcs2;
}

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
    start_point->add_node({1, 5});
    start_point->add_node({2, 6});
    start_point->add_node({3, 8});
    start_point->add_edge({1, 5}, {2, 6});
    start_point->add_edge({2, 6}, {3, 8});

    graph<std::pair<int, int>>* mcs1 = solve_local_search(*graph1, *graph2, *start_point, 1);
    graph<std::pair<int, int>>* mcs2 = solve_local_search(*graph1, *graph2, *start_point, 2);

    ASSERT_EQ(mcs1->n(), 3);
    ASSERT_EQ(mcs1->m(), 3);

    ASSERT_EQ(mcs2->n(), 3);
    ASSERT_EQ(mcs2->m(), 3);

    ASSERT(check_solution(pairs_to_solution(*mcs1), *graph1, *graph2));
    ASSERT(check_solution(pairs_to_solution(*mcs2), *graph1, *graph2));

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs1;
    delete mcs2;
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
    graph2->add_edge(1,4);
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

    graph<std::pair<int, int>>* mcs1 = solve_local_search(*graph1, *graph2, *start_point, 1);
    graph<std::pair<int, int>>* mcs2 = solve_local_search(*graph1, *graph2, *start_point, 2);

    ASSERT_EQ(mcs1->n(), 4);
    ASSERT_EQ(mcs1->m(), 4);

    ASSERT_EQ(mcs2->n(), 4);
    ASSERT_EQ(mcs2->m(), 5);

    ASSERT(check_solution(pairs_to_solution(*mcs1), *graph1, *graph2));
    ASSERT(check_solution(pairs_to_solution(*mcs2), *graph1, *graph2));

    delete graph1;
    delete graph2;
    delete start_point;
    delete mcs1;
    delete mcs2;
}

void compare_neighbourhoods() {
    chronometer timer;
    element_generator_int e_gen;
    graph<std::pair<int, int>>* start_point;
    graph<std::pair<int, int>>* h;
    double time;

    // CYCLES
    std::cout << "Graph type: CYCLES" << std::endl;
    e_gen.reset();
    adj_list_graph<int> g1 = graph_factory<int>::cycle_graph(e_gen, 2000);
    e_gen.reset();
    adj_list_graph<int> g2 = graph_factory<int>::cycle_graph(e_gen, 6000);

    timer.start();
    start_point = solve_greedy(g1, g2);
    time = timer.stop() / 1000000000;
    std::cout << "  GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*start_point), g1, g2) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;

    timer.start();
    h = solve_local_search(g1, g2, *start_point, 1, -1, .01);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 1: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g1, g2) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    timer.start();
    h = solve_local_search(g1, g2, *start_point, 2, -1, .01);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 2: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g1, g2) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    delete start_point;

    // TREES
    std::cout << "Graph type: TREES" << std::endl;
    e_gen.reset();
    adj_list_graph<int> g3, g4;
    graph_factory<int>::add_n_tree_vertices(g3, e_gen, 512);
    e_gen.reset();
    graph_factory<int>::add_n_tree_vertices(g4, e_gen, 1024);
    timer.start();
    start_point = solve_greedy(g3, g4);
    time = timer.stop() / 1000000000;
    std::cout << "  GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*start_point), g3, g4) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;

    timer.start();
    h = solve_local_search(g3, g4, *start_point, 1, -1, .01);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 1: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g3, g4) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    timer.start();
    h = solve_local_search(g3, g4, *start_point, 2, -1, .01);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 2: " << h->n() << " nodes, " << h->m() << " edges";
    std::cout << (check_solution(pairs_to_solution(*h), g3, g4) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    delete start_point;
}

void compare_with_cograph_exact() {
    chronometer timer;
    element_generator_int e_gen;
    graph<std::pair<int, int>>* start_point;
    graph<std::pair<int, int>>* h;
    double time;

    // COGRAPHS
    std::cout << "Graph type: COGRAPHS (Comparing with exact algorithm)" << std::endl;
    e_gen.reset();
    adj_list_graph<int> g1 = graph_factory<int>::random_co_graph(e_gen, 512);
    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 128);

    timer.start();
    solution exact_solution = solve_cograph_vs_complete(g1, g2);
    time = timer.stop() / 1000000000;
    std::cout << "  EXACT: " << exact_solution.h->n() << " nodes, " << exact_solution.h->m() << " edges" << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;

    timer.start();
    start_point = solve_greedy(g2, g1);
    time = timer.stop() / 1000000000;
    std::cout << "  GREEDY: " << start_point->n() << " nodes, " << start_point->m() << " edges ("
              << (float) start_point->m() / (float) exact_solution.h->m() * 100 << "\% exact)";
    std::cout << (check_solution(pairs_to_solution(*start_point), g2, g1) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;

    timer.start();
    h = solve_local_search(g2, g1, *start_point, 1, -1, .005);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 1: " << h->n() << " nodes, " << h->m() << " edges ("
              << (float) h->m() / (float) exact_solution.h->m() * 100 << "\% exact)";
    std::cout << (check_solution(pairs_to_solution(*h), g2, g1) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    timer.start();
    h = solve_local_search(g2, g1, *start_point, 2, -1, .005);
    time = timer.stop() / 1000000000;
    std::cout << "  L SRCH 2: " << h->n() << " nodes, " << h->m() << " edges ("
              << (float) h->m() / (float) exact_solution.h->m() * 100 << "\% exact)";
    std::cout << (check_solution(pairs_to_solution(*h), g2, g1) ? " (valid)" : " (invalid)") << std::endl;
    std::cout << "    time: " << time << " seconds" << std::endl;
    delete h;

    delete start_point;
}

void run_unit_tests() {
    RUN_TEST(test_c5);
    RUN_TEST(test_c8);
    RUN_TEST(test_triangles);
    RUN_TEST(test_crossed_square);
    compare_neighbourhoods();
    compare_with_cograph_exact();
}
