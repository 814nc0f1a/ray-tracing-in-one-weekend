#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

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

    // Translate the [0, 1] component value to the byte range [0, 255.]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif