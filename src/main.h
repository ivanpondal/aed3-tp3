#ifndef AED3_TP3_MAIN_H
#define AED3_TP3_MAIN_H

#include <iostream>      // cout, cin, <<
#include <fstream>       // open, close, <<
#include <iomanip>       // stoi
#include <unistd.h>      // getopt
#include <vector>        // vector
#include <unordered_set> // unordered_set
#include <utility>
#include <string>

#include "framework/utils/element_generator.h"
#include "framework/utils/io.h"
#include "framework/structures/graph.h"
#include "framework/structures/adj_list_graph.h"

extern bool verbose;

// Imprimir ayuda por pantalla
void show_help(char* bin_path);

// Funciones principales
solution run_solver(graph<int>& g1, graph<int>& g2);
void run_unit_tests();
void run_experimentation();

// Funciones auxiliares
solution pairs_to_solution(const graph<std::pair<int, int>>&, bool invert = false);

// Verifica que una solución sea válida
bool check_solution(const solution& s, const graph<int>& g1, const graph<int>& g2);

// Compara dos vectores
template <typename T>
bool compare_vectors(const std::vector<T> v1, const std::vector<T> v2) {
    if (v1.size() != v2.size()) {
        return false;
    } else {
        for (unsigned int i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
    }
    return true;
}

// Imprime un vector
template <typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    bool first = true;
    for (typename std::vector<T>::const_iterator it = v.begin();
        it != v.end(); ++it)
    {
        if (! first) {
            os << ", ";
        } else {
            first = false;
        }
        os << *it;
    }
    os << "]";
    return os;
}

// Imprime un par de enteros
std::ostream &operator<<(std::ostream& output, const std::pair<int, int>& p);

// Función de hash para pares de enteros
struct hash_pair_int{
    size_t operator()(const std::pair<int, int> &p) const{
        size_t seed = 0;
        seed ^= std::hash<int>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

// Instancias de grafos para experimentar

const std::string generated_instances_directory = "generated_instances";

const std::vector<std::string> known_solution_instances = {
    "aleatorio_n5_c025",
    "aleatorio_n5_c050",
    "aleatorio_n5_c075",
    "cografo_n100_k50",
    "cografo_n50_k100",
    "aleatorio_subgrafo_n500_c025",
    "aleatorio_subgrafo_n500_c050",
    "aleatorio_subgrafo_n500_c075",
    "arbol_subgrafo_n500",
    "completo_subgrafo_n500",
    "ciclo_subgrafo_n500",
    "aleatorio_bipartito_vs_completo_n500_k500_c050",
    "aleatorio_bipartito_vs_completo_n250_k500_c050",
    "bosque_vs_completo_n1000_d10",
    "aleatorio_vs_completo_n1000_d10_c050"
};

const std::vector<std::string> unknown_solution_instances = {
    "aleatorio_n1000_c025",
    "aleatorio_n1000_c050",
    "aleatorio_n1000_c075",
    "arbol_n1000",
    "aleatorio_bipartito_n500_k500_c050",
    "aleatorio_bipartito_n250_k500_c050",
    "bosque_n1000_d10_v025",
    "aleatorio_n1000_d10_c050_v025"
};

const std::vector<std::string> greedy_solution_instances = {
    "greedy_solution_instances"
};

#endif  // AED3_TP3_MAIN_H
