#include "ej4.h"
#include "../mini_test.h"

std::ostream &operator<<(std::ostream& output, const std::pair<int, int>& p){
	output << "(" << p.first << ", " << p.second << ")";
	return output;
}

void run_unit_tests(){
}
