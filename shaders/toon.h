#pragma once
#ifndef SHADER_TOON
#define SHADER_TOON

#include "..\core\geometry.h"
#include "..\core\object.h"
#include "..\core\frame.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

#include "shader.h"

using std::shared_ptr;

class toon : public shader<vin, v2f>
{
public:
	toon() {}
	toon(const vin& vertin, const color& light_col, const color& surface_col, const double& gloss, const shared_ptr<tga> texture) : vertin(vertin), light_col(light_col), surface_col(surface_col), gloss(gloss), maintexture(texture) {}

	virtual v2f vertex(vin& vertin)
	{
		std::cout << "vertex shader running..." << std::endl;

		v2f o;

		o.image_width = vertin.image_width;
		o.aspect_ratio = vertin.aspect_ratio;
		o.lightdir = vertin.lightdir;

		std::vector<point> worldverts;
		for(int i = 0; i < vertin.obj->vertslist.size(); i++)
		{
			point p = matrixMulti(vertin.obj2world, vertin.obj->vertslist[i]);		
			worldverts.push_back(p);		
		}
		o.worldverts = worldverts;

		std::vector<vector> worldnorms;
		for(int i = 0; i < vertin.obj->normslist.size(); i++)
		{
			vector n = matrixMulti(vertin.obj2world, vertin.obj->normslist[i]);
			n.set_vector();
			worldnorms.push_back(n);
		}
		o.worldnorms = worldnorms;

		o.uvs = vertin.obj->uvslist;

		std::vector<point> clampverts;
		for(int i = 0; i < worldverts.size(); i++)
		{
			point p = matrixMulti(vertin.world2clamp, worldverts[i]);
			double w = p.w();
			p /= w;
			clampverts.push_back(p);
		}
		o.clampverts = clampverts;

		std::vector<std::vector<vec3i>> candidates;
		for(int i = 0; i < vertin.obj->faceslist.size(); i++)
		{
			std::vector<vec3i> f = vertin.obj->faceslist[i];
			vector n = normalize(cross(worldverts[f[2].x()] - worldverts[f[0].x()], worldverts[f[1].x()] - worldverts[f[0].x()]));
			if(dot(normalize(vertin.lookat), n) > 0)
				candidates.push_back(f);
		}
		o.candidates = candidates;

		return o;
	}

	virtual void fragment(v2f& vertout, const shared_ptr<deepmap> dp, const shared_ptr<frame> rf)
	{
		std::cout << "fragment shader running..." << std::endl;

		int image_height = static_cast<int>(vertout.image_width / vertout.aspect_ratio);
		for(int k = 0; k < vertout.candidates.size(); k++)
		{
			triangle t = triangle(vertout.clampverts[vertout.candidates[k][0].x()],
								  vertout.clampverts[vertout.candidates[k][1].x()],
								  vertout.clampverts[vertout.candidates[k][2].x()]);
			if(t.edge[0] >= vertout.image_width || t.edge[1] < 0 || t.edge[2] >= image_height || t.edge[3] < 0)
			{
				// not render
				continue;
			}
			else
			{
				int xbegin = (t.edge[0] > 0) ? int(t.edge[0]) : 0;
				int ybegin = (t.edge[2] > 0)  ? int(t.edge[2]) : 0;
				int xend = (t.edge[1] < vertout.image_width) ? int(t.edge[1]) : vertout.image_width;
				int yend = (t.edge[3] < image_height) ? int(t.edge[3]) : image_height;

				for(int i = xbegin; i < xend; i++)
				{
					for(int j = ybegin; j < yend; j++)
					{
						double x = double(i) + 0.5;
						double y = double(j) + 0.5;
						vec3d b = t.barycentric(x, y);
						double z = 1;
						if(b.x() < 0 || b.y() < 0 || b.z() < 0)
						{
							continue;
						}
						else
						{
							z = b[0] * t.p[0].z() + b[1] * t.p[1].z() + b[2] * t.p[2].z();
							z = (z - 1) / 2 * (-1);
						}
						if(dp->update(i, j, z))
						{
							// draw t at (x, y)
							vector worldnormal;
							if(!vertout.worldnorms.empty())
							{
								worldnormal = normalize(b[0] * vertout.worldnorms[vertout.candidates[k][0].z()] + 
											    		b[1] * vertout.worldnorms[vertout.candidates[k][1].z()] + 
												 	    b[2] * vertout.worldnorms[vertout.candidates[k][2].z()]);
							}
							else
							{
								worldnormal = normalize(cross(t.p[2] - t.p[0], t.p[1] - t.p[0]));
							}
							
							point worldpos = b[0] * vertout.worldverts[vertout.candidates[k][0].x()] + 
											 b[1] * vertout.worldverts[vertout.candidates[k][1].x()] + 
											 b[2] * vertout.worldverts[vertout.candidates[k][2].x()];
							
							if(!vertout.uvs.empty() && maintexture != nullptr)
							{
								double alpha = b[0] / vertout.worldverts[vertout.candidates[k][0].x()].z();
								double beta = b[1] / vertout.worldverts[vertout.candidates[k][1].x()].z();
								double gamma = b[2] / vertout.worldverts[vertout.candidates[k][2].x()].z();
								vec2d uv = (alpha * vertout.uvs[vertout.candidates[k][0].y()] + beta * vertout.uvs[vertout.candidates[k][1].y()] + gamma * vertout.uvs[vertout.candidates[k][2].y()]) / (alpha + beta + gamma);
								tga_color tex_col_tga = maintexture->get(int(uv.x() * (maintexture->get_width() - 1)), int((1 - uv.y()) * (maintexture->get_height() - 1)));
								surface_col = color(int(tex_col_tga.bgra[2]) / 255., int(tex_col_tga.bgra[1]) / 255., int(tex_col_tga.bgra[0]) / 255., int(tex_col_tga.bgra[3]) / 255.);
							}

							double intensity = saturate(dot(worldnormal, -normalize(vertout.lightdir)));
							if(intensity > .75) intensity = 1;
							else if(intensity > .60) intensity = .80;
							else if(intensity > .45) intensity = .60;
							else if(intensity > .30) intensity = .45;
							else if(intensity > .15) intensity = .30;
							else intensity = .15;

							vector view = normalize(vertout.camerapos - worldpos);
							if(saturate(dot(view, worldnormal)) < 0.15) intensity = .60;
							
							color diffuse = light_col * surface_col * intensity;

							rf->drawpixel(i, j, diffuse);
						}
					}
				}
			}
		}
	}
	
	vin vertin;
	color light_col;
	color surface_col;
	double gloss;
	shared_ptr<tga> maintexture;
};

#endif // SHADER_TOON