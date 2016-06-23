#include "./main.h"

using namespace std;

// Modos de ejecución
enum mode {solver, test, experimentation};

bool verbose = false;

int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    mode exec_mode = solver;

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "hvte:")) != -1) {
        switch (opt) {
            case 'h': { // mostrar ayuda
                show_help(argv[0]);
                exit(0);
                break;
            }
            case 'v': { // ser verboso
                verbose = true;
                break;
            }
            case 't': { // correr tests unitarios
                exec_mode = test;
                break;
            }
            case 'e': { // correr pruebas de performance
                srand(stoi(optarg)); // configura el seed que recibe por parámetro
                exec_mode = experimentation;
                break;
            }
            default: { // si las opciones son inválidas
                show_help(argv[0]);
                exit(1);
                break;
            }
        }
    }

    if (exec_mode == solver) {
        adj_list_graph<int> g1;
        adj_list_graph<int> g2;
        read_input(cin, g1, g2);
        solution res = run_solver(g1, g2);
        print_solution(cout, res);
    }
    else if (exec_mode == test) {
        run_unit_tests();
    }
    else if (exec_mode == experimentation) {
        run_experimentation();
    }
}

// Imprime por pantalla un texto de ayuda
void show_help(char* bin_path) {
    cout << "  Modo de uso: " << setw(12) << bin_path << endl;
    cout << endl;
    cout << "  Los parámetros se reciben a través de la entrada estándar." << endl;
    cout << endl;
    cout << "  Opciones:" << endl;
    cout << "    -h          Muestra este texto de ayuda" << endl;
    cout << "    -t          Ejecuta los tests unitarios provistos para el algoritmo" << endl;
    cout << "    -p <seed>   Ejecuta las pruebas de performance diseñadas para el algoritmo" << endl;
}

// Funciones de entrada/salida

void read_input(std::istream& is, graph<int>& g1, graph<int>& g2) {
    uint n1, n2, m1, m2;
    is >> n1 >> n2 >> m1 >> m2;

    for (uint i = 0; i < n1; i++) {
        g1.add_node(i);
    }
    for (uint i = 0; i < n2; i++) {
        g2.add_node(i);
    }

    int vertex_1, vertex_2;
    for (uint i = 0; i < m1; i++) {
        is >> vertex_1 >> vertex_2;
        g1.add_edge(vertex_1, vertex_2);
    }
    for (uint i = 0; i < m2; i++) {
        is >> vertex_1 >> vertex_2;
        g2.add_edge(vertex_1, vertex_2);
    }
}

void print_solution(std::ostream& os, const solution& sol) {
    os << sol.h->n() << " " << sol.h->m() << std::endl;
    print_vector(os, sol.g1_mapping);
    os << std::endl;
    print_vector(os, sol.g2_mapping);
    os << std::endl;
    print_edges(os, sol.h);
}

void print_vector(std::ostream& os, const std::vector<int>& v) {
    bool first = true;
    for (typename std::vector<int>::const_iterator it = v.begin();
        it != v.end();
        it++)
    {
        if (first) {
            first = false;
            os << *it;
        }
        else {
            os << " " << *it;
        }
    }
}

void print_edges(std::ostream& os, const graph<int>* g) {
    std::vector<int> vertices_list = g->get_vertices();
    std::unordered_set<int> vertices;

    for (typename std::vector<int>::const_iterator it1 = vertices_list.begin();
        it1 != vertices_list.end();
        it1++)
    {
        vertices.insert(*it1);
    }

    for (typename std::vector<int>::const_iterator it1 = vertices_list.begin();
        it1 != vertices_list.end();
        it1++)
    {
        std::vector<int> neigh = g->neighbours(*it1);

        for (typename std::vector<int>::const_iterator it2 = neigh.begin();
            it2 != neigh.end();
            it2++)
        {
            if (vertices.find(*it2) != vertices.end()) {
                os << *it1 << " " << *it2 << std::endl;
            }
        }

        vertices.erase(*it1);
    }
}
