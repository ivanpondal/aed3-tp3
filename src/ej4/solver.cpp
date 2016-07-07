#include "ej4.h"

solution run_solver(graph<int>& g1, graph<int>& g2){
	graph<std::pair<int, int>> *maxComSub = solve_greedy(g1, g2, true);
	solution sol = pairs_to_solution(*maxComSub);

	delete maxComSub;

	return sol;
}
