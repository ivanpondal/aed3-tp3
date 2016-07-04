#ifndef AED3_TP3_MAIN_H
#define AED3_TP3_MAIN_H

#include <iostream>      // cout, cin, <<
#include <fstream>       // open, close, <<
#include <iomanip>       // stoi
#include <unistd.h>      // getopt
#include <vector>        // vector
#include <unordered_set> // unordered_set
#include <utility>

#include "framework/structures/graph.h"
#include "framework/utils/element_generator.h"
#include "framework/structures/adj_list_graph.h"

extern bool verbose;

// Imprimir ayuda por pantalla
void show_help(char* bin_path);

// Funciones principales
struct solution {
    graph<int>* h;
    std::vector<int> g1_mapping;
    std::vector<int> g2_mapping;

    ~solution() {
        delete h;
    }
};

solution run_solver(graph<int>& g1, graph<int>& g2);
void run_unit_tests();
void run_experimentation();

// Funciones de entrada/salida
void read_input(std::istream& is, graph<int>& g1, graph<int>& g2);
solution pairs_to_solution(const graph<std::pair<int, int>>&);
void print_solution(std::ostream& os, const solution& sol);
void print_vector(std::ostream& os, const std::vector<int>& v);
void print_edges(std::ostream& os, const graph<int>* g);

// Funciones auxiliares

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

#endif  // AED3_TP3_MAIN_H
