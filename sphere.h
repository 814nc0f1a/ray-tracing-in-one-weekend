#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere(const point3 &_center, double _radius, shared_ptr<material> _mat)
    {
        center = _center;
        radius = fmax(0.0, _radius);
        mat = _mat;
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        vec3 oc = center - r.get_origin();

        auto a = r.get_direction().length_squared();
        auto h = dot(r.get_direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        // Find the nearest root that lies in the acceptable range.
        auto sqrtd = sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat;

        return true;
    }

private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif