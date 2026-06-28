#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

/// use a reversed vector for rates
/// example : (acceleration,velocity) and not (velocity,acceleration)
/// to know the exact reason see the code below
/// pass a vector of size 2 prev to know the previous state of the body 

float integrate(double & quantity,double time,vector<double> & rates,vector<double> & prev){
    double quantity_prev;
    double rate_prev;
    
    using clock = chrono::high_resolution_clock;
    
    auto abs_prev = clock::now();
    auto prev_time = clock::now();
    
    while ( chrono::duration<float>(clock::now() - abs_prev).count() < time){
        double rate_1 = 0;
        double dt = chrono::duration<double>(clock::now() - prev_time).count();
        
        for (double & rate : rates){
            rate_prev = rate;
            rate += rate_1*dt;
            rate_1 = rate;   

        }
        quantity_prev = quantity;
        quantity += rate_1*dt;
        prev_time = clock::now();
        prev = {quantity_prev,rate_prev};
        
    }
    
    return 0;
}
    
