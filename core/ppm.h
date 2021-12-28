#pragma once
#ifndef CORE_PPM
#define CORE_PPM

#include <iostream>
#include <fstream>
#include "color.h"

class ppm
{
public:
	/* ppm public methods */
	ppm(int w, int h) : width(w), height(h) {}
	~ppm() {}

	void set_path(std::string path)
	{
		this->path = path;
	}

	void new_image()
	{
		image.open(path, std::ios::binary); // create image

		image << "P3\n" // PPM magic number
			  << width << ' ' << height << ' ' << '\n' // width & height in ASCII decimal
			  << "255\n"; // maximum color value in ASCII decimal

		std::cerr << "new ppm file: " << path << ' ' << "created successfully!\n";
		image.close();
	}

	void pixel_draw(color pixel_color)
	{
		write_color(image, pixel_color);
	}

	void pixel_draw(color pixel_color, int samples_per_pixel)
	{
		write_color(image, pixel_color, samples_per_pixel);
	}

	void draw_start()
	{
		image.open(path, std::ios::app);
	}

	void draw_end()
	{
		image.close();
	}

private:
	/* ppm private data */
	int width, height;
	std::string path;
	std::ofstream image;
};

#endif // CORE_PPM