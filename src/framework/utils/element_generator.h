#ifndef ELEMENT_GENERATOR_H_
#define ELEMENT_GENERATOR_H_

#include "../structures/graph.h"

template <typename T>
class element_generator{
	public:
		T generate(const graph<T> &g);
		void reset();
	private:
		virtual T get_next(const graph<T> &g) = 0;
	protected:
		int next_count = 0;
};

template <typename T>
T element_generator<T>::generate(const graph<T> &g){
	T new_element = get_next(g);

	while(g.contains(new_element)){
		new_element = get_next(g);
	}

	return new_element;
}

template <typename T>
void element_generator<T>::reset(){
	next_count = 0;
}

#endif // ELEMENT_GENERATOR_H_INCLUDED