#include <iostream>
#include <thread>
#include <cmath>
#include "../Vectors/Vector2.h"
#include "../body.h"

using namespace std;

void collision(vector<Body*> & bodies,double threshold ,vector<vector<Vec2>*> const &  prev){
    
    
    #define PI 3.14159265
    int i = 0;
    int j = 0;
    Body* prev_body;
    
    
    while(j < static_cast<int>(bodies.size())){
        
        if(bodies[j]->position.x <= 0 or bodies[j]->position.x >= 800){
            bodies[j]->position.x = (*prev[j])[0].x;
            bodies[j]->velocity.x = -bodies[j]->velocity.x;
        }
        if(bodies[j]->position.y <= 0 or bodies[j]->position.y >= 600){
            bodies[j]->position.y = (*prev[j])[0].y;
            bodies[j]->velocity.y = -bodies[j]->velocity.y;
        }
        i=0;
        
        while(i < static_cast<int>(bodies.size())){
            if(i==j){
                i += 1;
                continue;
            }
            
            if(magnitude(bodies[j]->position-(*bodies[i]).position)<=threshold){
                
                double va = magnitude(bodies[j]->velocity);
                double vb = magnitude((*bodies[i]).velocity);
                double x;
                double y;
                double z;
                               
                angle(bodies[j]->velocity,y);
                angle((*bodies[i]).velocity,z);
                angle(bodies[i]->position - (*bodies[j]).position,x); 
                Vec2 relative_position = (bodies[i]->position-bodies[j]->position);
                Vec2 relative_velocity = (bodies[i]->velocity-bodies[j]->velocity);
                
                //if (A-B)dot(va-vb) is positive the distance AB increases.
                
                if(dot(relative_position,relative_velocity) > 0){
                    
                    //without this safe guard the velocity changes twice since the position 
                    //does not change and cancels the effect
                    
                    i+=1;
                    continue;             
                }
                
                ///equations of collisions
                
                double va_along = (va*cos(y-x)*(bodies[j]->mass - bodies[i]->mass) + 2*bodies[i]->mass*vb*cos(z-x))/(bodies[j]->mass + bodies[i]->mass);
                double vb_along = (vb*cos(z-x)*(bodies[i]->mass - bodies[j]->mass) + 2*bodies[j]->mass*va*cos(y-x))/(bodies[j]->mass + bodies[i]->mass);
                
                ///simple trigonometry?
                
                bodies[j]->velocity = {1*(va_along*cos(x) + va*sin(y-x)*cos(PI/2 + x)),1*(va_along*sin(x) + va*sin(y-x)*sin(PI/2 + x))};
                bodies[i]->velocity = {1*(vb_along*cos(x) + vb*sin(z-x)*cos(PI/2 + x)),1*(vb_along*sin(x) + vb*sin(z-x)*sin(PI/2 + x))};  
            }
            i += 1;
        }
        j += 1;
    }
    
}
    
    
       
