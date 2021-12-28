#include "deepmap.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

int main()
{
	// Image
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 1000;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	const double obj_trans_x = 0;
	const double obj_trans_y = 0;
	const double obj_trans_z = -6;
	matrix4 obj_trans_mat = { vec4(1, 0, 0, obj_trans_x), 
							  vec4(0, 1, 0, obj_trans_y), 
							  vec4(0, 0, 1, obj_trans_z),
							  vec4(0, 0, 0, 1) };
	//triangle t = triangle(point(-5, -5, -6, 1), point(0, 5, -29, 1), point(5, 0, -20, 1));
	std::vector<triangle> trislist;
	object bunny = object("../assets/african_head.obj");
	auto fl = bunny.faceslist;
	auto vl = bunny.vertslist;
	auto it = fl.begin();
	while(it != fl.end())
	{
		auto tmp = *it;
		point p[3];
		int k = 0;
		for(auto i : tmp)
		{
			p[k] = matrixMulti(obj_trans_mat, vl[i]);
			k++;
		}
		triangle t = triangle(p[0], p[1], p[2]);
		trislist.push_back(t);
		it++;
	}

	// check obj world pos
/*
	std::cout << "obj world pos: " << std::endl;
	for(auto t : trislist)
	{
		std::cout << "p1: " << t.p[0].x() << ' ' << t.p[0].y() << ' ' << t.getz(t.p[0].x(), t.p[0].y()) << ' ' << t.p[0].w() << std::endl;
		std::cout << "p2: " << t.p[1].x() << ' ' << t.p[1].y() << ' ' << t.getz(t.p[1].x(), t.p[1].y()) << ' ' << t.p[1].w() << std::endl;
		std::cout << "p3: " << t.p[2].x() << ' ' << t.p[2].y() << ' ' << t.getz(t.p[2].x(), t.p[2].y()) << ' ' << t.p[2].w() << std::endl;
	}
	std::cout << std::endl;
*/
	// Camera
	// camera init look-at: (0, 0, -1), up: (0, 1, 0)
	vec4 lookat = vec4(0, 0, -1, 0);
	matrix4 rmat = getRotationMat(vec4(0, 0, -1, 0), lookat);
	vec4 up = matrixMulti(rmat, vec4(0, 1, 0, 0));
	// int sample_ratio = 1;
	// cuboid size
	double view_width = 2;
	double view_height = view_width / aspect_ratio;
	// orthocamera camera(point(0, 0, 0, 1), lookat, up, image_height, image_width, 0, -20, view_height, view_width);
	perspcamera camera(point(0, 0, 0, 1), lookat, up, image_height, image_width, -5, -7, view_height, view_width);
	// camera info
/*
	std::cout << "camera world pos: " << camera.pos << std::endl;
	std::cout << "camera look-at : " << camera.lookat << std::endl;
	std::cout << "camera up : " << camera.up << std::endl;
*/
	// Render
	//triangle rt = triangle(matrixMulti(camera.world2clampMat(), t.p[0]), matrixMulti(camera.world2clampMat(), t.p[1]), matrixMulti(camera.world2clampMat(), t.p[2]));
	std::vector<triangle> rtrislist = trislist;
	for(int i = 0; i < rtrislist.size(); i++)
	{
		triangle tmp = rtrislist[i];
		rtrislist[i] = triangle(matrixMulti(camera.world2clampMat(), tmp.p[0]), matrixMulti(camera.world2clampMat(), tmp.p[1]), matrixMulti(camera.world2clampMat(), tmp.p[2]));
		for(int j = 0; j < 3; j++)
		{
			double w = rtrislist[i].p[j].w();
			rtrislist[i].p[j] /= w;
		}
		rtrislist[i].setedge();
	}
/*
	std::cout << "obj clamp pos: " << std::endl;
	for(auto t : rtrislist)
	{
		std::cout << "p1: " << t.p[0].x() << ' ' << t.p[0].y() << ' ' << t.getz(t.p[0].x(), t.p[0].y()) << std::endl;
		std::cout << "p2: " << t.p[1].x() << ' ' << t.p[1].y() << ' ' << t.getz(t.p[1].x(), t.p[1].y()) << std::endl;
		std::cout << "p3: " << t.p[2].x() << ' ' << t.p[2].y() << ' ' << t.getz(t.p[2].x(), t.p[2].y()) << std::endl;
	}
	std::cout << std::endl;
*/
	
	// init deepmap
	std::vector<std::vector<double>> deepmap(image_width, std::vector<double>(image_height, 1));
	for(auto rt : rtrislist)
	{
		if(rt.edge[0] - double(image_width) > 1e-7 || rt.edge[1] - 0. < 1e-7 || rt.edge[2] - double(image_height) > 1e-7 || rt.edge[3] - 0. < 1e-7)
		{
			// not render rt
			//std::cout << "triangle won't be rendered..." << std::endl;
		}
		else
		{
			//std::cout << "triangle will be rendered..." << std::endl;

			int xbegin = (rt.edge[0] > 0) ? int(rt.edge[0]) : 0;
			int ybegin = (rt.edge[2] > 0)  ? int(rt.edge[2]) : 0;
			int xend = (rt.edge[1] < image_width) ? int(rt.edge[1]) : image_width;
			int yend = (rt.edge[3] < image_height) ? int(rt.edge[3]) : image_height;

			//std::cout << "xbegin:xend:ybegin:yend: " << xbegin << ' ' << xend << ' ' << ybegin << ' ' << yend <<std::endl;

			// update deepmap
			for(int i = xbegin; i < xend; i++)
			{
				for(int j = ybegin; j < yend; j++)
				{
					double x = double(i) + 0.5;
					double y = double(j) + 0.5;
					double z = rt.getz(x, y);
					if(z - deepmap[i][j] < 1e-7) deepmap[i][j] = z;
					//std::cout << z << ' ';
				}
			}
		}
	}
	

	// Print image
	ppm img(image_width, image_height);
	img.set_path("img.ppm");
	img.new_image();
	img.draw_start();
	// print
	for(int i = image_height - 1; i >= 0; i--)
	{
		for(int j = 0; j < image_width; j++)
		{
			img.pixel_draw(vec4(deepmap[j][i], deepmap[j][i], deepmap[j][i], 1.0));
		}
	}
	img.draw_end();



	system("pause");
	return 0;
}