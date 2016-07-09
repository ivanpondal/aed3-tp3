#ifndef QUALITY_EXPERIMENT_H_
#define QUALITY_EXPERIMENT_H_

#include <vector>
#include <utility>
#include <cmath>
#include <string>

#include "../utils/io.h"
#include "../utils/chronometer.h"
#include "../structures/adj_list_graph.h"
#include "../experiments/experiment.h"

class quality_experiment: public experiment {
	public:
		quality_experiment(const std::vector<std::string> &instances,
		                   const std::string &instances_directory,
		                   const std::string &output_file_name,
		                   const int discard_val, const int repetitions_val);
		void run();
	private:
		virtual unsigned int solve_instance(graph<int> &g1, graph<int> &g2) = 0;
		virtual void clean_solution();
		std::vector<std::string> instances;
		std::string instances_directory;
		std::string output_file_name;
		int discard_val;
		int repetitions_val;
};

#endif // QUALITY_EXPERIMENT_H_INCLUDED
