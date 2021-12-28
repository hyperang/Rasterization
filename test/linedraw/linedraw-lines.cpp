#include "linedraw.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

int main()
{
	color white = vec4(1, 1, 1, 1);

	
	// line
	const int width = 100;
	const int height = 200;
	frame f = frame(width, height);
	int zero = 0;
	//int ten = 9;
	//int twty = 19;
	int twf = 25;
	int fifty = 50;
	int sevf = 75;
	int hundr = 100;
	int thundr = 200;

	//f.drawline(zero, zero, ten, zero, white);
	//f.drawline(ten, zero, ten, twty, white);
	//f.drawline(ten, twty, zero, twty, white);
	//f.drawline(zero, twty, zero, zero, white);
	f.drawline(fifty, fifty, fifty, hundr, white);
	f.drawline(fifty, fifty, sevf, hundr, white);
	f.drawline(fifty, fifty, hundr, hundr, white);
	f.drawline(fifty, fifty, hundr, sevf, white);
	f.drawline(fifty, fifty, hundr, fifty, white);
	f.drawline(fifty, fifty, hundr, twf, white);
	f.drawline(fifty, fifty, hundr, zero, white);
	f.drawline(fifty, fifty, sevf, zero, white);
	f.drawline(fifty, fifty, fifty, zero, white);
	f.drawline(fifty, fifty, twf, zero, white);
	f.drawline(fifty, fifty, zero, zero, white);
	f.drawline(fifty, fifty, zero, twf, white);
	f.drawline(fifty, fifty, zero, fifty, white);
	f.drawline(fifty, fifty, zero, sevf, white);
	f.drawline(fifty, fifty, zero, hundr, white);
	f.drawline(fifty, fifty, twf, hundr, white);

	for(int i = height - 1; i >= 0; i--)
	{
		for(int j = 0; j < width; j++)
		{
			std::cout << '|' << f._frame[j][i].r() << ' ' << f._frame[j][i].g() << ' ' << f._frame[j][i].b() << '|';
		}
		std::cout << std::endl; 
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

	system("pause");
	return 0;
}