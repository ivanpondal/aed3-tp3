#include "../main.h"
#include "./exercise2.h"
#include "../mini_test.h"
#include "../framework/structures/adj_list_graph.h"
#include <sstream>

using namespace std;

void test_isolated_nodes() {
    adj_list_graph<int> g1;
    adj_list_graph<int> g2;

    g1.add_node(1);
    g2.add_node(1);

    graph<int> *maxComSub = mcs(&g1, &g2);

    ASSERT_EQ(maxComSub->m(), 0);
}

void test_k_1() {
    adj_list_graph<int> g1;
    adj_list_graph<int> g2;

    g1.add_node(1);
    g1.add_node(2);
    g1.add_edge(1, 2);

    g2.add_node(1);
    g2.add_node(2);
    g2.add_edge(1, 2);


    graph<int> *maxComSub = mcs(&g1, &g2);

    ASSERT_EQ(maxComSub->m(), 1);
}

void run_unit_tests() {
//    RUN_TEST(test_isolated_nodes);
    RUN_TEST(test_k_1);
}