#include "./ej5.h"
#include "../framework/structures/adj_list_graph.h"
#include <vector>

using namespace std; 

/*
**  Exercise 5
**  Problem solver
*/

graph<pair<int, int>>  run_solver(graph<int>& g1, graph<int>& g2) {
    std::cout << "Nothing here yet :/" << std::endl;

    return local_search(solver(g1,g2));
}


graph<pair<int, int>> local_search(pair<graph,graph>  solution){
	vector<graph<pair<int, int>> > neighbors = neighbor_solutions(solution);
	bool has_better;
	do{
		has_better = find_better_solution(solution,neighbors) ;
	}while( has_better );
}

vector<graph<pair<int, int>> > neighbor_solutions(pair<graph,graph>  solution){
	vector<graph<pair<int, int>> > neighbors;
	return neighbors;
} 

bool find_better_solution(pair<graph,graph>  &solution, vector<graph<pair<int, int>> > &neighbors){

	for (int i = 0; i < neighbors.size(); ++i){
		if(neighbors[i]->m() > solution->m()){
			solution = neighbors[i];
			return true;
		}	
	}

	return false;
}