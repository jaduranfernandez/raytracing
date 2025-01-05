#ifndef UTILITY_H
#define UTILITY_H


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdint>
#include <math.h>
#include <cstdlib>


// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double deg2radConv = pi / 180.0; 
// Utility Functions

inline double degrees2radians(double degrees) {
    return degrees * deg2radConv;
}

inline std::string createFilePath(const char* folder, const char* name){
    std::string filename = std::string(folder) + std::string(name) + ".png";
    return filename;
}


inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}




#endif