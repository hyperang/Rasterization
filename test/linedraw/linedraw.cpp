#include "linedraw.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

int main()
{
	color white = vec4(1, 1, 1, 1);

	// bunny
	std::vector<triangle> trislist;
	object bunny = object("../assets/bunny.obj");
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
			p[k] = vl[i];
			k++;
		}
		triangle t = triangle(p[0], p[1], p[2]);
		trislist.push_back(t);
		it++;
	}

	const int height = 400;
	const int width = 400;
	frame f(width, height);

	const int scale = 10;

	int linenum = 0;
	
	int p0x, p0y, p1x, p1y, p2x, p2y;
	
	for(int i = 0; i < trislist.size(); i++)
	{
		p0x = int((trislist[i].p[0].x() + 0.12) * (width - 1) * scale / 2);
		p0y = int((trislist[i].p[0].y() + 0) * (height - 1) * scale / 2);
		p1x = int((trislist[i].p[1].x() + 0.12) * (width - 1) * scale / 2);
		p1y = int((trislist[i].p[1].y() + 0) * (height - 1) * scale / 2);
		p2x = int((trislist[i].p[2].x() + 0.12) * (width - 1) * scale / 2);
		p2y = int((trislist[i].p[2].y() + 0) * (height - 1) * scale / 2);

		f.drawline(p0x, p0y, p1x, p1y, white);
		f.drawline(p1x, p1y, p2x, p2y, white);
		f.drawline(p0x, p0y, p2x, p2y, white);
		linenum += 3;
	}

	ppm img(width, height);
	img.set_path("img.ppm");
	img.new_image();
	img.draw_start();
	// ppm: travel pixels from left to right by row & travel rows from top to bottom 
	for(int i = height - 1; i >= 0; --i)
	{
		for(int j = 0; j < width; ++j)
		{
			img.pixel_draw(f._frame[j][i]);
		}
	}
	img.draw_end();

	std::cout << linenum << std::endl;


	system("pause");
	return 0;
}