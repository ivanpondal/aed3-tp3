#ifndef ELEMENT_GENERATOR_INT_H_
#define ELEMENT_GENERATOR_INT_H_

#include "element_generator.h"

class element_generator_int: public element_generator<int>{
	private:
		int get_next(const graph<int> &g);
};

#endif // ELEMENT_GENERATOR_INT_H_INCLUDED
