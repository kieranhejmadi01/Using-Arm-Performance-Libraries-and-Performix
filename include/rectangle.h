#pragma once

class Point; // forward declaration
class Vec1D;

/**
 * Object representing a Rectangle in a 2-D Plane. Requires 2 arguments for the bottom-left and top-right coordinates
 */
struct Rectangle{
public:


    Rectangle(const float x_l, const float y_l, const float x_r, const float y_r);

    /**
     * Tests whether a 2-D point vector is within the rectangular box
     */
    bool withinRectangle(const Point& v);
    int countPointsInRectangle(const Vec1D& points);
    float bottomLeft[2];
    float topRight[2];
};



