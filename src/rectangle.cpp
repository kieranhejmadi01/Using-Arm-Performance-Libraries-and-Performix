#include <atomic>
#include <algorithm>
#include <vector>
#include <ranges> // C++20 

#include "rectangle.h"
#include "point.h"
#include "vec1D.h"

Rectangle::Rectangle(const float x_l, const float y_l, const float x_r, const float y_r)
    : bottomLeft{x_l,y_l}
    , topRight{x_r,y_r} 
{

}   


bool Rectangle::withinRectangle(const Point& v){
    if(topRight[0] > v._x && v._x > bottomLeft[0]){
        if (topRight[1] > v._y && v._y > bottomLeft[1]){
            return true;
        }
    } 
    return false;
}

/**
 * 
 * Counts the numberf 2-D vector points located within a 
 * rectangle. 
 * 
 */
int Rectangle::countPointsInRectangle(const Vec1D& points){
    // TO DO, make this section multi-threaded?
    std::atomic<int> count{0};

    int size = static_cast<int>(points.getSize());
    const std::vector<Point>& data = points.getData();


    // iterate over the vector
    int ans = std::ranges::count_if(data.begin(), data.end(),[this](const Point& v){
        return withinRectangle(v);    
    });    

    // std::cout << "Answer = " << ans << std::endl;
    return ans;
}
