#pragma once
#include <chrono>
#include <iostream>

enum UNIT{
    SECONDS = 1,
    MS,
    US,
    NS,
};

/**
 * 
 * A simple timer class that times the duration the object is in scope. Second argument in unit of measurement
 * in SECONDS (seconds), MS (milliseconds), UM (microseconds) and NS (nanoseconds).
 * Example: 
 *    Timer A("name of section", UNIT::MS);
 * 
 */
class Timer{
public:
    using Clock = std::chrono::steady_clock;
    Timer(const char* name, const UNIT unit):_start(Clock::now()), _funcName(name),_unit(unit){};

    // prevent misuse of scoped timer
    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;
    
    ~Timer(){
        Clock::time_point _end = Clock::now();
        switch(_unit){
            case 1:{
                auto dur = std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count();
                std::cout << _funcName << " = " << dur << " s" << std::endl; 
                break;
            }
            case 2:{
                auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
                std::cout << _funcName << " = " << dur << " ms" <<std::endl; 
                break;
            }
            case 3:{
                auto dur = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count();
                std::cout << _funcName << " = " << dur << " us" << std::endl; 
                break;
            }
            case 4:{
                auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count();
                std::cout << _funcName << " = " << dur << " ns" << std::endl; 
                break;                        
            }
        }

    }


private:
    const Clock::time_point _start{};
    const char* _funcName{};
    const UNIT _unit{SECONDS};
};