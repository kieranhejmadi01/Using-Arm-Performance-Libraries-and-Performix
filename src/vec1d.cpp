#include <random>
#include <amath.h>
#include <iostream>
#include <armpl.h>
#include <algorithm>
#include <ranges>
#include <optional>
#include <chrono>

#include "vect.h"
#include "vec1D.h"

Point Vec1D::_randomVec(){

    static std::mt19937 rd(std::random_device{}());
    // uniform distribution use a switch statement to decide RNG
    switch (dist){
        case UNIFORM:{
            static std::uniform_real_distribution<float> distrib(param_a,param_b);
            return Point(distrib(rd), distrib(rd));
        }   
        case GAUSSIAN:{
            static std::normal_distribution<float> distrib(param_a,param_b);
            return Point(distrib(rd), distrib(rd));            
        }
        default:{
            static std::normal_distribution<float> distrib(param_a,param_b);
            return Point(distrib(rd), distrib(rd));            
        }

    }

};

Vec1D::Vec1D(std::size_t n):
    data(n,Point{0.0f,0.0f}),
    dist(BASIC_RNG::UNIFORM),
    n(n)
    {   
}

Vec1D::Vec1D(std::size_t n, BASIC_RNG dist, float param_a, float param_b)
    :data(n, Point{0.0f, 0.0f})
    ,n(n)
    ,dist(dist)
    ,param_a(param_a)
    ,param_b(param_b)
{
    
    std::srand(std::time(0));
    std::ranges::generate(data, [this](){return _randomVec();});
    
}

const std::vector<Point>& Vec1D::getData() const{
    return data;
};

std::vector<Point>& Vec1D::getData(){
    return data;
};

int Vec1D::getSize() const{
    return static_cast<int>(n);
}

std::optional<Vec1D> Vec1D::operator+(const Vec1D& r) const{
    // check if lengths are equal
    if (n != r.n){
        return std::nullopt;
    }
    Vec1D out(r.n);

    // add each element and store in origin vec1d
    std::ranges::transform(
        this->data,
        r.data,
        out.data.begin(),
        [](const Point&a, const Point&b){
            return a + b;
        }
    );
    return out;
}

std::ostream& operator<<(std::ostream& o, const Point& v){
    o << "[ " << v._x << ", " << v._y << " ]";
    return o;
}

std::ostream& operator<<(std::ostream& o, const Vec1D& v){
    const int num_element = v.n;
    o << "Vector of Size " << num_element << " ";
    for (int i = 1; i < num_element; i = i << 1){
        o << v.data[i] << " ,";
    }
    return o;
}

void createRandom1DVec(Vec1D& v, BASIC_RNG dist, float param_a, float param_b ){

    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_SFMT19937, 777);
    
    std::vector<float> tmp(2 * v.getSize());

    switch (dist){
        case UNIFORM:
            {
                vsRngUniform(                               // single-precision version
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    v.getSize(),
                    tmp.data(),
                    param_a,
                    param_b
                );
                break;
            }
        case EXPONENTIAL:
            {
                vsRngExponential(
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    v.getSize(),
                    tmp.data(),
                    param_a,
                    param_b
                );
                break;
            }
        case GAUSSIAN:
            {
                vsRngGaussian(
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    v.getSize(),
                    tmp.data(),
                    param_a, // ACTUALLY MEAN
                    param_b // ACTUALLY STDDEV
                );
                break;
            }
        case RALEIGH:
            {
                vsRngRayleigh(
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    v.getSize(),
                    tmp.data(),
                    param_a, // ACTUALLY DISPLACEMENT FACTOR
                    param_b // ACTUALLY SCALEFACTOR
                );
                break;
            }
        default:
            {
                vsRngUniform(                               // single-precision version
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    v.getSize(),
                    tmp.data(),
                    param_a,
                    param_b
                );
                break;
            }
            
    }


    auto& data = v.getData();
    for (int i = 0; i < v.getSize(); i++){
        data[i]._x = tmp[2*i];
        data[i]._y = tmp[2*i+1];
    }
    // map
    return;
};

