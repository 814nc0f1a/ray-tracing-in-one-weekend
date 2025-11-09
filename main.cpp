#include "vec3.h"
#include "color.h"

#include <iostream>
using namespace std;

int main() {
	// Image definition.
	int image_w = 256;
	int image_h = 256;

	// Render.
	cout << "P3\n" << image_w << " " << image_h << "\n255\n";

	for (int j = 0; j < image_h; j++) {
		clog << "\nLines remaining: " << (image_h - j) << " " << flush;

		for (int i = 0; i < image_w; i++) {
			auto pixel_color = color(
				double(i) / (image_w - 1),
				double(j) / (image_h - 1),
				0.0
			);
			write_color(cout, pixel_color);
		}
	}

	clog << "\nDone.\n";	
}
