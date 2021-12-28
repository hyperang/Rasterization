#pragma once
#ifndef SHADER_COOKTORRANCE
#define SHADER_COOKTORRANCE

#include "..\core\geometry.h"
#include "..\core\object.h"
#include "..\core\frame.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

#include "shader.h"
#include "brdf.h"

using std::shared_ptr;

class cooktorrance : public shader<vin, v2f>
{
public:
	cooktorrance();
	cooktorrance(const vin& vertin, const color& light_col, const double& roughness, const double& metallic, const vec3d& albedo) : vertin(vertin), light_col(light_col), roughness(roughness), metallic(metallic), albedo(albedo)
	{
		f0 = (1 - metallic) * vec3d(0.04, 0.04, 0.04) + metallic * albedo;
	}
	// ~cooktorrance();

	virtual v2f vertex(vin& vertin)
	{
		v2f o;

		o.image_width = vertin.image_width;
		o.aspect_ratio = vertin.aspect_ratio;
		o.lightdir = vertin.lightdir;
		o.camerapos = vertin.camworldpos;

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
							
							vector view = normalize(vertout.camerapos - worldpos);
							vector light = -normalize(vertout.lightdir);
							vector half = normalize(view + light);

							// brdf
							brdf brdf_ = brdf(worldnormal, light, view, albedo, roughness);

							// fresnel_term
							vec3d fresnel = brdf_.fresnel_schlick(f0);

							// ndf_term
							double ndf = brdf_.ndf_ggxtr();

							// geometry_term
							double geometry = brdf_.geometry();

							vec3d f_r = (vec3d(1., 1., 1.) - fresnel) * (1. - metallic) * albedo / M_PI + ndf * geometry * fresnel / (4 * dot(view, worldnormal) * dot(light, worldnormal));

							// rendering equition
							color col = light_col * color(saturate(f_r.r()), saturate(f_r.g()), saturate(f_r.b()), 1) * saturate(dot(worldnormal, light));

							rf->drawpixel(i, j, col);
						}
					}
				}
			}
		}
	}

protected:
	vin vertin;
	double roughness;
	double metallic;
	vec3d albedo;
	vec3d f0;
	color light_col;
	// shared_ptr<tga> img_light;
};

#endif // SHADER_COOKTORRANCE