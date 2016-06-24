#include "./ej5.h"
#include "../framework/structures/adj_list_graph.h"
#include <vector>

/*
**  Exercise 5
**  Problem solver
*/

using namespace std;

solution run_solver(graph<int>& g1, graph<int>& g2) {
    graph<pair<int, int>>* start_point = solve_greedy(g1, g2);
    graph<pair<int, int>>* h = solve_local_search_1(g1, g2, *start_point);

    solution ret = pairs_to_solution(*h);

    delete start_point;
    delete h;

    return ret;
}
