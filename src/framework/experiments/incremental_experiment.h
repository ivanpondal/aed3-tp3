#ifndef INCREMENTAL_EXPERIMENT_H_
#define INCREMENTAL_EXPERIMENT_H_

#include "experiment.h"
#include "input/incremental_experiment_input.h"
#include "../utils/chronometer.h"
#include <vector>
#include <utility>
#include <fstream>
#include <cmath>

template <typename T, typename S>
class incremental_experiment: public experiment{
	public:
		incremental_experiment(const incremental_experiment_input<T, S> *input, bool print = true);
		~incremental_experiment();
		void init(const incremental_experiment_input<T, S> *input);
		void run();
	private:
		virtual void load_instance(incremental_experiment_input<T, S> *input) = 0;
		virtual void solve_instance(incremental_experiment_input<T, S> *input) = 0;
		virtual void clean_solution();
		void print_results();
		std::vector< std::pair<T, std::vector<double>>> times_vec;
		incremental_experiment_input<T, S> *input = NULL;
		bool print;
};

template <typename T, typename S>
incremental_experiment<T, S>::incremental_experiment(const incremental_experiment_input<T, S> *input, bool print){
	init(input);
	this->print = print;
}

template <typename T, typename S>
incremental_experiment<T, S>::~incremental_experiment(){
	delete input;
}

template <typename T, typename S>
void incremental_experiment<T, S>::init(const incremental_experiment_input<T, S> *input){
	delete this->input;
	this->input = input->clone();
}

template <typename T, typename S>
void incremental_experiment<T, S>::run(){
	times_vec = std::vector< std::pair<T, std::vector<double>>>(input->get_samples(),
	            std::make_pair(T(), std::vector<double>(input->get_repetitions(), 0)));
	input->init();

	double elapsed_time = 0;
	for (int i = 0; i < input->get_samples(); i++) {

		load_instance(input);

		times_vec[i].first = input->get_inc_val();

		for (int j = -input->get_discard(); j < input->get_repetitions(); j++) {
			chronometer::start();
			solve_instance(input);
			elapsed_time = chronometer::stop();
			clean_solution();

			if (j >= 0) {
				times_vec[i].second[j] = elapsed_time;
			}
		}
		input->get_inc_val() += input->get_delta();
	}

	if(print){
		print_results();
	}
}

template <typename T, typename S>
void incremental_experiment<T, S>::print_results(){
	std::ofstream output_file;

	output_file.open(input->get_exp_name());

	for(unsigned i = 0; i < times_vec.size(); i++){
		T x = times_vec[i].first;
		std::vector<double> ys = times_vec[i].second;

		double average = 0;
		double std_deviation = 0;

		for(unsigned int j = 0; j < ys.size(); j++){
			average += ys[j];
		}
		average = average / ys.size();

		for(unsigned int j = 0; j < ys.size(); j++){
			std_deviation += pow(ys[j] - average, 2);
		}
		std_deviation = sqrt(std_deviation / ys.size());

		output_file << x << " " << average << " " << std_deviation << std::endl;
	}

	output_file.close();
}

template <typename T, typename S>
void incremental_experiment<T, S>::clean_solution() {
	// Default behaviour, do nothing
}

#endif // INCREMENTAL_EXPERIMENT_H_INCLUDED
