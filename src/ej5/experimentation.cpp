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


	cout << "g1.n() : " << g1.n() << endl;
	cout << "g2.n() : " << g2.n() << endl;

	if (g1.n() <= g2.n()) {
		small_graph = &g1;
		large_graph = &g2;
	} else {
		small_graph = &g2;
		large_graph = &g1;
	}

	graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
	graph< pair<int, int> >* h  = solve_local_search(*small_graph, *large_graph, *start_point, 2,reps,
		0.002f,true);

	int res = h->m();

	delete start_point;
	delete h;

	cout << "h->m() :  " << res << endl;

	return res;
}

void quality_exp_local_search_with_swap::clean_solution() {
}


unsigned int quality_exp_local_search_without_swap::solve_instance(graph<int> &g1, graph<int> &g2) {

	graph<int>* large_graph, * small_graph;

	// Local search solver assumes g1 has at most as many nodes as g2. If that
	// is not the case, we have to exchange both graphs before passing them
	// to the function, and remember this fact so that we can read correctly
	// the obtained solution


	cout << "g1.n() : " << g1.n() << endl;
	cout << "g2.n() : " << g2.n() << endl;
	int res = 0;
	if(	g1.n() == g2.n() ){
		cout << "h->m() :  " << -1 << endl;

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
		graph<pair<int, int>>* h = solve_local_search(*small_graph, *large_graph, *start_point, 1,reps,
			0.002f,true);
		res = h->m();

		delete start_point;
		delete h;


	}
	cout << "h->m() :  " << res << endl;


	return res;
}



void quality_exp_local_search_without_swap::clean_solution() {


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
		int percentage = (int) ( input->get_inc_val() * 100.0f);
		if (percentage % 20 == 0){
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
		*input->get_subject().greedy_solve,2,-1,input->get_inc_val(),true);
		last_h_m = h->m();
	}else{
		int percentage = (int) ( input->get_inc_val() * 100.0f);
		if (percentage % 20 == 0){
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
		*input->get_subject().greedy_solve,1,input->get_inc_val(),0.1f,true);
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
		*input->get_subject().greedy_solve,2,input->get_inc_val(), 0.1f, true);
	cout << "h->m() :  " << h->m() << endl;
	return h->m();

}

// Experiments

void run_experimentation(){

	/*
	*  Define experiments
	*/

	experiment_suite quality_exp_suite;
	experiment_suite  neighbourhood_proportion_calibrate_exp_suite;
	experiment_suite  iteration_calibrate_exp_suite;

	// Quality

	int repetitions_val = 1;

	// // quality local_search_2_exp
	// quality_exp_local_search_with_swap local_search_2_exp(
	// 		known_solution_instances, "../exp/ej5/known_solution_instances_search_2_exp", 0, repetitions_val);


	// // quality local_search_1_exp 50 iterates (change reps in .h!!!)
	// quality_exp_local_search_without_swap local_search_1_exp(
	// 		known_solution_instances, "../exp/ej5/known_solution_instances_search_1_exp", 0, repetitions_val);


	// // quality local_search_1_exp 100 iterates
	// quality_exp_local_search_without_swap local_search_1_exp(
	// 		known_solution_instances, "../exp/ej5/known_solution_instances_search_1_exp_100", 0, repetitions_val);

	// quality similar_nodes_count_instance_generation

	quality_exp_local_search_with_swap local_search_2_exp_similar_nodes_count(
			similar_nodes_count_instances, "../exp/ej5/similar_nodes_count_instance_generation_2_exp",
			0, repetitions_val);

	quality_exp_local_search_without_swap local_search_1_exp_similar_nodes_count(
			similar_nodes_count_instances, "../exp/ej5/similar_nodes_count_instance_generation_1_exp",
			0, repetitions_val);

	// quality diferents_nodes_count_instances

	quality_exp_local_search_with_swap local_search_2_exp_diferents_nodes_count(
			diferents_nodes_count_instances, "../exp/ej5/diferents_nodes_count_instance_generation_2_exp",
			0, repetitions_val);

	quality_exp_local_search_without_swap local_search_1_exp_diferents_nodes_count(
			diferents_nodes_count_instances, "../exp/ej5/diferents_nodes_count_instance_generation_1_exp",
			0, repetitions_val);



	// Neighbourhood proportion

	repetitions_val = 5;
	int sample_val = 5;
	int sample_val_granular = 40;

	element_generator_int e_gen;

	// generate graph families
	adj_list_graph<int> big_tree;
	graph_factory<int>::add_n_tree_vertices(big_tree, e_gen, 600);
	e_gen.reset();

	adj_list_graph<int> small_tree;
	graph_factory<int>::add_n_tree_vertices(small_tree, e_gen, 300);
	e_gen.reset();

	adj_list_graph<int> small_complete;
	graph_factory<int>::add_n_vertices_and_all_edges(small_complete, e_gen, 150);
	e_gen.reset();

	adj_list_graph<int> big_cicle =
		graph_factory<int>::cycle_graph(e_gen, 600);
	e_gen.reset();

	adj_list_graph<int> small_cicle =
		graph_factory<int>::cycle_graph(e_gen, 300);
	e_gen.reset();

	adj_list_graph<int> big_bipartite_some_edges =
		graph_factory<int>::random_bipartite_graph(e_gen, 150, 150,0.5f);
	e_gen.reset();

	star_solution parameters;
	graph<pair<int, int>>* start_point;

	// Neighbourhood I

	// big_tree_vs_small_cicle_exp (I1)

	start_point = solve_greedy(small_cicle,big_tree);

	parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_tree_vs_small_cicle_input(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_1_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_tree_vs_small_cicle_input_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_1_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_tree_vs_small_cicle_exp =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_tree_vs_small_cicle_input);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_tree_vs_small_cicle_exp_granular =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_tree_vs_small_cicle_input_granular);

	// big_cicle_vs_small_tree_exp (I2)

	start_point = solve_greedy(small_tree,big_tree);

	parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;


	incremental_experiment_input_float<star_solution> big_cicle_vs_small_tree_input(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_cicle_vs_small_tree_1_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_cicle_vs_small_tree_input_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_cicle_vs_small_tree_1_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_cicle_vs_small_tree_exp =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_cicle_vs_small_tree_input);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_cicle_vs_small_tree_exp_granular =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_cicle_vs_small_tree_input_granular);

	// big_bipartite_some_edges_vs_big_tree (I3)

	start_point = solve_greedy(big_bipartite_some_edges,big_tree);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_tree_input(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_1_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_tree_input_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_1_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp_granular =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input_granular);

	// big_bipartite_some_edges_vs_big_cicle (I4)

	start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_cicle_input(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_1_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_cicle_input_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_1_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp_granular =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input_granular);

	// big_bipartite_some_edges_vs_empeorar_complete (I5)

	start_point = solve_greedy(small_complete,big_bipartite_some_edges);

	parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_small_complete_input(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_1_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_small_complete_input_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_1_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input);

	g1_vs_g2_neighbourhood_1_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp_granular =
		g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input_granular);


	// Neighbourhood II

	// big_tree_vs_small_cicle_exp (I1)

	start_point = solve_greedy(small_cicle,big_tree);

	parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_tree_vs_small_cicle_input_2(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_2_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_tree_vs_small_cicle_input_2_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_2_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_tree_vs_small_cicle_exp_2 =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_tree_vs_small_cicle_input_2);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_tree_vs_small_cicle_exp_2_granular =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_tree_vs_small_cicle_input_2_granular);

	// big_cicle_vs_small_tree_exp (I2)

	start_point = solve_greedy(small_tree,big_tree);

	parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_cicle_vs_small_tree_input_2(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_cicle_vs_small_tree_neighbourhood_2_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_cicle_vs_small_tree_input_2_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_cicle_vs_small_tree_neighbourhood_2_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_cicle_vs_small_tree_exp_2 =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_cicle_vs_small_tree_input_2);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_cicle_vs_small_tree_exp_2_granular =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_cicle_vs_small_tree_input_2_granular);

	// big_bipartite_some_edges_vs_big_tree (I3)

	start_point = solve_greedy(big_bipartite_some_edges,big_tree);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_tree_input_2(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_2_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_tree_input_2_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_2_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp_2 =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input_2);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_tree_exp_2_granular =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_input_2_granular);

	// big_bipartite_some_edges_vs_big_cicle (I4)

	start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_cicle_input_2(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_2_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_big_cicle_input_2_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_2_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp_2 =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input_2);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_big_cicle_exp_2_granular =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_input_2_granular);

	// big_bipartite_some_edges_vs_small_complete (I5)

	start_point = solve_greedy(small_complete,big_bipartite_some_edges);

	parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_small_complete_input_2(
		0.0f, // min_val
		1.0f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_2_proportion" // exp_name
	);

	incremental_experiment_input_float<star_solution> big_bipartite_some_edges_vs_small_complete_input_2_granular(
		0.0f, // min_val
		0.2f, // max_val
		0, // discard_val
		repetitions_val, // repetitions_val
		sample_val_granular, // samples_val
		parameters, // subject_val
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_2_proportion_granular" // exp_name
	);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp_2 =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input_2);

	g1_vs_g2_neighbourhood_2_proportion_incremental_experiment big_bipartite_some_edges_vs_small_complete_exp_2_granular =
		g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(&big_bipartite_some_edges_vs_small_complete_input_2_granular);


	// Iteration count
	repetitions_val = 3;
	sample_val = 20;
	int max_iteration = 200;

	// Neighbourhood I

	// big_tree_vs_small_cicle_exp

	start_point = solve_greedy(small_cicle,big_tree);

	parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_tree_vs_small_cicle_iteration_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_1_iteration"
	);

	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_tree_vs_small_cicle_iteration_exp =
		g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_tree_vs_small_cicle_iteration_input);

	// big_cicle_vs_small_tree_exp

	start_point = solve_greedy(small_tree,big_tree);

	parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_cicle_vs_small_tree_iteration_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_cicle_vs_small_tree_neighbourhood_1_iteration"
	);

	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_cicle_vs_small_tree_iteration_exp =
		g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_cicle_vs_small_tree_iteration_input);

	// big_bipartite_some_edges_vs_big_tree

	start_point = solve_greedy(big_bipartite_some_edges,big_tree);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_big_tree_iteration_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_1_iteration"
	);

	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_big_tree_iteration_exp =
		g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_iteration_input);

	// big_bipartite_some_edges_vs_big_cicle

	start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_big_cicle_iteration_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_1_iteration"
	);

	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_big_cicle_iteration_exp =
		g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_iteration_input);

	// big_bipartite_some_edges_vs_small_complete

	start_point = solve_greedy(small_complete,big_bipartite_some_edges);

	parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_small_complete_iteration_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_1_iteration"
	);

	g1_vs_g2_neighbourhood_1_iterations_incremental_experiment big_bipartite_some_edges_vs_small_complete_iteration_exp =
		g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(
			&big_bipartite_some_edges_vs_small_complete_iteration_input);


	// Neighbourhood 2

	// big_tree_vs_small_cicle_exp

	start_point = solve_greedy(small_cicle,big_tree);

	parameters.g1 =  small_cicle;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_tree_vs_small_cicle_iteration_2_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_tree_vs_small_cicle_neighbourhood_2_iteration"
	);

	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_tree_vs_small_cicle_iteration_2_exp =
		g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_tree_vs_small_cicle_iteration_2_input);

	// big_cicle_vs_small_tree_exp

	start_point = solve_greedy(small_tree,big_tree);

	parameters.g1 =  small_tree;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_cicle_vs_small_tree_iteration_2_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_cicle_vs_small_tree_neighbourhood_2_iteration"
	);

	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_cicle_vs_small_tree_iteration_2_exp =
		g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_cicle_vs_small_tree_iteration_2_input);

	// big_bipartite_some_edges_vs_big_tree

	start_point = solve_greedy(big_bipartite_some_edges,big_tree);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_tree;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_big_tree_iteration_2_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_big_tree_neighbourhood_2_iteration"
	);

	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_big_tree_iteration_2_exp =
		g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_tree_iteration_2_input);

	// big_bipartite_some_edges_vs_big_cicle

	start_point = solve_greedy(big_bipartite_some_edges,big_cicle);

	parameters.g1 =  big_bipartite_some_edges;
	parameters.g2 =  big_cicle;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_big_cicle_iteration_2_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_big_cicle_neighbourhood_2_iteration"
	);

	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_big_cicle_iteration_2_exp =
		g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(&big_bipartite_some_edges_vs_big_cicle_iteration_2_input);

	// big_bipartite_some_edges_vs_small_complete

	start_point = solve_greedy(small_complete,big_bipartite_some_edges);

	parameters.g1 =  small_complete;
	parameters.g2 =  big_bipartite_some_edges;
	parameters.greedy_solve = start_point;

	incremental_experiment_input_int<star_solution> big_bipartite_some_edges_vs_small_complete_iteration_2_input(
		0,
		max_iteration,
		0,
		repetitions_val,
		sample_val,
		parameters,
		"../exp/ej5/big_bipartite_some_edges_vs_small_complete_neighbourhood_2_iteration"
	);

	g1_vs_g2_neighbourhood_2_iterations_incremental_experiment big_bipartite_some_edges_vs_small_complete_iteration_2_exp =
		g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(
			&big_bipartite_some_edges_vs_small_complete_iteration_2_input);

	/*
    *  Add experiments to suites
    */


	// // Quality
	// quality_exp_suite.add(&local_search_1_exp);
	// quality_exp_suite.add(&local_search_2_exp);
	// quality_exp_suite.add(&local_search_1_exp_similar_nodes_count);
	// quality_exp_suite.add(&local_search_2_exp_similar_nodes_count);
	quality_exp_suite.add(&local_search_2_exp_diferents_nodes_count);
	quality_exp_suite.add(&local_search_1_exp_diferents_nodes_count);


	// Neighbourhood proportion
	// Neighbourhood I
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp_granular);

	// Neighbourhood II
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp_2);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_tree_vs_small_cicle_exp_2_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp_2);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_cicle_vs_small_tree_exp_2_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp_2);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_exp_2_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp_2);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_exp_2_granular);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp_2);
	// neighbourhood_proportion_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_exp_2_granular);

	// Iteration count
	// Neighbourhood I
	// iteration_calibrate_exp_suite.add(&big_tree_vs_small_cicle_iteration_exp);
	iteration_calibrate_exp_suite.add(&big_cicle_vs_small_tree_iteration_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_iteration_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_iteration_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_iteration_exp);

	// Neighbourhood II
	// iteration_calibrate_exp_suite.add(&big_tree_vs_small_cicle_iteration_2_exp);
	// iteration_calibrate_exp_suite.add(&big_cicle_vs_small_tree_iteration_2_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_tree_iteration_2_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_big_cicle_iteration_2_exp);
	// iteration_calibrate_exp_suite.add(&big_bipartite_some_edges_vs_small_complete_iteration_2_exp);


	/*
    *  Run experiments
    */

	quality_exp_suite.run();
	// neighbourhood_proportion_calibrate_exp_suite.run();
	// iteration_calibrate_exp_suite.run();

}
