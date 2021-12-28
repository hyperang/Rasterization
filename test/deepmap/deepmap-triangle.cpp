#include "deepmap.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

int main()
{
	// Image
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	triangle t = triangle(point(-5, -5, -11, 1), point(0, 5, -29, 1), point(5, 0, -20, 1));

	// Camera
	// camera init look-at: (0, 0, -1), up: (0, 1, 0)
	vec4 lookat = vec4(0, 0, -1, 0);
	matrix4 rmat = getRotationMat(vec4(0, 0, -1, 0), lookat);
	vec4 up = matrixMulti(rmat, vec4(0, 1, 0, 0));
	// int sample_ratio = 1;
	// cuboid size
	double view_width = 10;
	double view_height = view_width / aspect_ratio;
	// orthocamera camera(point(0, 0, 0, 1), lookat, up, image_height, image_width, 0, -20, view_height, view_width);
	perspcamera camera(point(0, 0, 0, 1), lookat, up, image_height, image_width, -10, -30, view_height, view_width);
	// camera info
	std::cout << "camera world pos: " << camera.pos << std::endl;
	std::cout << "camera look-at : " << camera.lookat << std::endl;
	std::cout << "camera up : " << camera.up << std::endl;

	// Render
	triangle rt = triangle(matrixMulti(camera.world2clampMat(), t.p[0]), matrixMulti(camera.world2clampMat(), t.p[1]), matrixMulti(camera.world2clampMat(), t.p[2]));
	for(int i = 0; i < 3; i++)
	{
		double w = rt.p[i].w();
		rt.p[i] /= w;
	}
	rt.setedge();
	// triangle info
	std::cout << "trianle point a: " << rt.p[0].x() << ' ' << rt.p[0].y() << ' ' << rt.p[0].z() << ' ' << rt.p[0].w() << std::endl;
	std::cout << "trianle point b: " << rt.p[1].x() << ' ' << rt.p[1].y() << ' ' << rt.p[1].z() << ' ' << rt.p[1].w() << std::endl;
	std::cout << "trianle point c: " << rt.p[2].x() << ' ' << rt.p[2].y() << ' ' << rt.p[2].z() << ' ' <<rt.p[2].w() << std::endl;
	// init deepmap
	std::vector<std::vector<double>> deepmap(image_width, std::vector<double>(image_height, 1));
	if(rt.edge[0] > image_width || rt.edge[1] < 0 || rt.edge[2] > image_height || rt.edge[3] < 0)
	{
		// not render rt
		std::cout << "triangle won't be rendered..." << std::endl;
	}
	else
	{
		std::cout << "triangle will be rendered..." << std::endl;

		int xbegin = (rt.edge[0] > 0) ? int(rt.edge[0]) : 0;
		int ybegin = (rt.edge[2] < image_height)  ? int(rt.edge[2]) : image_height;
		int xend = (rt.edge[1] < image_width) ? int(rt.edge[1]) : image_width;
		int yend = (rt.edge[3] > 0) ? int(rt.edge[3]) : 0;

		std::cout << "xbegin:xend:ybegin:yend: " << xbegin << ' ' << xend << ' ' << ybegin << ' ' << yend <<std::endl;

		// update deepmap
		for(int i = xbegin; i < xend; i++)
		{
			for(int j = ybegin; j < yend; j++)
			{
				double x = double(i) + 0.5;
				double y = double(j) + 0.5;
				double z = rt.getz(x, y);
				if(z < deepmap[i][j]) deepmap[i][j] = z;
				std::cout << z << ' ';
			}
		}
	}

	// Print image
	ppm img(image_width, image_height);
	img.set_path("img.ppm");
	img.new_image();
	img.draw_start();
	// print
	for(int i = 0; i < image_width; i++)
	{
		for(int j = 0; j < image_height; j++)
		{
			img.pixel_draw(vec4(deepmap[i][j], deepmap[i][j], deepmap[i][j], 1.0));
		}
	}
	img.draw_end();

	system("pause");
	return 0;
}