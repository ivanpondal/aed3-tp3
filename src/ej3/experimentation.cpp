
#include "../main.h"
#include "./ej3.h"
#include "../framework/structures/adj_list_graph.h"
#include "../framework/utils/element_generator_int.h"


/*
**  Exercise 3
**  Experimentation
*/
using namespace std;



adj_list_graph<int> random_co_graph(int n){
	// genero n grafos triviales
	vector < adj_list_graph<int> > vec_g (
		n,
		adj_list_graph<int>() 
	);
	for (int i = 0; i < n; ++i){
		vec_g[i].add_node(i);
	}

	element_generator_int e_gen;

	while(n > 1){
		int i = (int) ( (std::rand()*1.0f / RAND_MAX) * n );
		int j = (int) ( (std::rand()*1.0f / RAND_MAX) * n );
		int unite_o_join = std::rand() % 2 ;
		if (unite_o_join == 0){
			vec_g[i].unite(vec_g[j],e_gen);
		}else{
			vec_g[i].join(vec_g[j],e_gen);
		}
		vec_g.erase ( vec_g.begin()+ j  );
		n--;
	} 

	return vec_g[0];

}

void run_experimentation() {
    adj_list_graph<int> co_g = random_co_graph(5);
    cout << "co_g: " << endl;
    cout << co_g << endl;
}
