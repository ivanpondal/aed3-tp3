#ifndef EXPERIMENT_SUITE_H_
#define EXPERIMENT_SUITE_H_

#include "experiment.h"
#include <queue>

template <typename IN>
class experiment_suite{
	public:
		void add(experiment<IN> *input);
		void run();
	private:
		std::queue< experiment<IN>*> experiments_queue;
};

template <typename IN>
void experiment_suite<IN>::add(experiment<IN> *input){
	experiments_queue.push(input);
}

template <typename IN>
void experiment_suite<IN>::run(){
	while(!experiments_queue.empty()){
		experiments_queue.front()->run();
		experiments_queue.pop();
	}
}
#endif // EXPERIMENT_SUITE_H_INCLUDED
