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
class incremental_experiment: public experiment<incremental_experiment_input<T, S>>{
	public:
		void run(incremental_experiment_input<T, S> &input);
	private:
		virtual const char *get_experiment_name() const = 0;
		virtual void load_instance(incremental_experiment_input<T, S> *input) = 0;
		virtual void solve_instance(incremental_experiment_input<T, S> *input) = 0;
		void print_results();
		std::vector< std::pair<T, std::vector<T>>> times_vec;
};

template <typename T, typename S>
void incremental_experiment<T, S>::run(incremental_experiment_input<T, S> &input){
	times_vec = std::vector< std::pair<T, std::vector<T>>>(input.get_samples(),
	            std::make_pair(T(), std::vector<T>(input.get_repetitions(), T())));
	input.init();

	double elapsed_time = 0;
	for (int i = 0; i < input.get_samples(); i++) {

		load_instance(&input);

		times_vec[i].first = input.get_inc_val();

		for (int j = -input.get_discard(); j < input.get_repetitions(); j++) {
			chronometer::start();
			solve_instance(&input);
			elapsed_time = chronometer::stop();

			if (j >= 0) {
				times_vec[i].second[j] = elapsed_time;
			}
		}
		input.get_inc_val() += input.get_delta();
	}

	print_results();
}

template <typename T, typename S>
void incremental_experiment<T, S>::print_results(){
	std::ofstream output_file;

	output_file.open(get_experiment_name());

	for(unsigned i = 0; i < times_vec.size(); i++){
		T x = times_vec[i].first;
		std::vector<T> ys = times_vec[i].second;

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

#endif // INCREMENTAL_EXPERIMENT_H_INCLUDED