#pragma once
#include <ostream>
#include <vector>
struct Vec2{
    double x;
    double y;
    Vec2 operator+=(const Vec2 & other){
        x += other.x;
        y += other.y;
        return *this; 

    }
    
    
};
Vec2 operator+(const Vec2 & a , Vec2 & b);
Vec2 operator-(const Vec2 & a , Vec2 & b);
float magnitude(const Vec2 &a);
Vec2 normalise(const Vec2 &a);
float dot(const Vec2 & a , Vec2 & b);
Vec2 operator*(double & a, Vec2 & b);
void angle(const Vec2 & a,double &t);
std::ostream& operator<<(std::ostream& os, const Vec2& v);
float integrate(Vec2 & quantity,std::vector<Vec2*>& rates,std::vector<Vec2> & prev);