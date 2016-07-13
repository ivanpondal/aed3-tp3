#ifndef AED3_TP3_EJ5_H
#define AED3_TP3_EJ5_H
#include <utility>

#include "../main.h"
#include "../heuristics/heuristics.h"
#include "../framework/experiments/experiment_suite.h"
#include "../framework/experiments/quality_experiment.h"
#include "../framework/utils/element_generator_int.h"
#include "../framework/utils/graph_factory.h"
#include "../framework/experiments/quality_incremental_experiment.h"
#include "../framework/experiments/input/incremental_experiment_input_int.h"
#include "../framework/experiments/input/incremental_experiment_input_float.h"


/*
**  Exercise 5
*/

// Here go declarations of functions which are exported by the problem solver,
// global variables, etc.


struct star_solution {
	adj_list_graph<int> g1;
	adj_list_graph<int> g2;
	graph<std::pair<int, int>> *greedy_solve;
};


// Local search , neighbourhood without swap

class quality_exp_local_search_without_swap: public quality_experiment {
	public:
		quality_exp_local_search_without_swap(std::vector<std::string> instances, const std::string &output_file_name,
		                   const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* h;
};

// Local search , neighbourhood with swap


class quality_exp_local_search_with_swap: public quality_experiment {
	public:
		quality_exp_local_search_with_swap(std::vector<std::string> instances, const std::string &output_file_name,
		                   const int discard_val, const int repetitions_val):
		quality_experiment(instances, generated_instances_directory,
		                   output_file_name, discard_val, repetitions_val){};
	private:
		unsigned int solve_instance(graph<int> &g1, graph<int> &g2);
		void clean_solution();
		graph<std::pair<int, int>>* h;
};

class g1_vs_g2_neighbourhood_1_proportion_incremental_experiment:public quality_incremental_experiment< float,
	 star_solution >{
    public:
        g1_vs_g2_neighbourhood_1_proportion_incremental_experiment(const incremental_experiment_input< float, 
        	star_solution > *input): quality_incremental_experiment(input){

        };
    private:
        void load_instance(incremental_experiment_input< float, star_solution > *input);
        int solve_instance(incremental_experiment_input< float, star_solution >*input);
};

class g1_vs_g2_neighbourhood_2_proportion_incremental_experiment:public quality_incremental_experiment< float,
	 star_solution >{
    public:
        g1_vs_g2_neighbourhood_2_proportion_incremental_experiment(const incremental_experiment_input< float, 
        	star_solution > *input): quality_incremental_experiment(input){

        };
    private:
        void load_instance(incremental_experiment_input< float, star_solution > *input);
        int solve_instance(incremental_experiment_input< float, star_solution >*input);
};

class g1_vs_g2_neighbourhood_2_iterations_incremental_experiment:public quality_incremental_experiment< int,
	 star_solution >{
    public:
        g1_vs_g2_neighbourhood_2_iterations_incremental_experiment(const incremental_experiment_input< int, 
        	star_solution > *input): quality_incremental_experiment(input){

        };
    private:
        void load_instance(incremental_experiment_input< int, star_solution > *input);
        int solve_instance(incremental_experiment_input< int, star_solution >*input);
};

class g1_vs_g2_neighbourhood_1_iterations_incremental_experiment:public quality_incremental_experiment< int,
	 star_solution >{
    public:
        g1_vs_g2_neighbourhood_1_iterations_incremental_experiment(const incremental_experiment_input< int, 
        	star_solution > *input): quality_incremental_experiment(input){

        };
    private:
        void load_instance(incremental_experiment_input< int, star_solution > *input);
        int solve_instance(incremental_experiment_input< int, star_solution >*input);
};



#endif  // AED3_TP3_EJ5_H