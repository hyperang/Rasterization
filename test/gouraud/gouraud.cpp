#include "gouraud.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

int main()
{
	// Image
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 500;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	matrix4 rotation = {vec4d(sqrt(0.5), 0, sqrt(0.5), 0), vec4d(0, 1, 0, 0), vec4d(-1 * sqrt(0.5), 0, sqrt(0.5), 0), vec4d(0, 0, 0, 1)};
	matrix4 movement = {vec4d(1, 0, 0, 0), vec4d(0, 1, 0, 0), vec4d(0, 0, 1, -6), vec4d(0, 0, 0, 1)};
	matrix4 obj_trans_mat = matrixMulti({ rotation, movement });
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
			p[k] = matrixMulti(obj_trans_mat, vl[i.x()]);
			k++;
		}
		triangle t = triangle(p[0], p[1], p[2]);
		trislist.push_back(t);
		it++;
	}

	// Light
	vector lightdir = vector(-1, -1, -1, 0);

	// Camera
	// camera init look-at: (0, 0, -1), up: (0, 1, 0)
	vector lookat = vector(0, 0, -1, 0);
	matrix4 rmat = getRotationMat(vec4d(0, 0, -1, 0), lookat);
	vector up = matrixMulti(rmat, vector(0, 1, 0, 0));
	// int sample_ratio = 1;
	// cuboid size
	double view_width = 2;
	double view_height = view_width / aspect_ratio;
	perspcamera camera(point(0, 0, 0, 1), lookat, up, image_height, image_width, -5, -7, view_height, view_width);

	// Render
	std::vector<triangle> rtrislist;
	std::vector<color> fcollist;

	for(int i = 0; i < trislist.size(); i++)
	{
		triangle t = trislist[i];
		bool iscut = false;
		vector worldnormal = normalize(cross(t.p[2] - t.p[0], t.p[1] - t.p[0]));
		
		iscut = (dot(normalize(lookat), worldnormal) > 0) ? false : true;
		if(iscut) continue;

		// trans to clamp
		t = triangle(matrixMulti(camera.world2clampMat(), t.p[0]), matrixMulti(camera.world2clampMat(), t.p[1]), matrixMulti(camera.world2clampMat(), t.p[2]));
		for(int j = 0; j < 3; j++)
		{
			double w = t.p[j].w();
			t.p[j] /= w;
		}
		t.setedge();
		rtrislist.push_back(t);
		double intensity = dot(worldnormal, normalize(lightdir));
		
		if(intensity > 0) fcollist.push_back(color(intensity, intensity, intensity, 1));
		else fcollist.push_back(color(0, 0, 0, 1));
	}
	
	// init deepmap
	deepmap dp(image_width, image_height);
	// init frame
	frame rf = frame(image_width, image_height);
	for(int k = 0; k < rtrislist.size(); k++)
	{
		if(rtrislist[k].edge[0] > image_width || rtrislist[k].edge[1] < 0 || rtrislist[k].edge[2] > image_height || rtrislist[k].edge[3] < 0)
		{
			// not render
		}
		else
		{
			int xbegin = (rtrislist[k].edge[0] > 0) ? int(rtrislist[k].edge[0]) : 0;
			int ybegin = (rtrislist[k].edge[2] > 0)  ? int(rtrislist[k].edge[2]) : 0;
			int xend = (rtrislist[k].edge[1] < image_width) ? int(rtrislist[k].edge[1]) : image_width;
			int yend = (rtrislist[k].edge[3] < image_height) ? int(rtrislist[k].edge[3]) : image_height;

			// update deepmap
			for(int i = xbegin; i < xend; i++)
			{
				for(int j = ybegin; j < yend; j++)
				{
					double x = double(i) + 0.5;
					double y = double(j) + 0.5;
					double z = rtrislist[k].getz(x, y);
					if(dp.update(i, j, z))
					{
						rf.drawpixel(i, j, fcollist[k]);
					}
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
			img.pixel_draw(rf.pixelcol(j, i));
		}
	}
	img.draw_end();



	system("pause");
	return 0;
}