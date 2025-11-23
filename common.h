#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

// Constants.

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

/*
    Converts degrees to radians.

    Parameters:
        degrees - Angle in degrees.

    Returns:
        Angle in radians.
*/
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

/*
    Returns a random real in [0,1).

    Returns:
        A double precision floating-point number in the range [0, 1).
*/
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

/*
    Returns a random real in [min, max.)

    Parameters:
        min - Minimum value (inclusive.)
        max - Maximum value (exclusive.)

    Returns:
        A double precision floating-point number in the range [min, max.)
*/
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

// Common Headers.

#include "color.h"
#include "interval.h"
#include "vec3.h"
#include "point3.h"
#include "ray.h"

#endif