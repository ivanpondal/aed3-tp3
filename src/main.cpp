#include "./main.h"
#include "framework/structures/adj_list_graph.h"

using namespace std;

// Modos de ejecución
enum mode {solver, test, experimentation};

bool verbose = false;

int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    mode exec_mode = solver;
    srand(time(NULL)); // configura el seed por defecto

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "hvtes:")) != -1) {
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
                exec_mode = experimentation;
                break;
            }
            case 's': {
                srand(stoi(optarg)); // configura el seed que recibe por parámetro
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
        io::read_input(cin, g1, g2);
        solution res = run_solver(g1, g2);
        io::print_solution(cout, res);
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
    cout << "    -e          Ejecuta las pruebas de performance diseñadas para el algoritmo" << endl;
    cout << "    -s <seed>   Configura el seed utilizado durante la generación de instancias" << endl;
    cout << "                  aleatorias. Por defecto, se genera en base a la hora del CPU" << endl;
}

// Funciones auxiliares

solution pairs_to_solution(const graph<std::pair<int, int>>& g) {
    solution ret;
    ret.h = new adj_list_graph<int>();


    std::vector<std::pair<int, int>> vert = g.get_vertices();
    std::unordered_map<std::pair<int, int>, int, hash_pair_int> mapping;

    for (unsigned int i = 0; i < vert.size(); i++)
    {
        ret.h->add_node(i);
        mapping.insert({vert[i], i});
        ret.g1_mapping.push_back(vert[i].first);
        ret.g2_mapping.push_back(vert[i].second);
    }

    for (unsigned int i = 0; i < vert.size(); i++) {
        vector<pair<int,int>> neigh = g.neighbours(vert[i]);

        for (uint j = 0; j < neigh.size(); j++) {
            pair<int, int> curr_neigh = neigh[j];
            int mapped_neigh = mapping[curr_neigh];
            if (mapped_neigh < (int) i) {
                ret.h->add_edge(i, mapped_neigh);
            }
        }
    }

    return ret;
}

bool check_solution(
    const solution& s,
    const graph<int>& g1,
    const graph<int>& g2
) {
    for (unsigned int i = 0; i < s.h->n(); i++) {
        int vert1_g1 = s.g1_mapping[i];
        int vert1_g2 = s.g2_mapping[i];

        std::vector<int> neigh = s.h->neighbours(i);
        for (unsigned int j = 0; j < neigh.size(); j++) {
            int vert2_g1 = s.g1_mapping[neigh[j]];
            int vert2_g2 = s.g2_mapping[neigh[j]];

            if (! g1.adjacent(vert1_g1, vert2_g1) ||
                ! g2.adjacent(vert1_g2, vert2_g2)
            ) {
                return false;
            }
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream& output, const std::pair<int, int>& p){
    output << "(" << p.first << ", " << p.second << ")";
    return output;
}
