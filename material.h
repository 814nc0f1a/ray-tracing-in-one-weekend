#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material
{
public:
    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
    {
        return false;
    }
};

class lambertian : public material
{
public:
    lambertian(const color &_albedo)
    {
        albedo = _albedo;
    }

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            // Catch degenerate scatter direction.
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;

        return true;
    }

private:
    color albedo;
};

class metal : public material
{
public:
    metal(const color &_albedo, double _fuzz = 0.0)
    {
        albedo = _albedo;
        fuzz = _fuzz < 1.0 ? _fuzz : 1.0;
    }

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        vec3 reflected = reflect(r_in.get_direction(), rec.normal);

        reflected = unit_vector(reflected) + fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected);
        attenuation = albedo;

        return (dot(scattered.get_direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};

class dielectric : public material
{
public:
    dielectric(double _refractive_index)
    {
        refractive_index = _refractive_index;
    }

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override
    {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0 / refractive_index) : refractive_index;

        vec3 unit_direction = unit_vector(r_in.get_direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        vec3 direction;
        bool cannot_refract = ri * sin_theta > 1.0;
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    double refractive_index;

    static double reflectance(double cosine, double ref_idx)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;

        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif