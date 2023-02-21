#pragma once

#include <iostream>
#include <chrono>
 
class Timer {

public:
	Timer() : Timer("timer") {}

	Timer(std::string name) : 
		_name(name),
		_time_start(std::chrono::high_resolution_clock::now()) {}

	~Timer() {
		_time_end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(_time_end - _time_start);
		std::cout << _name << " takes " << duration.count() / 1000000.0 << " ms\n";
	}

private:
	std::string _name;//先声明的先初始化，不会因为在_time_start后初始化导致不必要的性能惩罚
	std::chrono::time_point<std::chrono::high_resolution_clock> _time_start;
	std::chrono::time_point<std::chrono::high_resolution_clock> _time_end;
};
