#include "./ej6.h"
#include "../framework/structures/adj_list_graph.h"

/*
**  Exercise 6
**  Problem solver
*/

using namespace std;

solution run_solver(graph<int>& g1, graph<int>& g2) {
    graph<int>* large_graph, * small_graph;
    bool invert;

    // Local search solver assumes g1 has at most as many nodes as g2. If that
    // is not the case, we have to exchange both graphs before passing them
    // to the function, and remember this fact so that we can read correctly
    // the obtained solution
    if (g1.n() <= g2.n()) {
        small_graph = &g1;
        large_graph = &g2;
        invert = false;
    } else {
        small_graph = &g2;
        large_graph = &g1;
        invert = true;
    }

    graph<pair<int, int>>* start_point = solve_greedy(*small_graph, *large_graph);
    graph<pair<int, int>>* h = solve_tabu(*small_graph, *large_graph, *start_point, 1, 1000);

    solution ret = pairs_to_solution(*h, invert);

    delete start_point;
    delete h;

    return ret;
}
