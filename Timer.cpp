#include "Timer.h"


Timer::Timer(){
    startTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer(){
    Stop();
}

void Timer::Stop(){
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimePoint-startTimePoint).count();

    std::cout<<duration<< " us"<<std::endl;
}