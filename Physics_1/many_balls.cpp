///position is one step ahead of velocity i.e. 
///the velocity at a position p is calculated in the next loop
///take care of this or suffers from energy loss
///position is one step ahead of velocity (approx) the velocity of object at a position gets calculated in the next loop
///for smaller values of dt i.e. higher precision the ball gets jiggled between 2 states(velocities)
///dont use values of dt equivalent to 0.0001
///safe values 0.016(1/60) 0.008(1/120) also fractions dont work

#include <SFML/Graphics.hpp>
#include "Vectors/Vector2.h"
#include "body.h"
#include "collisions/collisions.h"




using namespace std;

sf::Vector2f ToSMFL(const Vec2 & a){
    return sf::Vector2f(
        static_cast<float>(a.x),
        static_cast<float>(a.y)
    );
}

int main(){
    Body body_1 = {Vec2 {100,300},Vec2 {100,0},Vec2 {0,0},2};
    Body body_2 = {Vec2 {0,200},Vec2 {10,0},Vec2 {0,9.8},2};
    Vec2* acc_1 = & body_1.acceleration;
    Vec2* vel_1 = & body_1.velocity;
    Vec2* acc_2 = & body_2.acceleration;
    Vec2* vel_2 = & body_2.velocity;
    vector<Vec2*> rates_1 = {acc_1,vel_1};
    vector<Vec2*> rates_2 = {acc_2,vel_2};
    vector<Vec2> prev_2 = {{0,0}};
    vector<Vec2> prev_1={{0,0}};

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Physics Engine"
    );
    sf::CircleShape circle_1(50.f);
    sf::CircleShape circle_2(50.f);

    while(window.isOpen()){
        collision(body_1,body_2,100);
        if (body_1.position.y>500){
            
            body_1.velocity.y =-body_1.velocity.y;
            body_1.position.y = prev_1[0].y;
        }
        if (body_1.position.y<0){
            
            body_1.velocity.y =-body_1.velocity.y;
            body_1.position.y = prev_1[0].y;
        }
        if (body_2.position.y>500){
            
            body_2.velocity.y =-body_2.velocity.y;
            body_2.position.y = prev_2[0].y;
        }
        if (body_2.position.y<0){
            
            body_2.velocity.y =-body_2.velocity.y;
            body_2.position.y = prev_2[0].y;
        }
        if (body_1.position.x>700){
            body_1.velocity.x =-body_1.velocity.x;
            body_1.position.x = prev_1[0].x;
        }
        if (body_2.position.x>700){
            body_2.velocity.x =-body_2.velocity.x;
            body_2.position.x = prev_2[0].x;
        }
        
        if (body_2.position.x<0){
            body_2.velocity.x =-body_2.velocity.x;
            body_2.position.x = prev_2[0].x;
        }
        if (body_1.position.x<0){
            body_1.velocity.x =-body_1.velocity.x;
            body_1.position.x = prev_1[0].x;
        }
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                
                window.close();
            }
            
        }
        integrate(body_1.position,rates_1,prev_1);
        integrate(body_2.position,rates_2,prev_2);
        circle_1.setPosition(ToSMFL(body_1.position));
        circle_2.setPosition(ToSMFL(body_2.position));
        window.clear();
        window.draw(circle_1);
        window.draw(circle_2);
        window.display();
    }

    
}