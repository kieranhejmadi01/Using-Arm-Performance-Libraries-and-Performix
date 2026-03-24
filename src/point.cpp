#include <random>
#include <algorithm>
#include <math.h>
#include <amath.h>
#include <ranges>
#include <iostream>
#include <armpl.h>
#include <chrono>
#include "point.h"


Point::Point(float x, float y):_x(x),_y(y){

};

LengthProxy Point::length() const{
    return LengthProxy(_x,_y);
}

float Point::lengthSlow() const{
    return std::sqrt((_x*_x + _y*_y));
}

auto operator<=>(const LengthProxy& proxy, float len){
    return proxy._lengthSquare <=> (len*len);
}

LengthProxy::LengthProxy(float _x, float _y):_lengthSquare((_x*_x) + (_y*_y)){

}

LengthProxy::operator float() const&&{
    return std::sqrt(_lengthSquare);
}

float Point::angleFromOrigin(){
    float ans = armpl_acos_f32(_y/_x);
    return (180.0/M_PI)*ans;
}

float min_length(const std::vector<Point>& r){
    auto compare = [&](auto&& a, auto&& b){
        return a.length() < b.length();
    };
    auto it = std::ranges::min_element(r, compare);
    return it->length();
}

float min_length_slow(const std::vector<Point>& r){
    auto compare = [&](auto&& a, auto&& b){
        return a.lengthSlow() < b.lengthSlow();
    };
    auto it = std::ranges::min_element(r, compare);
    return it->lengthSlow();
}

Point operator+(const Point& l, const Point& r){
    return Point(l._x+r._x, l._y+r._y);
}

Point operator-(const Point& l, const Point& r){
    return Point(l._x - r._x, l._y - r._y);
}

