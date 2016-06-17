#include "element_generator_int.h"

int element_generator_int::get_next(const graph<int> &g){
	int next = 0;
	if(next_count == 0){
		next = g.n();
	}
	else{
		next = g.n() + next_count;
	}
	next_count++;
	return next;
}
