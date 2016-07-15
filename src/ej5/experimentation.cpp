#include "./ej5.h"
#include "../framework/structures/adj_list_graph.h"

/*
**  Exercise 5
**  Experimentation
*/

// graph<std::pair<int, int>>* solve_local_search(
//     graph<int>& g1,
//     graph<int>& g2,
//     graph<std::pair<int, int>>& start_point,
//     int neighbourhood_type,                   // 1 or 2
//     int iteration_limit = -1,                 // -1 indicates no limit
//     float neighbourhood_proportion = 1,       // between 0 and 1
//     bool strict_comparisons = true
// );

using namespace std;


unsigned int quality_exp_local_search_with_swap::solve_instance(graph<int> &g1, graph<int> &g2) {

	graph<int>* large_graph, * small_graph;

    // Local search solver assumes g1 has at most as many nodes as g2. If that
    // is not the case, we have to exchange both graphs before passing them
    // to the function, and remember this fact so that we can read correctly
    // the obtained solution
    if (g1.n() <= g2.n()) {
        small_graph = &g1;
        large_graph = &g2;
    } else {
        small_graph = &g2;
        large_graph = &g1;
    }

    graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
    h = solve_local_search(*small_graph, *large_graph, *start_point, 2,50,0.002f,true);

    delete start_point;

	return h->m();
}

void quality_exp_local_search_with_swap::clean_solution() {
	delete h;

}


unsigned int quality_exp_local_search_without_swap::solve_instance(graph<int> &g1, graph<int> &g2) {

	graph<int>* large_graph, * small_graph;

    // Local search solver assumes g1 has at most as many nodes as g2. If that
    // is not the case, we have to exchange both graphs before passing them
    // to the function, and remember this fact so that we can read correctly
    // the obtained solution
    if(	g1.n() == g2.n() ){

    	return -1;

    }else{

    	if (g1.n() <= g2.n()) {
	        small_graph = &g1;
	        large_graph = &g2;
	    } else {
	        small_graph = &g2;
	        large_graph = &g1;
	    }
	    graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
    	h = solve_local_search(*small_graph, *large_graph, *start_point, 1,100,0.002f,true);
    	delete start_point;
    }

	return h->m();
}



void quality_exp_local_search_without_swap::clean_solution() {
	delete h;

}

void g1_vs_g2_neighbourhood_1_proportion_incremental_experiment::load_instance(incremental_experiment_input<float,
	star_solution >*input) {
	cout << "neighbourhood_1_proportion :  " << input->get_inc_val() << endl;

	// cout << "g1.n() :  " << input->get_subject().g1.n()<< endl;
	// cout << "g2.n() :  " << input->get_subject().g2.n()<< endl;

}

int g1_vs_g2_neighbourhood_1_proportion_incremental_experiment::solve_instance(incremental_experiment_input<float,
	star_solution > *input){
	// solve_local_search(graph<int>&, graph<int>&, graph<std::pair<int, int> >&, int, int, float, bool)
	graph<pair<int, int>>* h;
	if(input->get_inc_val() <0.2f){
		h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
		*input->get_subject().greedy_solve,1,-1,input->get_inc_val(),true);
		last_h_m = h->m();
	}else{
		int porcentage = (int) ( input->get_inc_val() * 100.0f);
		if (porcentage % 20 == 0){
			h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
			*input->get_subject().greedy_solve,1,-1,input->get_inc_val(),true);
			last_h_m = h->m();
		}else{
			return last_h_m;
		}

	}


	cout << "h->m() :  " << h->m() << endl;

	return h->m();

}

void g1_vs_g2_neighbourhood_2_proportion_incremental_experiment::load_instance(incremental_experiment_input<float,
	star_solution >*input) {
	cout << "neighbourhood_2_proportion :  " << input->get_inc_val() << endl;

	// cout << "g1.n() :  " << input->get_subject().g1.n()<< endl;
	// cout << "g2.n() :  " << input->get_subject().g2.n()<< endl;

}

int g1_vs_g2_neighbourhood_2_proportion_incremental_experiment::solve_instance(incremental_experiment_input<float,
	star_solution > *input){
	// solve_local_search(graph<int>&, graph<int>&, graph<std::pair<int, int> >&, int, int, float, bool)
	graph<pair<int, int>>* h;
	if(input->get_inc_val() <0.2f){
		h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
		*input->get_subject().greedy_solve,1,-1,input->get_inc_val(),true);
		last_h_m = h->m();
	}else{
		int porcentage = (int) ( input->get_inc_val() * 100.0f);
		if (porcentage % 20 == 0){
			h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
				*input->get_subject().greedy_solve,2,-1,input->get_inc_val(),true);
			last_h_m = h->m();
		}else{
			return last_h_m;
		}
	}
	cout << "h->m() :  " << h->m() << endl;
	return h->m();

}

void g1_vs_g2_neighbourhood_1_iterations_incremental_experiment::load_instance(incremental_experiment_input<int,
	star_solution >*input) {
	cout << "iteration :  " << input->get_inc_val() << endl;
	// cout << "g1.n() :  " << input->get_subject().g1.n()<< endl;
	// cout << "g2.n() :  " << input->get_subject().g2.n()<< endl;

}

int g1_vs_g2_neighbourhood_1_iterations_incremental_experiment::solve_instance(incremental_experiment_input<int,
	star_solution > *input){
	// solve_local_search(graph<int>&, graph<int>&, graph<std::pair<int, int> >&, int, int, float, bool)
		graph<pair<int, int>>* h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
		*input->get_subject().greedy_solve,1,input->get_inc_val(),0.05f,true);
	cout << "h->m() :  " << h->m() << endl;
	return h->m();

}


void g1_vs_g2_neighbourhood_2_iterations_incremental_experiment::load_instance(incremental_experiment_input<int,
	star_solution >*input) {
	cout << "iteration :  " << input->get_inc_val() << endl;
	// cout << "g1.n() :  " << input->get_subject().g1.n()<< endl;
	// cout << "g2.n() :  " << input->get_subject().g2.n()<< endl;

}

int g1_vs_g2_neighbourhood_2_iterations_incremental_experiment::solve_instance(incremental_experiment_input<int,
	star_solution > *input){
	// solve_local_search(graph<int>&, graph<int>&, graph<std::pair<int, int> >&, int, int, float, bool)
		graph<pair<int, int>>* h = solve_local_search(input->get_subject().g1, input->get_subject().g2,
		*input->get_subject().greedy_solve,2,input->get_inc_val(),0.001f,true);
	cout << "h->m() :  " << h->m() << endl;
	return h->m();

}

// Experiments

void run_experimentation(){


	experiment_suite quality_exp_suite;
	experiment_suite  neighbourhood_proportion_calibrate_exp_suite;
	experiment_suite  iteration_calibrate_exp_suite;

	// quality exp
	int repetitions_val = 3;
	int sample_val = 200;

	/*// quality local_search_2_exp
	quality_exp_local_search_with_swap local_search_2_exp(
			known_solution_instances, "../exp/ej5/known_solution_instances_search_2_exp", 0, repetitions_val);
	*/


	// quality local_search_1_exp
	/*quality_exp_local_search_without_swap local_search_1_exp(
			known_solution_instances, "../exp/ej5/known_solution_instances_search_1_exp_100", 0, repetitions_val);
	*/



	// quality similar_nodes_count_instance_generation

	// quality_exp_local_search_with_swap local_search_2_exp_similar_nodes_count(
	// 		similar_nodes_count_instances, "../exp/ej5/similar_nodes_count_instance_generation",
	// 		0, repetitions_val);


	//quality_exp_suite.add(&local_search_1_exp);
	/*quality_exp_suite.add(&local_search_2_exp);*/
	quality_exp_suite.run();




	// neighbourhood proportion calibrate

	// neighbourhood 1
	element_generator_int e_gen;
	// generate graph families
	adj_list_graph<int> big_tree;
	graph_factory<int>::add_n_tree_vertices(big_tree, e_gen, 600);
	e_gen.reset();
	adj_list_graph<int> small_tree;
	graph_factory<int>::add_n_tree_vertices(small_tree, e_gen, 300);

	e_gen.reset();
	adj_list_graph<int> big_complete;
	graph_factory<int>::add_n_vertices_and_all_edges(big_complete, e_gen, 300);
	e_gen.reset();
	adj_list_graph<int> small_complete;
	graph_factory<int>::add_n_vertices_and_all_edges(small_complete, e_gen, 150);
	e_gen.reset();
	adj_list_graph<int> big_cicle = graph_factory<int>::cycle_graph(e_gen, 600);
	e_gen.reset();
	adj_list_graph<int> small_cicle = graph_factory<int>::cycle_graph(e_gen, 300);
	e_gen.reset();
	adj_list_graph<int> big_bipartite_low_edges = graph_factory<int>::random_bipartite_graph(e_gen, 150, 150,0.1f);
	e_gen.reset();
	adj_list_graph<int> small_bipartite_low_edges = graph_factory<int>::random_bipartite_graph(e_gen, 75, 75,0.1f);
	e_gen.reset();
	adj_list_graph<int> big_bipartite_some_edges = graph_factory<int>::random_bipartite_graph(e_gen, 150, 150,0.5f);
	e_gen.reset();
	adj_list_graph<int> small_bipartite_some_edges = graph_factory<int>::random_bipartite_graph(e_gen, 75, 75,0.5f);
	e_gen.reset();
	adj_list_graph<int> big_bipartite_complete = graph_factory<int>::random_bipartite_graph(e_gen, 150, 150,1.0f);
	e_gen.reset();
	adj_list_graph<int> small_bipartite_complete = graph_factory<int>::random_bipartite_graph(e_gen, 75, 75,1.0f);


	star_solution parameters;
	graph<pair<int, int>>* start_point;


	// neighbourhood proportion calibrate

	// neighbourhood 1


	// big_tree_vs_small_tree
	start_point = solve_greedy(small_tree,big_tree);

	parameters.g1 =  small_tree;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;


	incremental_experiment_input_float< star_solution >  big_tree_vs_small_tree_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_small_tree_neighbourhood_1_proportion");


    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment  big_tree_vs_small_tree_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_tree_vs_small_tree_input);



    // big_cicle_vs_small_cicle
	start_point = solve_greedy(small_cicle,big_cicle);

	parameters.g1 =  small_cicle;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;


	incremental_experiment_input_float< star_solution >  big_cicle_vs_small_cicle_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_small_cicle_neighbourhood_1_proportion");


    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment  big_cicle_vs_small_cicle_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_cicle_vs_small_cicle_input);



	// tree_vs_big_complete
	start_point = solve_greedy(big_complete,big_tree);

	parameters.g1 =  big_complete;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_tree_vs_big_complete_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_big_complete_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_tree_vs_big_complete_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_tree_vs_big_complete_input);

    // big_cicle_vs_big_complete
    start_point = solve_greedy(big_complete,big_cicle);


	parameters.g1 =  big_complete;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_cicle_vs_big_complete_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_big_complete_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_cicle_vs_big_complete_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_cicle_vs_big_complete_input);




    //big_tree_vs_small_cicle_exp

    start_point = solve_greedy(small_cicle,big_tree);

    parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_tree_vs_small_cicle_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_small_cicle_neighbourhood_1_proportion");


    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_tree_vs_small_cicle_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_tree_vs_small_cicle_input);

    // big_cicle_vs_small_tree_exp


    start_point = solve_greedy(small_tree,big_tree);


    parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;


	incremental_experiment_input_float< star_solution >  big_cicle_vs_small_tree_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_small_tree_1_proportion");


    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_cicle_vs_small_tree_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_cicle_vs_small_tree_input);


	// big_bipartite_low_edges_vs_small_bipartite_low_edges
    start_point = solve_greedy(small_bipartite_low_edges,big_bipartite_low_edges);

    parameters.g1 =  small_bipartite_low_edges;
	parameters.g2 =  big_bipartite_low_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_low_edges_vs_small_bipartite_low_edges_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_low_edges_vs_small_bipartite_low_edges_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_low_edges_vs_small_bipartite_low_edges_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_low_edges_vs_small_bipartite_low_edges_input);


    // big_bipartite_some_edges_vs_small_bipartite_some_edges

    start_point = solve_greedy(small_bipartite_some_edges,big_bipartite_some_edges);

    parameters.g1 =  small_bipartite_some_edges;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_small_bipartite_some_edges_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_bipartite_some_edges_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_small_bipartite_some_edges_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_bipartite_some_edges_input);

    // big_bipartite_complete_vs_small_bipartite_complete

    start_point = solve_greedy(small_bipartite_complete,big_bipartite_complete);

    parameters.g1 =  small_bipartite_complete;
	parameters.g2 =  big_bipartite_complete;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_complete_vs_small_bipartite_complete_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_complete_vs_small_bipartite_complete_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_complete_vs_small_bipartite_complete_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_complete_vs_small_bipartite_complete_input);

    // big_bipartite_some_edges_vs_big_tree


    start_point = solve_greedy(big_bipartite_some_edges,big_tree);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_big_tree_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input);

    // big_bipartite_some_edges_vs_big_cicle

    start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_big_cicle_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp = 
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input);

    // big_bipartite_some_edges_vs_small_complete	


    start_point = solve_greedy(small_complete,big_bipartite_some_edges);

    parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_small_complete_input(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_1_proportion");

    g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp =
    	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input);




    // neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp);

    // neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp);

    // neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp);

    // neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp);

    // neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp);





    // neighbourhood 2


	// tree_vs_big_complete
	start_point = solve_greedy(big_complete,big_tree);

	parameters.g1 =  big_complete;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_tree_vs_big_complete_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_big_complete_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_tree_vs_big_complete_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_tree_vs_big_complete_input_2);

    // big_cicle_vs_big_complete 
    start_point = solve_greedy(big_complete,big_cicle);


	parameters.g1 =  big_complete;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_cicle_vs_big_complete_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_big_complete_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_cicle_vs_big_complete_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_cicle_vs_big_complete_input_2);

 

    //big_tree_vs_small_cicle_exp

    start_point = solve_greedy(small_cicle,big_tree);

    parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_tree_vs_small_cicle_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_small_cicle_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_tree_vs_small_cicle_exp_2 = 
    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_tree_vs_small_cicle_input_2);

    // big_cicle_vs_small_tree_exp

    start_point = solve_greedy(small_tree,big_tree);

    parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_cicle_vs_small_tree_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_small_tree_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_cicle_vs_small_tree_exp_2 = 
    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_cicle_vs_small_tree_input_2);


    // big_bipartite_low_edges_vs_small_bipartite_low_edges
    start_point = solve_greedy(small_bipartite_low_edges,big_bipartite_low_edges);

    parameters.g1 =  small_bipartite_low_edges;
	parameters.g2 =  big_bipartite_low_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_low_edges_vs_small_bipartite_low_edges_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_low_edges_vs_small_bipartite_low_edges_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_low_edges_vs_small_bipartite_low_edges_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_low_edges_vs_small_bipartite_low_edges_input_2);


    // big_bipartite_some_edges_vs_small_bipartite_some_edges

    start_point = solve_greedy(small_bipartite_some_edges,big_bipartite_some_edges);

    parameters.g1 =  small_bipartite_some_edges;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_small_bipartite_some_edges_input_2(0.0f, 1.0f, 3, 5,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_bipartite_some_edges_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_small_bipartite_some_edges_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_bipartite_some_edges_input_2);

    // big_bipartite_complete_vs_small_bipartite_complete

    start_point = solve_greedy(small_bipartite_complete,big_bipartite_complete);

    parameters.g1 =  small_bipartite_complete;
	parameters.g2 =  big_bipartite_complete;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_complete_vs_small_bipartite_complete_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_complete_vs_small_bipartite_complete_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_complete_vs_small_bipartite_complete_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_complete_vs_small_bipartite_complete_input_2);

    // big_bipartite_some_edges_vs_big_tree

    start_point = solve_greedy(big_bipartite_some_edges,big_tree);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_big_tree_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input_2);

    // big_bipartite_some_edges_vs_big_cicle

    start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_big_cicle_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input_2);

    // big_bipartite_some_edges_vs_small_complete	

    start_point = solve_greedy(small_complete,big_bipartite_some_edges);

    parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float< star_solution >  big_bipartite_some_edges_vs_small_complete_input_2(0.0f, 1.0f, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_2_proportion");

    g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp_2 = 
    	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input_2);




    neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp_2);

    neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp_2);

    neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp_2);

    neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp_2);

    neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp_2);


	 neighbourhood_proportion_calibrate_exp_suite.run();

	// neighbourhood 1

	// iteration calibrate
	repetitions_val = 3;
	sample_val = 10;

	int max_iteration= 200;
	//big_tree_vs_small_cicle_exp


    start_point = solve_greedy(small_cicle,big_tree);

    parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_tree_vs_small_cicle_iteration_input(0, max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_small_cicle_neighbourhood_1_iteration");

    g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_tree_vs_small_cicle_iteration_exp = 
    	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_tree_vs_small_cicle_iteration_input);

    // big_cicle_vs_small_tree_exp

    start_point = solve_greedy(small_tree,big_tree);

    parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_cicle_vs_small_tree_iteration_input(0, max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_small_tree_1_iteration");

    g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_cicle_vs_small_tree_iteration_exp = 
    	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_cicle_vs_small_tree_iteration_input);


    // big_bipartite_some_edges_vs_big_tree

    start_point = solve_greedy(big_bipartite_some_edges,big_tree);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_big_tree_iteration_input(0, max_iteration, 3,
		repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_1_iteration");

    g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_big_tree_iteration_exp = 
    	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_iteration_input);

    // big_bipartite_some_edges_vs_big_cicle

    start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_big_cicle_iteration_input(0, max_iteration,
		3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_1_iteration");

    g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_big_cicle_iteration_exp = 
    	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_iteration_input);

    // big_bipartite_some_edges_vs_small_complete	


    start_point = solve_greedy(small_complete,big_bipartite_some_edges);

    parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_small_complete_iteration_input(0,
		 max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_1_iteration");

    g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_small_complete_iteration_exp = 
    	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(
    		&big_bipartite_some_edges_vs_small_complete_iteration_input);



    /*iteration_calibrate_exp_suite.add(&big_tree_vs_small_cicle_iteration_exp);

    iteration_calibrate_exp_suite.add(&big_cicle_vs_small_tree_iteration_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_iteration_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_iteration_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_iteration_exp);*/

	// neighbourhood 1

	//big_tree_vs_small_cicle_exp


    start_point = solve_greedy(small_cicle,big_tree);

    parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_tree_vs_small_cicle_iteration_2_input(0, max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_tree_vs_small_cicle_neighbourhood_2_iteration");

    g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_tree_vs_small_cicle_iteration_2_exp = 
    	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_tree_vs_small_cicle_iteration_2_input);

    // big_cicle_vs_small_tree_exp

    start_point = solve_greedy(small_tree,big_tree);

    parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_cicle_vs_small_tree_iteration_2_input(0, max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_cicle_vs_small_tree_2_iteration");

    g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_cicle_vs_small_tree_iteration_2_exp = 
    	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_cicle_vs_small_tree_iteration_2_input);


    // big_bipartite_some_edges_vs_big_tree

    start_point = solve_greedy(big_bipartite_some_edges,big_tree);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_big_tree_iteration_2_input(0, max_iteration, 3,
		repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_2_iteration");

    g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_big_tree_iteration_2_exp = 
    	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_iteration_2_input);

    // big_bipartite_some_edges_vs_big_cicle

    start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

    parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_big_cicle_iteration_2_input(0, max_iteration,
		3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_2_iteration");

    g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_big_cicle_iteration_2_exp = 
    	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_iteration_2_input);

    // big_bipartite_some_edges_vs_small_complete	


    start_point = solve_greedy(small_complete,big_bipartite_some_edges);

    parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int< star_solution >  big_bipartite_some_edges_vs_small_complete_iteration_2_input(0,
		 max_iteration, 3, repetitions_val,
		sample_val, parameters, "../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_2_iteration");

    g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_small_complete_iteration_2_exp = 
    	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(
    		&big_bipartite_some_edges_vs_small_complete_iteration_2_input);



    iteration_calibrate_exp_suite.add(&big_tree_vs_small_cicle_iteration_2_exp);

    iteration_calibrate_exp_suite.add(&big_cicle_vs_small_tree_iteration_2_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_iteration_2_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_iteration_2_exp);

    iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_iteration_2_exp);


    // iteration_calibrate_exp_suite.run();



}
