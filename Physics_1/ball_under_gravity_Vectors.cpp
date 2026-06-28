///position is one step ahead of velocity i.e. 
///the velocity at a position p is calculated in the next loop
///take care of this or suffers from energy loss
///position is one step ahead of velocity (approx) the velocity of object at a position gets calculated in the next loop
///for smaller values of dt i.e. higher precision the ball gets jiggled between 2 states(velocities)
///dont use values of dt equivalent to 0.0001
///safe values 0.016(1/60) 0.008(1/120) also fractions dont work

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Vectors/Vector_intergration.h"
#include "Vectors/V_alzebra.h"
#include "Vectors/Vector2.h"
#include "body.h"


using namespace std;

sf::Vector2f ToSMFL(const Vec2 & a){
    return sf::Vector2f(
        static_cast<float>(a.x),
        static_cast<float>(a.y)
    );
}

int main(){
    Body body = {Vec2 {100,100},Vec2 {10,0},Vec2 {0,9.8},2};
    Vec2* acc = & body.acceleration;
    Vec2* vel = & body.velocity;
    vector<Vec2*> rates = {acc,vel};
    vector<Vec2> prev={{0,0}};

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Physics Engine"
    );
    sf::CircleShape circle(50.f);
    while(window.isOpen()){
        if (body.position.y>500){
            
            body.velocity.y =-body.velocity.y;
            body.position.y = prev[0].y;
        }
        if (body.position.x>700){
            body.velocity.x =-body.velocity.x;
            body.position.x = prev[0].x;
        }
        if (body.position.x<0){
            body.velocity.x =-body.velocity.x;
            body.position.x = prev[0].x;
        }
        
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                
                window.close();
            }
            
        }
        integrate(body.position,rates,prev);
        circle.setPosition(ToSMFL(body.position));
        window.clear();
        window.draw(circle);
        window.display();
    }

    
}