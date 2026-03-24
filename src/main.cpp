#include <iostream>
#include <fstream>
#include <string>

#if defined(__aarch64__)
    #include <amath.h> // Arm Math Libraries
    #include <armpl.h> // Arm Performance Libraries. Tested on v26.01
#elif defined(__x86_64__) || defined(__i386__)
    #error "Please rebuild on an aarch64 machine"
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
    // Comment Out when running with Arm Performix
    // exportVectorsToCSV(ans.value(), "vector_data.csv", "comb");
    return;
}


int main(){

    processData();

    return 0;
}


