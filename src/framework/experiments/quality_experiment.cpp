#include "quality_experiment.h"

using namespace std;

quality_experiment::quality_experiment(const std::vector<string> &instances,
                                       const string &instances_directory,
                                       const string &output_file_name,
                                       const int discard_val, const int repetitions_val) {
	this->instances = instances;
	this->instances_directory = instances_directory;
	this->output_file_name = output_file_name;
	this->discard_val = discard_val;
	this->repetitions_val = repetitions_val;
}

void quality_experiment::run() {
	ofstream output_file;
	ifstream instance_file;

	unsigned int m = 0;
	double elapsed_time = 0;

	vector<pair<vector<double>, vector<double>>> instance_results =
	            vector< pair<vector<double>, vector<double>>>(instances.size(),
	            make_pair(vector<double>(repetitions_val, 0), vector<double>(repetitions_val, 0)));

	adj_list_graph<int> g1, g2;

	cout << "Iniciando prueba de calidad '" << output_file_name << "'" << endl;

	for (unsigned int i = 0; i < instances.size(); i++) {
		instance_file.open(instances_directory + "/" + instances[i]);
		io::read_input(instance_file, g1, g2);
		instance_file.close();

		cout << "Experimentando con instancia '" << instances[i] << "'" << endl;
		for (int j = -discard_val; j < repetitions_val; j++) {
			chronometer::start();
			m = solve_instance(g1, g2);
			elapsed_time = chronometer::stop();
			clean_solution();

			if (j >= 0) {
				instance_results[i].first[j] = m;
				instance_results[i].second[j] = elapsed_time;
			}
		}
	}

	output_file.open(output_file_name);

	double solution_average = 0;
	double solution_std_deviation = 0;

	double time_average = 0;
	double time_std_deviation = 0;

	for(unsigned i = 0; i < instance_results.size(); i++){
		for(int j = 0; j < repetitions_val; j++){
			solution_average += instance_results[i].first[j];
			time_average += instance_results[i].second[j];
		}
		solution_average /= repetitions_val;
		time_average /= repetitions_val;

		for(int j = 0; j < repetitions_val; j++){
			solution_std_deviation += pow(instance_results[i].first[j] - solution_average, 2);
			time_std_deviation += pow(instance_results[i].second[j] - time_average, 2);
		}
		solution_std_deviation = sqrt(solution_std_deviation / repetitions_val);
		time_std_deviation = sqrt(time_std_deviation / repetitions_val);

		output_file << instances[i] << " " << solution_average << " " << solution_std_deviation
		            << " " << time_average << " " << time_std_deviation << std::endl;

		solution_average = 0;
		solution_std_deviation = 0;

		time_average = 0;
		time_std_deviation = 0;
	}

	output_file.close();
}

void quality_experiment::clean_solution() {
	// Default behaviour, do nothing
}
