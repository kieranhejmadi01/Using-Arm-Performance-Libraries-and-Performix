#include <iostream>
#include <fstream>
#include <string>

#if defined(__aarch64__)
    #include <amath.h> // Arm Math Libraries
    #include <armpl.h> // Arm Performance Libraries. Tested on v26.01
#elif defined(__x86_64__) || defined(__i386__)
    #include <mkl_vsl.h>
    #define USE_ARMPL 0
    #define USE_MKL_VSL 1
#endif

#include "rectangle.h"
#include "point.h"
#include "vec1D.h"
#include "scopedTimer.h"
#include "export_data.h"

using namespace std;

// void exportVectorsToCSV(const Vec1D& vectors, const string& filename, const string& dist_type);

const int NUM_POINTS = (1<<22);

void processData(){
    Timer A("Using Random.h",UNIT::MS);
    Vec1D u(NUM_POINTS, BASIC_RNG::UNIFORM, 20.0, 400.0);
    Vec1D v(NUM_POINTS, BASIC_RNG::GAUSSIAN,100.0,20.0);

    auto ans = u + v;
    if (ans.has_value()){
        
    } else{
        std::cout << "sizes of vec1D are different" << std::endl;
    }
    return;
}

void processDataAPL(){
    Timer A("Using armpl.h",UNIT::MS);
    
    Vec1D u(NUM_POINTS);
    Vec1D v(NUM_POINTS);
    createRandom1DVec(u,BASIC_RNG::GAUSSIAN,100.0,20.0);
    createRandom1DVec(v,BASIC_RNG::UNIFORM,20.0,400.0);

    auto ans = u + v;
    if (ans.has_value()){
        
    } else{
        std::cout << "sizes of vec1D are different" << std::endl;
    }
    // Comment Out when running with Arm Performix
    // exportVectorsToCSV(ans.value(), "vector_data.csv", "comb");
    return;
}

int main(){

    processData();
    processDataAPL();

    return 0;
}


