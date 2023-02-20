#pragma once

#include <iostream>
#include <chrono>
 
class Timer {

public:

    Timer() : Timer("timer") {}

    Timer(std::string name) : 
        _time_start(std::chrono::high_resolution_clock::now()),
        _name(name) {}

    ~Timer() {
        _time_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(_time_end - _time_start);
        std::cout << _name << " takes " << duration.count() / 1000000.0 << " ms\n";
    }

private:

    std::string _name;
    std::chrono::time_point<std::chrono::high_resolution_clock> _time_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> _time_end;
};
