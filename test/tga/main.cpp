#include "tga.h"
#include <memory>

int main()
{
	std::shared_ptr<tga> texutre = std::make_shared<tga>();
	std::cerr << "texture file loading " << (texutre->read_tga_file("../assets/african_head_diffuse.tga") ? "ok" : "failed") << std::endl;

	int width = texutre->get_width();
	int height = texutre->get_height();

	frame rf(width, height);
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			tga_color tex_col_tga = texutre->get(i, height - j - 1);
			color col = color(int(tex_col_tga.bgra[2]) / 255., int(tex_col_tga.bgra[1]) / 255., int(tex_col_tga.bgra[0]) / 255., int(tex_col_tga.bgra[3]) / 255.);

			rf.drawpixel(i, j, col);
		}
	}

	ppm img(width, height);
	img.set_path("img.ppm");
	img.new_image();
	img.draw_start();
	// print
	for(int i = height - 1; i >= 0; i--)
	{
		for(int j = 0; j < width; j++)
		{
			img.pixel_draw(rf.pixelcol(j, i));
		}
	}
	img.draw_end();

	system("pause");
	return 0;
}