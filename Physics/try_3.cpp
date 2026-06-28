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
sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Physics Engine"
    );
sf::CircleShape circle_1(50.f);
sf::CircleShape circle_2(50.f);
sf::CircleShape circle_3(50.f);

int main(){

    Body body_1 = {{100,200},{20,30},{0,9.8},3};
    Body body_2 = {{300,100},{20,30},{0,9.8},3};
    Body body_3 = {{300,400},{20,30},{0,9.8},3};
    vector<Body*> bodies = {& body_1,& body_2,& body_3};
    vector<Vec2*> rates_1 = {& body_1.acceleration, & body_1.velocity};
    vector<Vec2*> rates_2 = {& body_2.acceleration, & body_2.velocity};
    vector<Vec2*> rates_3 = {& body_3.acceleration, & body_3.velocity};
    vector<Vec2> prev_1 = {{0,0},{0,0}};
    vector<Vec2> prev_2 = {{0,0},{0,0}};
    vector<Vec2> prev_3 = {{0,0},{0,0}};
    vector<vector<Vec2>*> prev = {& prev_1,& prev_2,& prev_3};
    
    while(window.isOpen()){
        
        
        
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                
                window.close();
            }
        
        }
        integrate(bodies[0]->position,rates_1,prev_1);
        integrate(bodies[1]->position,rates_2,prev_2);
        integrate(bodies[2]->position,rates_3,prev_3);
        collision(bodies,100,prev);
        circle_1.setPosition(ToSMFL(body_1.position));
        circle_2.setPosition(ToSMFL(body_2.position));
        circle_3.setPosition(ToSMFL(body_3.position));
        window.clear();
        window.draw(circle_1);
        window.draw(circle_2);
        window.draw(circle_3);
        window.display();
    }   

}
        
        
  