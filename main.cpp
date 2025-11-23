#include "vec3.h"
#include "ray.h"
#include "color.h"

#include <iostream>
using namespace std;

/*
	Check if a ray hits a sphere.

	Parameters:
	- center: The center of the sphere.
	- radius: The radius of the sphere.
	- r: The ray to test.

	Returns:
	- true if the ray hits the sphere, false otherwise.
*/
bool hit_sphere(const point3 &center, double radius, const ray &r)
{
	vec3 oc = r.get_origin() - center;

	auto a = dot(r.get_direction(), r.get_direction());
	auto b = -2.0 * dot(r.get_direction(), oc);
	auto c = dot(oc, oc) - radius * radius;

	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

/*
	Get the color seen along a ray.

	Parameters:
	- r: The ray to trace.

	Returns:
	- The color seen along the ray.
*/
color get_ray_color(const ray &r)
{
	color start_color(1.0, 0.7, 0.3); // Light orange.
	color end_color(0.5, 0.7, 1.0);	  // Light blue.

	if (hit_sphere(point3(0, 0, -1), 0.5, r))
	{
		return color(1.0, 0.0, 0.0); // Red.
	}

	vec3 unit_direction = unit_vector(r.get_direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);

	return (1.0 - a) * start_color + a * end_color;
}

int main()
{
	// Image definition.
	auto aspect_ratio = 16.0 / 9.0;
	int image_w = 400;
	int image_h = int(image_w / aspect_ratio);
	image_h = (image_h < 1) ? 1 : image_h;

	// Camera definition.
	auto focal_length = 1.0;
	auto camera_center = point3(0, 0, 0);

	// Viewport definition.
	auto viewport_h = 2.0;
	auto viewport_w = viewport_h * (double(image_w) / image_h);
	auto viewport_u = vec3(viewport_w, 0, 0);
	auto viewport_v = vec3(0, -viewport_h, 0);

	auto pixel_delta_u = viewport_u / image_w;
	auto pixel_delta_v = viewport_v / image_h;
	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u * 0.5) - (viewport_v * 0.5);
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Render.
	cout << "P3\n"
		 << image_w << " " << image_h << "\n255\n";

	for (int j = 0; j < image_h; j++)
	{
		clog << "\nLines remaining: " << (image_h - j) << " " << flush;

		for (int i = 0; i < image_w; i++)
		{
			auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = get_ray_color(r);
			write_color(cout, pixel_color);
		}
	}

	clog << "\nDone.\n";
}
