#ifndef UTILITY_H
#define UTILITY_H


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdint>
#include <math.h>



// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
const double deg2radConv = pi / 180.0; 
// Utility Functions

inline double degrees2radians(double degrees) {
    return degrees * deg2radConv;
}


#endif