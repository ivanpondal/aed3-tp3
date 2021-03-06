#include "main.h"
#include "../mini_test.h"

using namespace std;

// class definitions

void adj_list_n_incremental_experiment::load_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input){

	input->get_subject().add_node(input->get_inc_val());
}

void adj_list_n_incremental_experiment::solve_instance(
	incremental_experiment_input<int, adj_list_graph<int>> *input){

	input->get_subject().contains(-1);
}

void adj_list_c_incremental_experiment::load_instance(
	incremental_experiment_input<float, adj_list_graph<int>> *input){

	graph_factory<int>::add_n_random_vertices(input->get_subject(), e_gen, 1, input->get_inc_val());
}

void adj_list_c_incremental_experiment::solve_instance(
	incremental_experiment_input<float, adj_list_graph<int>> *input){

	input->get_subject().contains(-1);
}

// unit tests

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

	vector<int> expected = {2, 3};
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

	stringstream iss;
	iss << "5 4\n1 2\n2 3\n3 4\n3 5";

	iss >> g;

	ASSERT_EQ(g.n(), 5);
	ASSERT_EQ(g.m(), 4);

	ASSERT(g.adjacent(2, 1));
	ASSERT(g.adjacent(3, 2));
	ASSERT(g.adjacent(3, 4));
	ASSERT(g.adjacent(3, 5));

	vector<int> expected = {2, 4, 5};
	ASSERT(g.neighbours(3) == expected);
}

void test_adj_list_graph_ostream(){
	adj_list_graph<int> g;

	g.add_node(4);
	g.add_node(2);
	g.add_node(6);
	g.add_node(7);

	g.add_edge(4, 2);
	g.add_edge(2, 6);
	g.add_edge(6, 4);
	g.add_edge(6, 7);

	stringstream oss;
	oss << g;
	const char* expected = "4: 2 6\n2: 4 6\n6: 2 4 7\n7: 6\n";

	ASSERT_EQ(oss.str().c_str(), expected);
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

	vector<int> expected = {4, 2, 3};

	ASSERT(g.get_vertices() == expected);
}

void test_adj_list_graph_unite(){
	adj_list_graph<int> g_1;
	adj_list_graph<int> g_2;
	g_1.add_node(0);
	g_1.add_node(1);
	g_1.add_node(2);
	g_2.add_node(0);
	g_2.add_node(1);
	g_2.add_node(2);
	g_2.add_edge(0,1);
	g_2.add_edge(1,2);
	g_2.add_edge(2,0);
	element_generator_int e_gen;
	g_1.unite(g_2,e_gen);
	vector<int> expected = {0, 1, 2, 3, 4, 5};
	ASSERT(g_1.adjacent(3, 4));
	ASSERT(g_1.adjacent(4, 5));
	ASSERT(g_1.adjacent(5, 3));
	ASSERT(g_1.get_vertices() == expected);
}

void test_adj_list_graph_join(){
	adj_list_graph<int> g_1;
	adj_list_graph<int> g_2;
	g_1.add_node(0);
	g_1.add_node(1);
	g_1.add_node(2);
	g_2.add_node(0);
	g_2.add_node(1);
	g_2.add_node(2);
	g_2.add_edge(0,1);
	g_2.add_edge(1,2);
	g_2.add_edge(2,0);
	element_generator_int e_gen;
	g_1.join(g_2,e_gen);
	vector<int> expected = {0, 1, 2, 3, 4, 5};
	ASSERT(g_1.adjacent(3, 4));
	ASSERT(g_1.adjacent(4, 5));
	ASSERT(g_1.adjacent(5, 3));
	//cout << "join" << g_1 << endl;
	ASSERT(g_1.adjacent(0, 3));
	ASSERT(g_1.adjacent(0, 4));
	ASSERT(g_1.adjacent(0, 5));
	ASSERT(g_1.adjacent(1, 3));
	ASSERT(g_1.adjacent(1, 4));
	ASSERT(g_1.adjacent(1, 5));
	ASSERT(g_1.adjacent(2, 3));
	ASSERT(g_1.adjacent(2, 4));
	ASSERT(g_1.adjacent(2, 5));
	ASSERT(g_1.get_vertices() == expected);
	adj_list_graph<int> g_3;
	adj_list_graph<int> g_4;
	g_3.add_node(0);
	g_4.add_node(0);
	element_generator_int e_gen_1;
	g_3.join(g_4,e_gen_1);
	//cout << endl << "join" << g_3 << endl;
	ASSERT(g_3.adjacent(0, 1));
}

void test_adj_list_graph_assignment(){
	adj_list_graph<int> g;
	g.add_node(7);
	g.add_node(4);
	g.add_node(3);
	g.add_edge(7, 3);
	graph<int>* g_base = &g;

	adj_list_graph<int> g_tmp;
	g_tmp.add_node(1);
	g_tmp.add_node(2);
	g_tmp.add_node(3);
	g_tmp.add_edge(1, 2);
	g_tmp.add_edge(2, 3);
	graph<int>* g_base_tmp = &g_tmp;

	(*g_base) = *g_base_tmp;

	ASSERT(g.contains(1));
	ASSERT(g.contains(2));
	ASSERT(g.contains(3));

	ASSERT_EQ(g.n(), 3);
	ASSERT_EQ(g.m(), 2);

	ASSERT(g.adjacent(1, 2));
	ASSERT(g.adjacent(2, 3));
}

void test_adj_list_n_incremental_experiment(){
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> input_exp(1, 100000, 0, 60, 1000, adj_list_graph<int>(), "test_adj_list_n");

	adj_list_n_incremental_experiment exp(&input_exp);

	exp.run();
}

void test_adj_list_c_incremental_experiment(){
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_float< adj_list_graph<int>> input_exp(0, 1, 0, 60, 100, adj_list_graph<int>(), "test_adj_list_c");

	adj_list_c_incremental_experiment exp(&input_exp);

	exp.run();
}

void test_adj_list_n_incremental_experiment_suite(){
	// load min, max, discard, repetitions, samples and initial subject values
	incremental_experiment_input_int< adj_list_graph<int>> exp1_input(1, 100000, 0, 60, 1000, adj_list_graph<int>(), "test_adj_list_n_1");
	incremental_experiment_input_int< adj_list_graph<int>> exp2_input(1, 100, 20, 60, 50, adj_list_graph<int>(), "test_adj_list_n_2");

	adj_list_n_incremental_experiment exp1 = adj_list_n_incremental_experiment(&exp1_input);
	adj_list_n_incremental_experiment exp2 = adj_list_n_incremental_experiment(&exp2_input);

	experiment_suite exp_suite;

	exp_suite.add(&exp1);
	exp_suite.add(&exp2);

	exp_suite.run();
}

void test_graph_factory_int_random(){
	element_generator_int e_gen;
	adj_list_graph<int> g;
	float epsilon = 0.01;
	float edge_proportion = 0;

	graph_factory<int>::add_n_random_vertices(g, e_gen, 100, 0.5);

	edge_proportion = g.m()*1.0f / ((g.n()*(g.n() - 1))/2);

	ASSERT_EQ(g.n(), 100);
	ASSERT(abs(edge_proportion - 0.5) < epsilon);
}

void test_graph_factory_int_tree(){
	element_generator_int e_gen;
	adj_list_graph<int> g;

	graph_factory<int>::add_n_tree_vertices(g, e_gen, 10);

	ASSERT_EQ(g.n(), 10);
	ASSERT_EQ(g.m(), 9);
}

void test_graph_factory_int_bipartite(){
	element_generator_int e_gen;

	float epsilon = 0.01;
	float edge_proportion = 0;

	int n = 20;
	int k = 100;

	adj_list_graph<int> g = graph_factory<int>::random_bipartite_graph(e_gen, n, k, 0.5);

	edge_proportion = g.m()*1.0f / (n*k);

	ASSERT_EQ(g.n(), n + k);
	ASSERT(abs(edge_proportion - 0.5) < epsilon);
}

void test_graph_factory_int_cycle(){
	element_generator_int e_gen;

	int n = 10;

	adj_list_graph<int> g = graph_factory<int>::cycle_graph(e_gen, n);

	for(unsigned int i = 0; i < g.n(); i++){
		ASSERT_EQ(g.degree(g.get_vertices()[i]), 2);
	}

	ASSERT_EQ(g.n(), n);
	ASSERT_EQ(g.m(), n);
}

void test_graph_factory_int_disconnected(){
	element_generator_int e_gen;

	int n = 12;
	int d = 3;

	// forest
	adj_list_graph<int> g = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 0);

	ASSERT_EQ(g.n(), n);
	ASSERT_EQ(g.m(), n - d);

	// complete
	g = graph_factory<int>::random_disconnected_graph(e_gen, n, d, 1);

	ASSERT_EQ(g.n(), n);
	ASSERT_EQ(g.m(), d*(n/d)*(n/d - 1)/2);
}

void test_complete_graph(){
	element_generator_int e_gen;
	adj_list_graph<int> g;

	graph_factory<int>::add_n_vertices_and_all_edges(g,e_gen,1);

	ASSERT_EQ(g.m(), 0);
	ASSERT_EQ(g.n(), 1);

	graph_factory<int>::add_n_vertices_and_all_edges(g,e_gen,1);

	ASSERT_EQ(g.m(), 1);
	ASSERT(g.adjacent(0, 1));
	ASSERT_EQ(g.n(), 2);

	graph_factory<int>::add_n_vertices_and_all_edges(g,e_gen,2);

	ASSERT_EQ(g.m(), 6);
	ASSERT_EQ(g.n(), 4);

	ASSERT(g.adjacent(0, 1));

	ASSERT(g.adjacent(0, 2));
	ASSERT(g.adjacent(1, 2));

	ASSERT(g.adjacent(0, 3));
	ASSERT(g.adjacent(1, 3));
	ASSERT(g.adjacent(2, 3));

}

void test_co_graph_with_c_probability_edges(){
	element_generator_int e_gen;
	adj_list_graph<int> g;

	g = graph_factory<int>::co_graph_with_c_probability_edges(e_gen,10,0.f);

	ASSERT_EQ(g.m(), 0);
	ASSERT_EQ(g.n(), 10);

	e_gen.reset();
	g = graph_factory<int>::co_graph_with_c_probability_edges(e_gen,4,1.0f);

	ASSERT_EQ(g.m(), 6);
	ASSERT_EQ(g.n(), 4);

	ASSERT(g.adjacent(0, 1));

	ASSERT(g.adjacent(0, 2));
	ASSERT(g.adjacent(1, 2));

	ASSERT(g.adjacent(0, 3));
	ASSERT(g.adjacent(1, 3));
	ASSERT(g.adjacent(2, 3));

}

void run_unit_tests(){
	// adj_list_graph tests
	RUN_TEST(test_adj_list_graph_add_nodes);
	RUN_TEST(test_adj_list_graph_add_edges);
	RUN_TEST(test_adj_list_graph_neighbours);
	RUN_TEST(test_adj_list_graph_degree);
	RUN_TEST(test_adj_list_graph_istream);
	RUN_TEST(test_adj_list_graph_ostream);
	RUN_TEST(test_adj_list_graph_contains);
	RUN_TEST(test_adj_list_graph_clone);
	RUN_TEST(test_adj_list_graph_vertices);
	RUN_TEST(test_adj_list_graph_assignment);
	RUN_TEST(test_adj_list_graph_unite);
	RUN_TEST(test_adj_list_graph_join);

	// experiment tests
	RUN_TEST(test_adj_list_n_incremental_experiment);
	RUN_TEST(test_adj_list_c_incremental_experiment);
	RUN_TEST(test_adj_list_n_incremental_experiment_suite);

	// utils tests
	RUN_TEST(test_graph_factory_int_random);
	RUN_TEST(test_graph_factory_int_tree);
	RUN_TEST(test_graph_factory_int_bipartite);
	RUN_TEST(test_graph_factory_int_cycle);
	RUN_TEST(test_graph_factory_int_disconnected);
	RUN_TEST(test_complete_graph);
	RUN_TEST(test_co_graph_with_c_probability_edges);

}
