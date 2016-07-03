#include "ej2.h"

using namespace std;

solution run_solver(graph<int> &g1, graph<int> &g2) {
    graph<std::pair<int, int>> *maxComSub = solve_backtracking(&g1, &g2);
    return pairs_to_solution(*maxComSub);
}
