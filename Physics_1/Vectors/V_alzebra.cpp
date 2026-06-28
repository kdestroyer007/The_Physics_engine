#include "Vector2.h"
#include <cmath>
#include <ostream>



Vec2 operator+(const Vec2 & a , Vec2 & b){
    return {a.x + b.x , a.y + b.y};

}

Vec2 operator-(const Vec2 & a , Vec2 & b){
    return {a.x - b.x , a.y - b.y};

}

float magnitude(const Vec2 &a){
    return std::sqrt(std::pow(a.x,2) + std::pow(a.y,2));

}
Vec2 normalise(const Vec2 &a){

    float m = magnitude(a);
    return {a.x/m , a.y/m};
}

float dot(const Vec2 & a , Vec2 & b){
    return (a.x)*(b.x) + (a.y)*(b.y);

}

Vec2 operator*(double & a, Vec2 & b){
    return {a*(b.x) , a*(b.y) };

}

void angle(const Vec2 & a,double &t){
    #define PI 3.14159265
    if (a.y>0)
    {
        if (a.x<0)
        {
            t = PI + atan(a.y/a.x);
        }
        if (a.x>0)
        {
            t= atan(a.y/a.x);
        }
        
    }
    if (a.y<0)
    {
        if (a.x<0)
        {
            t= PI + atan(a.y/a.x);
        }
        if (a.x>0)
        {
            t= atan(a.y/a.x);
        }
    }
    if(a.y == 0){
        if (a.x<0)
        {
            t= PI;
        }
        if (a.x >0){
            t= 0;
        }
        
    }
    
}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}