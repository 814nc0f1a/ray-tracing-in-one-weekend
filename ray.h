#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "point3.h"

class ray
{
public:
    ray() {}

    ray(const point3 &_origin, const vec3 &_direction)
    {
        origin = _origin;
        direction = _direction;
    }

    const point3 &get_origin() const
    {
        return origin;
    }

    const vec3 &get_direction() const
    {
        return direction;
    }

    point3 at(double t) const
    {
        return origin + t * direction;
    }

private:
    point3 origin;
    vec3 direction;
};

#endif