#include "../main.h"
#include "ej2.h"
#include "../mini_test.h"
#include <sstream>

using namespace std;

void test_isolated_nodes() {
    adj_list_graph<int> g1;
    adj_list_graph<int> g2;

    g1.add_node(1);
    g1.add_node(2);
    g2.add_node(2);
    g2.add_node(3);

    graph<int> *maxComSub = mcs(&g1, &g2);

    ASSERT_EQ(maxComSub->m(), 0);

    delete(maxComSub);
}

void test_k1_and_other() {
    adj_list_graph<int> g1;
    adj_list_graph<int> g2;

    g1.add_node(1);
    g2.add_node(2);
    g2.add_node(1);

    graph<int> *maxComSub = mcs(&g1, &g2);

    ASSERT_EQ(maxComSub->m(), 0);

    delete(maxComSub);
}

void test_k2s() {
    adj_list_graph<int> g1;
    adj_list_graph<int> g2;

    g1.add_node(1);
    g1.add_node(2);
    g1.add_edge(1, 2);

    g2.add_node(3);
    g2.add_node(4);
    g2.add_edge(3, 4);


    graph<int> *maxComSub = mcs(&g1, &g2);

    ASSERT_EQ(maxComSub->m(), 1);
    ASSERT_EQ(maxComSub->n(), 2);

    delete(maxComSub);
}

void test_k2_and_k3() {
    element_generator_int e_gen;
    adj_list_graph<int> k2, k3;

    graph_factory<int>::add_n_random_vertices(k2, e_gen, 2, 1.0f);
    graph_factory<int>::add_n_random_vertices(k3, e_gen, 3, 1.0f);

    graph<int> *maxComSub = mcs(&k2, &k3);

    ASSERT_EQ(maxComSub->m(), 1);
    ASSERT_EQ(maxComSub->n(), 2);

    delete(maxComSub);
}

void test_k4s() {
    element_generator_int e_gen;
    adj_list_graph<int> k4, k4bis;

    graph_factory<int>::add_n_random_vertices(k4, e_gen, 4, 1.0f);
    graph_factory<int>::add_n_random_vertices(k4bis, e_gen, 4, 1.0f);

    graph<int> *maxComSub = mcs(&k4, &k4bis);

    // ASSERT_EQ(maxComSub->m(), 6);

    delete(maxComSub);
}

void test_p4_and_2k2() {
    adj_list_graph<int> p4;
    adj_list_graph<int> k2s;

    p4.add_node(1);
    p4.add_node(2);
    p4.add_node(3);
    p4.add_node(4);
    p4.add_edge(1, 2);
    p4.add_edge(2, 3);
    p4.add_edge(3, 4);

    k2s.add_node(1);
    k2s.add_node(2);
    k2s.add_node(3);
    k2s.add_node(4);
    k2s.add_edge(1, 2);
    k2s.add_edge(3, 4);

    graph<int> *maxComSub = mcs(&p4, &k2s);

    ASSERT_EQ(maxComSub->m(), 2);

    delete(maxComSub);
}

void test_p4_and_3k2() {
    adj_list_graph<int> p4;
    adj_list_graph<int> k2s;

    p4.add_node(1);
    p4.add_node(2);
    p4.add_node(3);
    p4.add_node(4);
    p4.add_edge(1, 2);
    p4.add_edge(2, 3);
    p4.add_edge(3, 4);

    k2s.add_node(1);
    k2s.add_node(2);
    k2s.add_node(3);
    k2s.add_node(4);
    k2s.add_node(5);
    k2s.add_node(6);
    k2s.add_edge(1, 2);
    k2s.add_edge(3, 4);
    k2s.add_edge(5, 6);

    graph<int> *maxComSub = mcs(&p4, &k2s);

    ASSERT_EQ(maxComSub->m(), 2);

    delete(maxComSub);
}

void test_handcrafted_and_p5() {
    adj_list_graph<int> handcrafted;
    adj_list_graph<int> p5;

    handcrafted.add_node(1);
    handcrafted.add_node(2);
    handcrafted.add_node(3);
    handcrafted.add_node(4);
    handcrafted.add_edge(1, 2);
    handcrafted.add_edge(2, 3);
    handcrafted.add_edge(2, 4);
    handcrafted.add_edge(3, 4);

    p5.add_node(1);
    p5.add_node(2);
    p5.add_node(3);
    p5.add_node(4);
    p5.add_node(5);
    p5.add_edge(1, 2);
    p5.add_edge(2, 3);
    p5.add_edge(3, 4);
    p5.add_edge(4, 5);

    graph<int> *maxComSub = mcs(&handcrafted, &p5);

    ASSERT_EQ(maxComSub->m(), 3);

    delete(maxComSub);
}

void test_handcrafteds() {
    adj_list_graph<int> graph1, graph2;

    graph1.add_node(1);
    graph1.add_node(2);
    graph1.add_node(3);
    graph1.add_node(4);
    graph1.add_node(5);
    graph1.add_edge(1, 2);
    graph1.add_edge(1, 4);
    graph1.add_edge(1, 5);
    graph1.add_edge(2, 3);
    graph1.add_edge(2, 4);
    graph1.add_edge(3, 4);
    graph1.add_edge(4, 5);

    graph2.add_node(1);
    graph2.add_node(2);
    graph2.add_node(3);
    graph2.add_node(4);
    graph2.add_node(5);
    graph2.add_node(6);
    graph2.add_edge(1, 2);
    graph2.add_edge(1, 4);
    graph2.add_edge(1, 6);
    graph2.add_edge(2, 3);
    graph2.add_edge(2, 4);
    graph2.add_edge(3, 4);
    graph2.add_edge(4, 5);

    graph<int> *maxComSub = mcs(&graph1, &graph2);

    ASSERT_EQ(maxComSub->m(), 6);

    delete(maxComSub);
}

void test_pseudofranco_example() {
    adj_list_graph<int> graph1, graph2;

    graph1.add_node(1);
    graph1.add_node(2);
    graph1.add_node(3);
    graph1.add_node(4);
    graph1.add_node(5);
    graph1.add_node(6);
    graph1.add_edge(1, 2);
    graph1.add_edge(1, 3);
    graph1.add_edge(2, 3);
    graph1.add_edge(3, 4);
    graph1.add_edge(4, 5);
    graph1.add_edge(4, 6);
    graph1.add_edge(5, 6);

    graph2.add_node(1);
    graph2.add_node(2);
    graph2.add_node(3);
    graph2.add_node(4);
    graph2.add_node(5);
    graph2.add_node(6);
    graph2.add_node(7);
    graph2.add_edge(1, 2);
    graph2.add_edge(1, 3);
    graph2.add_edge(2, 3);
    graph2.add_edge(3, 4);
    graph2.add_edge(4, 5);
    graph2.add_edge(5, 6);
    graph2.add_edge(5, 7);
    graph2.add_edge(6, 7);

    graph<int> *maxComSub = mcs(&graph1, &graph2);

    ASSERT_EQ(maxComSub->m(), 6);

    delete(maxComSub);
}

void test_pseudofranco_example2() {
    adj_list_graph<int> franco1, franco2;

    franco1.add_node(1);
    franco1.add_node(2);
    franco1.add_node(3);
    franco1.add_node(4);
    franco1.add_node(5);
    franco1.add_node(6);
    franco1.add_node(7);
    franco1.add_edge(1, 2);
    franco1.add_edge(1, 3);
    franco1.add_edge(1, 4);
    franco1.add_edge(2, 3);
    franco1.add_edge(2, 4);
    franco1.add_edge(3, 4);
    franco1.add_edge(2, 5);
    franco1.add_edge(5, 6);
    franco1.add_edge(5, 7);
    franco1.add_edge(6, 7);

    franco2.add_node(1);
    franco2.add_node(2);
    franco2.add_node(3);
    franco2.add_node(4);
    franco2.add_node(5);
    franco2.add_node(6);
    franco2.add_node(7);
    franco2.add_node(8);
    franco2.add_edge(1, 2);
    franco2.add_edge(1, 3);
    franco2.add_edge(1, 4);
    franco2.add_edge(2, 3);
    franco2.add_edge(2, 4);
    franco2.add_edge(3, 4);
    franco2.add_edge(2, 8);
    franco2.add_edge(8, 5);
    franco2.add_edge(5, 6);
    franco2.add_edge(5, 7);
    franco2.add_edge(6, 7);

    graph<int> *maxComSub = mcs(&franco1, &franco2);

    ASSERT_EQ(maxComSub->m(), 9);

    delete(maxComSub);
}

void test_franco_example() {
    adj_list_graph<int> franco1, franco2;

    franco1.add_node(1);
    franco1.add_node(2);
    franco1.add_node(3);
    franco1.add_node(4);
    franco1.add_node(5);
    franco1.add_node(6);
    franco1.add_node(7);
    franco1.add_node(8);
    franco1.add_edge(1, 2);
    franco1.add_edge(1, 3);
    franco1.add_edge(1, 4);
    franco1.add_edge(2, 3);
    franco1.add_edge(2, 4);
    franco1.add_edge(3, 4);
    franco1.add_edge(2, 5);
    franco1.add_edge(5, 6);
    franco1.add_edge(5, 7);
    franco1.add_edge(5, 8);
    franco1.add_edge(6, 7);
    franco1.add_edge(6, 8);
    franco1.add_edge(7, 8);

    franco2.add_node(1);
    franco2.add_node(2);
    franco2.add_node(3);
    franco2.add_node(4);
    franco2.add_node(5);
    franco2.add_node(6);
    franco2.add_node(7);
    franco2.add_node(8);
    franco2.add_node(9);
    franco2.add_edge(1, 2);
    franco2.add_edge(1, 3);
    franco2.add_edge(1, 4);
    franco2.add_edge(2, 3);
    franco2.add_edge(2, 4);
    franco2.add_edge(3, 4);
    franco2.add_edge(2, 9);
    franco2.add_edge(9, 5);
    franco2.add_edge(5, 6);
    franco2.add_edge(5, 7);
    franco2.add_edge(5, 8);
    franco2.add_edge(6, 7);
    franco2.add_edge(6, 8);
    franco2.add_edge(7, 8);

    graph<int> *maxComSub = mcs(&franco1, &franco2);

    cout << endl << *maxComSub << endl;

    ASSERT_EQ(maxComSub->m(), 12);
       
    delete(maxComSub);
}

void run_unit_tests() {
    // RUN_TEST(test_isolated_nodes);
    // RUN_TEST(test_k1_and_other);
    // RUN_TEST(test_k2s);
    // RUN_TEST(test_k2_and_k3);
    RUN_TEST(test_k4s);
    // RUN_TEST(test_p4_and_2k2);
    // RUN_TEST(test_p4_and_3k2);
    // RUN_TEST(test_handcrafted_and_p5);
    // RUN_TEST(test_handcrafteds);
    // RUN_TEST(test_pseudofranco_example);
    // RUN_TEST(test_pseudofranco_example2);
    // RUN_TEST(test_franco_example);

}