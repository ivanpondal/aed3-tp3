#include "main.h"

using namespace std;

void show_help(char* bin_path) {
	cout << "  Modo de uso: " << bin_path << endl;
	cout << endl;
	cout << "  Opciones:" << endl;
	cout << "    -h          Muestra este texto de ayuda" << endl;
	cout << "    -t          Ejecuta los tests unitarios provistos para el framework" << endl;
	cout << "    -g          Ejecuta los generadores de instancias de grafos para pruebas" << endl;
}

int main (int argc, char* argv[]) {
	mode exec_mode = test;

	char opt;
	while ((opt = getopt(argc, argv, "htg")) != -1) {
		switch (opt) {
			case 'h': {
				show_help(argv[0]);
				exit(0);
				break;
			}
			case 't': {
				exec_mode = test;
				break;
			}
			case 'g': {
				exec_mode = instance_generation;
				break;
			}
			default: {
				show_help(argv[0]);
				exit(1);
				break;
			}
		}
	}

	if (exec_mode == test) {
		run_unit_tests();
	}
	else if (exec_mode == instance_generation) {
		run_instance_generation();
	}
}
