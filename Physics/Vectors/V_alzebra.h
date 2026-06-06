#include "Vector2.h"
#include <cmath>

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

Vec2 operator*(float & a, Vec2 & b){
    return {a*(b.x) , a*(b.y) };

}

std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}