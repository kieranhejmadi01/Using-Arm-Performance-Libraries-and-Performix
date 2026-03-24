#include <iostream>
#include <fstream>

#include "vec1D.h"

void exportVectorsToCSV(const Vec1D& vectors, const std::string& filename, const std::string& dist_type) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    // Write header
    file << "x,y,type" << std::endl;
    
    // Write vector data
    const auto& data = vectors.getData();
    for (const auto& vec : data) {
        file << vec._x << "," << vec._y << "," << dist_type << std::endl;
    }
    
    file.close();
    std::cout << "Data exported to " << filename << " (" << vectors.getSize() << " points)" << std::endl;
}