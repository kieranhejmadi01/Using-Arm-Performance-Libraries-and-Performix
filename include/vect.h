#pragma once
#include <iostream>

class Vec;
/**
 * 
 * Proxy object exist to accelerate comparison operators
 * by omission the square root function in calculating the magnitude
 * of a vector
 * 
 */

class LengthProxy{
public:
    LengthProxy(float _x, float _y);
    // overloaded comparison operator
    bool operator==(const LengthProxy& other) const = default;
    auto operator<=>(const LengthProxy& other) const = default; // compiler generates functions that perform member-wise comparison 
    friend auto operator<=>(const LengthProxy& proxy, float len);
    operator float() const&&;
private:
    // LengthSquared
    float _lengthSquare{};

};


/**
 * 
 * A Single Point Vector in a 2-D plane
 * 
 */
class Vec{
public:
    Vec(float x, float y); // constructor

    LengthProxy length() const; // return a LengthProxy object
    float lengthSlow() const; // returns actual length from Pythagoras' theorem
    friend std::ostream& operator<<(std::ostream& o, const Vec& v);
    float angleFromOrigin();
    float _x{};
    float _y{};
};





