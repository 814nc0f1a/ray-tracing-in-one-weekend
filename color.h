#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>
using namespace std;

// color is an alias for vec3. It represents an RGB color.
using color = vec3;

/*
    Write the color object to the output stream in PPM format.

    Parameters:
    - out: The output stream to write to.
    - pixel_color: The color to write, expressed as a vec3.
*/
void write_color(ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif