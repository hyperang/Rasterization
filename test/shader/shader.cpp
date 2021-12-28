#include "shader.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <memory>

using std::sqrt;
using std::shared_ptr;

int main()
{
	// Image
	const auto aspect_ratio = 1.0 / 1.0;
	const int image_width = 1000;

	// World
	shared_ptr<object> obj = std::make_shared<object>("../assets/african_head.obj");
	//shared_ptr<object> obj = std::make_shared<object>("../assets/sphere-cylcoords-1k.obj");
	matrix4 rotation = {vector(sqrt(0.5), 0, -1 * sqrt(0.5), 0), vector(0, 1, 0, 0), vector(sqrt(0.5), 0, sqrt(0.5), 0), vector(0, 0, 0, 1)};
	matrix4 movement = {vector(1, 0, 0, 0), vector(0, 1, 0, 0), vector(0, 0, 1, -6), vector(0, 0, 0, 1)};
	matrix4 obj_to_world = matrixMulti({ rotation, movement });

	// Light
	vector lightdir = vector(0, -1, -1, 0);
	color light_col = color(1, 1, 1, 1);

	// Camera
	vector lookat = vector(0, 0, -1, 0);
	matrix4 rmat = getRotationMat(vector(0, 0, -1, 0), lookat);
	vector up = matrixMulti(rmat, vector(0, 1, 0, 0));
	point camerapos = point(0, 0, 0, 1);
	double view_width = 2;
	double view_height = view_width / aspect_ratio;
	int image_height = image_width / aspect_ratio;
	perspcamera cam(camerapos, lookat, up, image_height, image_width, -5, -7, view_height, view_width);

	// Shader
	struct vin data = { image_width, aspect_ratio, obj, obj_to_world, lightdir, lookat, camerapos, cam.world2clampMat() };

	// Texture
	//shared_ptr<tga> maintex = std::make_shared<tga>();
	//std::cerr << "texture file: [../assets/african_head_diffuse.tga] loading " << (maintex->read_tga_file("../assets/african_head_diffuse.tga") ? "ok" : "failed") << std::endl;
	//shared_ptr<tga> spectex = std::make_shared<tga>();
	//std::cerr << "texture file: [../assets/african_head_spec.tga] loading " << (spectex->read_tga_file("../assets/african_head_spec.tga") ? "ok" : "failed") << std::endl;

	//shared_ptr<tga> toont;

	// Pass
	shared_ptr<deepmap> dp = std::make_shared<deepmap>(image_width, image_height);
	shared_ptr<frame> rf = std::make_shared<frame>(image_width, image_height);

	//const double gloss = 0.5;
	const double metallic = 1.;
	const double roughness = 0.2;
	const vec3d albedo = vec3d(250./255., 209./255., 194./255.);
	const color surf_col = color(1, 155. / 255., 0, 1);
	//blinnphong bpshader(data, light_col, surf_col, gloss, maintex, spectex);
	//toon tshader(data, light_col, surf_col, gloss, toont);
	cooktorrance ctshader(data, light_col, roughness, metallic, albedo);

	//v2f vertout = bpshader.vertex(data);
	v2f vertout = ctshader.vertex(data);
	//bpshader.fragment(vertout, dp, rf);
	ctshader.fragment(vertout, dp, rf);

	// Print img
	ppm img(image_width, image_height);
	img.set_path("img.ppm");
	img.new_image();
	img.draw_start();
	// print
	for(int i = image_height - 1; i >= 0; i--)
	{
		for(int j = 0; j < image_width; j++)
		{
			img.pixel_draw(rf->pixelcol(j, i));
		}
	}
	img.draw_end();

	system("pause");
	return 0;
}