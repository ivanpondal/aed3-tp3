#include "chronometer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> chronometer::start_time = std::chrono::time_point<std::chrono::high_resolution_clock>();
std::chrono::time_point<std::chrono::high_resolution_clock> chronometer::end_time = std::chrono::time_point<std::chrono::high_resolution_clock>();


void chronometer::start(){
	start_time = std::chrono::high_resolution_clock::now();
}

double chronometer::stop(){
	end_time = std::chrono::high_resolution_clock::now();
	return double(std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count());
}
