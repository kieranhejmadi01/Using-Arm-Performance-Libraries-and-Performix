#include <random>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <optional>
#include <chrono>
#include <ctime>

#if USE_ARMPL
    #if defined(__aarch64__)
        #include <amath.h>
        #include <armpl.h>
    #else
        #error "USE_ARMPL enabled but not on AArch64"
    #endif
#endif

#include "point.h"
#include "vec1D.h"



void createRandom1DVec(Vec1D& v, BASIC_RNG dist, float param_a, float param_b);

Point Vec1D::_randomVec(){

    static std::mt19937 rd(std::random_device{}());
    // uniform distribution use a switch statement to decide RNG
    switch (dist){
        case UNIFORM:{
            std::uniform_real_distribution<float> distrib(param_a,param_b);
            return Point(distrib(rd), distrib(rd));
        }   
        case GAUSSIAN:{
            std::normal_distribution<float> distrib(param_a,param_b);
            return Point(distrib(rd), distrib(rd));            
        }
        default:{
            std::normal_distribution<float> distrib(param_a,param_b);
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

#if USE_ARMPL
    createRandom1DVec(*this, dist, param_a, param_b);
#else
    std::generate(data.begin(), data.end(), [this](){ return _randomVec(); });
#endif
    
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

    std::transform(
        this->data.begin(),
        this->data.end(),
        r.data.begin(),
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

#if USE_ARMPL

    VSLStreamStatePtr stream;
    vslNewStream(&stream, VSL_BRNG_SFMT19937, 777); // NOTE: seeded vsl stream with fixed value, 777
    
    const int count = 2*v.getSize();
    std::vector<float> tmp(2 * v.getSize());

    switch (dist){
        case UNIFORM:
            {
                vsRngUniform(                               // single-precision version
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    count,
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
                    count,
                    tmp.data(),
                    param_a, // ACTUALLY MEAN
                    param_b // ACTUALLY STDDEV
                );
                break;
            }
        default:
            {
                vsRngUniform(                               // single-precision version
                    VSL_RNG_METHOD_UNIFORM_STD,
                    stream,
                    count,
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

    vslDeleteStream(&stream);

#else
    std::mt19937 rd(std::random_device{}());
    auto& data = v.getData();

    switch (dist){
        case UNIFORM:
            {
                std::uniform_real_distribution<float> distrib(param_a, param_b);
                for (int i = 0; i < v.getSize(); i++){
                    data[i]._x = distrib(rd);
                    data[i]._y = distrib(rd);
                }
                break;
            }
        case GAUSSIAN:
            {
                std::normal_distribution<float> distrib(param_a, param_b);
                for (int i = 0; i < v.getSize(); i++){
                    data[i]._x = distrib(rd);
                    data[i]._y = distrib(rd);
                }
                break;
            }
        default:
            {
                std::uniform_real_distribution<float> distrib(param_a, param_b);
                for (int i = 0; i < v.getSize(); i++){
                    data[i]._x = distrib(rd);
                    data[i]._y = distrib(rd);
                }
                break;
            }
    }
#endif

    return;
};

