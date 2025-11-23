#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera
{
public:
    double aspect_ratio = 1.0;  // Aspect ratio.
    int image_w = 100;          // Image width in pixels.
    int samples_per_pixel = 10; // Number of samples per pixel.
    int max_depth = 10;         // Maximum number of ray bounces into scene.

    /*
        Render the scene from the camera's perspective.

        Parameters:
        - world: The world containing hittable objects.
    */
    void render(const hittable &world)
    {
        inizialize();

        // Render.
        cout << "P3\n"
             << image_w << " " << image_h << "\n255\n";

        for (int j = 0; j < image_h; j++)
        {
            clog << "\nLines remaining: " << (image_h - j) << " " << flush;

            for (int i = 0; i < image_w; i++)
            {
                color pixel_color(0, 0, 0);

                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j);
                    pixel_color += get_ray_color(r, max_depth, world);
                }

                write_color(cout, pixel_samples_scale * pixel_color);
            }
        }

        clog << "\nDone.\n";
    }

private:
    int image_h;                // Image height in pixels.
    double pixel_samples_scale; // Scale factor for pixel color averaging.
    point3 camera_center;       // Camera center point.
    point3 pixel00_loc;         // Location of pixel (0, 0.)
    vec3 pixel_delta_u;         // Offset to pixel to the right.
    vec3 pixel_delta_v;         // Offset to pixel below.

    /*
        Initialize camera parameters.
    */
    void inizialize()
    {
        image_h = int(image_w / aspect_ratio);
        image_h = (image_h < 1) ? 1 : image_h;

        pixel_samples_scale = 1.0 / double(samples_per_pixel);

        camera_center = point3(0, 0, 0);

        // Viewport definition.
        auto focal_length = 1.0;
        auto viewport_h = 2.0;
        auto viewport_w = viewport_h * (double(image_w) / image_h);
        auto viewport_u = vec3(viewport_w, 0, 0);
        auto viewport_v = vec3(0, -viewport_h, 0);

        pixel_delta_u = viewport_u / image_w;
        pixel_delta_v = viewport_v / image_h;
        auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u * 0.5) - (viewport_v * 0.5);
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    /*
        Generate a ray from the camera through the specified pixel.

        Parameters:
        - pixel_i: Pixel column index.
        - pixel_j: Pixel row index.

        Returns:
        - The generated ray.
    */
    ray get_ray(int pixel_i, int pixel_j) const
    {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((pixel_i + offset.x()) * pixel_delta_u) + ((pixel_j + offset.y()) * pixel_delta_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - camera_center;
        return ray(ray_origin, ray_direction);
    }

    /*
        Return a vector to a random point in the [-0.5, -0.5] - [0.5, 0.5]
        unit square.

        Returns:
        - A vec3 representing the sampled point.
    */
    vec3 sample_square() const
    {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    /*
        Get the color seen along a ray.

        Parameters:
        - r: The ray to trace.
        - depth: The maximum number of ray bounces allowed.
        - world: The world containing hittable objects.

        Returns:
        - The color seen along the ray.
    */
    color get_ray_color(const ray &r, int depth, const hittable &world) const
    {
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        color start_color(1.0, 1.0, 1.0); // White.
        color end_color(0.5, 0.7, 1.0);   // Light blue.

        if (world.hit(r, interval(0.001, infinity), rec))
        {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * get_ray_color(ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.get_direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);

        return (1.0 - a) * start_color + a * end_color;
    }
};

#endif