#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

/// use a reversed vector for rates
/// example : (acceleration,velocity) and not (velocity,acceleration)
/// to know the exact reason see the code below
/// pass a vector of size 2 prev to know the previous state of the body 
///for smaller values of dt i.e. higher precision the ball gets jiggled between 2 states(velocities)
///dont use values of dt equivalent to 0.0001
///safe values 0.016(1/60) 0.008(1/120) also fractions dont work

float integrate(double & quantity,vector<double> & rates,vector<double> & prev){
    using clock = chrono::high_resolution_clock;
    auto prev_time = clock::now();
    const double  dt = 0.008;
    
    double rate_1 = 0;
    double accumulator = 0.0;
    
    while(true){
        accumulator += chrono::duration<double>(clock::now() - prev_time).count();
        if (accumulator>=dt){
            for(double & rate : rates){
                
                rate += dt*rate_1;
                rate_1 = rate;
            }
            prev[0] = quantity;
            quantity += dt*rate_1;
            
            break;
        }
    }
    return 0;
}