#pragma once

#include <vector>
#include <optional>
#include <armpl.h>



class Vec;
class Rectangle;

enum BASIC_RNG{
        UNIFORM = 1,
        EXPONENTIAL,
        GAUSSIAN,
        RALEIGH,
};

/** 
 * 
 *  Small wrapper class that creates an arbitrary vector of vec. 
 *   Please Note: 1D is reffering to a 1 dimensional vector
 * 
*/
class Vec1D{
public:
    /**
     * 
     * Constructor to create a random vector of 2D points of size n
     */
    Vec1D(std::size_t n, BASIC_RNG dist, float param_a, float param_b); // initializes vector of size n
    /**
     * 
     * Constructor to create an empty vector of 2D points of size n
     */
    Vec1D(std::size_t n); // initializes empty vector of size n

    const std::vector<Vec>& getData() const;
    std::vector<Vec>& getData(); // non-const version

    /**
     * partially print to stdout
     */
    friend std::ostream& operator<<(std::ostream& o, const Vec1D& v);
    
    /**
     * Find the magnitude of a 2D point (distance from origin 0,0)
     */
    int getSize() const;

    /**
     * Calculate how many points are within a rectangle, r
     */
    int numOfVectInRectangle(const Rectangle& r);

    /**
     * Add 2 vectors together
     */
    std::optional<Vec1D> operator+(const Vec1D& r) const;

private:
    Vec _randomVec();
    std::vector<Vec> data{};
    std::size_t n{};
    const BASIC_RNG dist;
    float param_a{0.0};
    float param_b{0.0};
};

/**
 * 
 * Utility function to return the smallest magnitude point vector from std::vector of
 * point vectors
 */
float min_length(const std::vector<Vec>& r);
float min_length_slow(const std::vector<Vec>& r);




/**
 * 
 * Free functcion to instantiate a 1D vector of points (Vec), v with a random distribution of values
 * 
 * dist allows you to select a specific mathematical distributions with 2 parameters (e.g., mean & stddev for gaussian or min and max for uniform)
 * 
 */
void createRandom1DVec(Vec1D& v, BASIC_RNG dist, float param_a, float param_b );

/**
 * 
 * Operation to add two Point Vectors together
 *  
 */
Vec operator+(const Vec& l, const Vec& r);

/**
 * 
 * Operation to minus the left hand point Vector from the right hand point vectors
 */
Vec operator-(const Vec& l, const Vec& r);


