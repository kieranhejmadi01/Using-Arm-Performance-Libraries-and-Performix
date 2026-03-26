#include <iostream>
#include <utility>
#include <string>

#include "rectangle.h"
#include "point.h"
#include "vec1D.h"
#include "scopedTimer.h"
#include "export_data.h"

using namespace std;

Vec1D generateDistribution(const int NUM_ELEMENTS, BASIC_RNG distrubutionA, BASIC_RNG distrubutionB, const std::pair<float, float>& argA, const std::pair<float, float>& argB){
    
    // auto title = std::string{"Generating Distribution of size "} + std::to_string(NUM_ELEMENTS);
    // Timer A(title.c_str(), UNIT::US);
    
    float paramA = argA.first;
    float paramB = argA.second;

    Vec1D a(NUM_ELEMENTS, distrubutionA, argA.first, argA.second);
    Vec1D b(NUM_ELEMENTS, distrubutionB, argB.first, argB.second);

    auto sum = a + b;

    if (sum.has_value()){
        // print out the sum of the 2 distributions.
        auto& result = sum.value();
        return result;
    } else{
        std::cout << "sizes of vec1D objects are not the same " << std::endl;
    }


}


int main(){
    
    const int NUM_POINTS = (1<<14); // 2^14 (16,384) random points

    std::pair<float, float> meanAndStdDeviationParams{30.0,50.0}; // Key parameters for a Gaussian Distribution
    std::pair<float, float> minAndMaxParams{10.0,100.0}; // Key parameters for a uniform distribution

    // STEP 1. Generate a distribution of 2D Points that is the sum of a Gaussian and Uniform distribution

    const Vec1D distribution  = generateDistribution(NUM_POINTS, BASIC_RNG::GAUSSIAN, BASIC_RNG::UNIFORM, meanAndStdDeviationParams, minAndMaxParams);

    // STEP 2. Calculate the number of points that fit within a 2D window

    Rectangle window(10.0,10.0,50.0,50.0);
    int numberOfPoints = window.countPointsInRectangle(distribution);
    std::cout << "Number of Data Points = " << NUM_POINTS 
              << " | Number of Points within Window ( [" 
              << window.bottomLeft[0]  << ", " << window.bottomLeft[1] << "] , ["
              << window.topRight[0]  << ", " << window.topRight[1]
              << "] ) = " << numberOfPoints << std::endl;
    
    
    // STEP 3. Calculate the magnitude of the smallest point within the distribution

    float shortestDistance = min_length(distribution.getData());
    std::cout << "Shortest Distance from Origin = " << shortestDistance << std::endl;

    return 0;
}
