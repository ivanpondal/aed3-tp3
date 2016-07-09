#include "ej2.h"

solution run_solver(graph<int> &g1, graph<int> &g2) {
    graph<std::pair<int, int>> *maxComSub = solve_backtracking(&g1, &g2);
    solution sol = pairs_to_solution(*maxComSub);

    delete maxComSub;

    return sol;
}
