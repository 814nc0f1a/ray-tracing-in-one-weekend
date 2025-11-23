#include "common.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

/*
	Get the color seen along a ray.

	Parameters:
	- r: The ray to trace.

	Returns:
	- The color seen along the ray.
*/
color get_ray_color(const ray &r, const hittable &world)
{
	hit_record rec;
	color start_color(1.0, 1.0, 1.0); // White.
	color end_color(0.5, 0.7, 1.0);	  // Light blue.

	if (world.hit(r, interval(0, infinity), rec))
	{
		return 0.5 * (rec.normal + start_color);
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

	// World definition.
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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

			color pixel_color = get_ray_color(r, world);
			write_color(cout, pixel_color);
		}
	}

	clog << "\nDone.\n";
}
