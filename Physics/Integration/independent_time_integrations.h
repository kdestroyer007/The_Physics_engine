#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

/// use a reversed vector for rates
/// example : (acceleration,velocity) and not (velocity,acceleration)
/// to know the exact reason see the code below

float integrate(float quantity,float time,vector<float> & rates){
    
    using clock = chrono::high_resolution_clock;
    
    auto abs_prev = clock::now();
    auto prev = clock::now();
    
    while ( chrono::duration<float>(clock::now() - abs_prev).count() < time){
        float rate_1 = 0;
        float dt = chrono::duration<float>(clock::now() - prev).count();
        
        for (float & rate : rates){
            rate += rate_1*dt;
            rate_1 = rate;   

        }
        quantity += rate_1*dt;
        prev = clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return quantity;
}
    
