#include "experiment_suite.h"

void experiment_suite::add(experiment *input){
	experiments_queue.push(input);
}

void experiment_suite::run(){
	while(!experiments_queue.empty()){
		experiments_queue.front()->run();
		experiments_queue.pop();
	}
}
