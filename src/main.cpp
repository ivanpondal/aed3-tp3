#include "./main.h"

using namespace std;

// Modos de ejecución
#define MODE_DEFAULT           0
#define MODE_UNIT_TESTS        1
#define MODE_EXPERIMENTATION   2

bool verbose = false;


int main (int argc, char* argv[]) {
    // Configuración de la ejecución
    // bool verbose = false;
    int mode = MODE_DEFAULT;

    // Parsea las opciones recibidas
    char opt;
    while ((opt = getopt(argc, argv, "htvp:")) != -1) {
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
                mode = MODE_UNIT_TESTS;
                break;
            }
            case 'e': { // correr pruebas de performance
                srand(stoi(optarg)); // configura el seed que recibe por parámetro
                mode = MODE_EXPERIMENTATION;
                break;
            }
            default: { // si las opciones son inválidas
                show_help(argv[0]);
                exit(1);
                break;
            }
        }
    }

    switch (mode) {
        case MODE_DEFAULT:
            run_solution();
            break;

        case MODE_UNIT_TESTS:
            run_unit_tests();
            break;

        case MODE_EXPERIMENTATION:
            run_experimentation();
            break;
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
