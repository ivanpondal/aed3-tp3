#ifndef CHRONOMETER_H_
#define CHRONOMETER_H_

#include <chrono>

class chronometer{
	public:
		static void start();
		static double stop();
	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
		static std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

#endif // CHRONOMETER_H_INCLUDED
