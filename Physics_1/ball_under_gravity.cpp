///position is one step ahead of velocity (approx) the velocity of object at a position gets calculated in the next loop
///for smaller values of dt i.e. higher precision the ball gets jiggled between 2 states(velocities)
///dont use values of dt equivalent to 0.0001
///safe values 0.016(1/60) 0.008(1/120) also fractions dont work

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "body.h"
#include "Integration/better_integration.cpp"
#include "Vectors/Vector2.h"

int main(){
    vector<double> prev_x = {0,0};
    vector<double> prev_y = {0,0};
    vector<double> rates_y = {98,0};
    
    vector<double> rates_x = {0,20};
    Body body;
    body.position.y = 100;
    body.position.x = 100;
    

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Physics Engine"
    );
    sf::CircleShape circle(50.f);
    while(window.isOpen()){
        if (body.position.y>500){
            
            body.position.y = prev_y[0];
            rates_y[1] = -rates_y[1];
            
        }
        if (body.position.x>700){
            rates_x[1] = -rates_x[1];
        }
        if (body.position.x<0){
            rates_x[1] = -rates_x[1];
        }
        
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                
                window.close();
            }
            
        }
        
        
        integrate(body.position.y,rates_y,prev_y);
        integrate(body.position.x,rates_x,prev_x);

        float x = static_cast<float>(body.position.x);
        float y = static_cast<float>(body.position.y);

        circle.setPosition({x,y});
        window.clear();
        window.draw(circle);
        window.display();
    }   

}