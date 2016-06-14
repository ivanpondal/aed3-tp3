#ifndef MAIN_H
#define MAIN_H

#include <iostream>      // cout, cin, <<
#include <fstream>       // open, close, <<
#include <iomanip>       // stoi
#include <unistd.h>      // getopt
#include <vector>        // vector

// Imprimir ayuda por pantalla
void show_help(char* bin_path);

// Funciones principales
extern bool verbose;
void run_solution();
void run_unit_tests();
void run_experimentation();

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
    for (typename std::vector<T>::const_iterator it = v.begin();
        it != v.end(); ++it)
    {
        os << *it << ", ";
    }
    os << "\b\b]";
    return os;
}

#endif
