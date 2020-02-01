#pragma once
#include <chrono>
#include <iostream>

class Timer{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;

public:
    Timer();
    ~Timer();

    void Stop();

};