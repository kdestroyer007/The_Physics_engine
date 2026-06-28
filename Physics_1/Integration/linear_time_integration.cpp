#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

float integrate(float quantity,float rate,float time){
    using clock = chrono::high_resolution_clock;
    
    auto abs_prev = clock::now();
    auto prev = clock::now();
    while ( chrono::duration<float>(prev - abs_prev).count() < time){
        float dt = chrono::duration<float>(clock::now() - prev).count();
        quantity += dt*rate;
        prev = clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return quantity;
}
