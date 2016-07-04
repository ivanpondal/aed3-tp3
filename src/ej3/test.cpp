#include "../main.h"
#include "./ej3.h"
#include "../mini_test.h"
#include "../framework/structures/adj_list_graph.h"

#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"

#include <algorithm>

/*
**  Exercise 3
**  Unit tests
*/

using namespace std;

void test_p3_vs_k2() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    g1.add_node(0);
    g1.add_node(1);
    g1.add_node(2);
    g1.add_edge(0,1);
    g1.add_edge(1,2);

    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 2);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 2);
    ASSERT_EQ(max_com_sub.h->m(), 1);
}

void test_p3_vs_k3() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    g1.add_node(0);
    g1.add_node(1);
    g1.add_node(2);
    g1.add_edge(0,1);
    g1.add_edge(1,2);

    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 3);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 3);
    ASSERT_EQ(max_com_sub.h->m(), 2);
}

void test_p3_vs_k4() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    g1.add_node(0);
    g1.add_node(1);
    g1.add_node(2);
    g1.add_edge(0,1);
    g1.add_edge(1,2);

    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 4);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 3);
    ASSERT_EQ(max_com_sub.h->m(), 2);
}

void test_eight_lonely_nodes() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    g1.add_node(0);
    g1.add_node(1);
    g1.add_node(2);
    g1.add_node(3);
    g1.add_node(4);
    g1.add_node(5);
    g1.add_node(6);
    g1.add_node(7);

    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 6);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 6);
    ASSERT_EQ(max_com_sub.h->m(), 0);
}

void test_k6_vs_k4() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    graph_factory<int>::add_n_vertices_and_all_edges(g1, e_gen, 6);

    e_gen.reset();
    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 4);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 4);
    ASSERT_EQ(max_com_sub.h->m(), 6);
}

void test_triangle_line_and_two_lonely_nodes() {
    element_generator_int e_gen;

    adj_list_graph<int> g1;
    g1.add_node(0);
    g1.add_node(1);
    g1.add_node(2);
    g1.add_node(3);
    g1.add_node(4);
    g1.add_node(5);
    g1.add_node(6);
    g1.add_node(7);
    g1.add_edge(1,2);
    g1.add_edge(1,3);
    g1.add_edge(2,3);
    g1.add_edge(2,4);
    g1.add_edge(3,4);
    g1.add_edge(6,7);

    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 4);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 4);
    ASSERT_EQ(max_com_sub.h->m(), 5);
}

void test_large_random_cograph() {
    element_generator_int e_gen;

    adj_list_graph<int> g1 = graph_factory<int>::random_co_graph(e_gen, 400);

    e_gen.reset();
    adj_list_graph<int> g2;
    graph_factory<int>::add_n_vertices_and_all_edges(g2, e_gen, 350);

    solution max_com_sub = solve_cograph_vs_complete(g1, g2);
    ASSERT(check_solution(max_com_sub, g1, g2));
    ASSERT_EQ(max_com_sub.h->n(), 350);
}

void run_unit_tests() {
    RUN_TEST(test_p3_vs_k2);
    RUN_TEST(test_p3_vs_k3);
    RUN_TEST(test_p3_vs_k4);
    RUN_TEST(test_eight_lonely_nodes);
    RUN_TEST(test_k6_vs_k4);
    RUN_TEST(test_triangle_line_and_two_lonely_nodes);
    RUN_TEST(test_large_random_cograph);
}
