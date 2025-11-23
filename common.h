#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

// Constants.
const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions.
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers.
#include "color.h"
#include "interval.h"
#include "vec3.h"
#include "point3.h"
#include "ray.h"

#endif