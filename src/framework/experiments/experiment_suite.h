#ifndef EXPERIMENT_SUITE_H_
#define EXPERIMENT_SUITE_H_

#include "experiment.h"
#include <queue>

class experiment_suite{
	public:
		void add(experiment *input);
		void run();
	private:
		std::queue< experiment*> experiments_queue;
};

#endif // EXPERIMENT_SUITE_H_INCLUDED
