 #pragma once
#ifndef BRDF
#define BRDF

#include "../core/geometry.h"
#include <cmath>

class brdf
{
protected:
	vector normal;
	vector light;
	vector view;
	vec3d albedo;
	double roughness;

	double vdn;
	double ldn;
	double hdn;
	double vdh;

	void init()
	{
		vdn = dot(view, normal);
		ldn = dot(light, normal);
		vector half = normalize(view + light);
		hdn = dot(half, normal);
		vdh = dot(view, half);
	}

public:
	brdf();
	brdf(const vector& normal, const vector& light, const vector& view, const vec3d& albedo, const double& roughness) : normal(normal), light(light), view(view), albedo(albedo), roughness(roughness)
	{
		init();
	}
	
	// Diffuse BRDF
	vec3d diffuse(const vec3d& albedo)
	{
		return albedo / M_PI;
	}

	// Fresnel term
	// schlick's approximation
	vec3d fresnel_schlick(const vec3d& f0)
	{
		return f0 + (vec3d(1., 1., 1.) - f0) * pow(1. - vdh, 5);
	}

	// ue's acceleration
	vec3d fresnel_ue(const vec3d& f0)
	{
		double power = (-5.55473 * vdh - 6.98316) * vdh;
		
		return f0 + (vec3d(1., 1., 1.) - f0) * pow(2, power);
	}

	// Geometry term
	// schlick's model
	double geometry()
	{	
		double k = pow(roughness + 1., 2) / 8;
		double g1_view = vdn / (vdn * (1 - k) + k);
		double g1_light = ldn / (ldn * (1 - k) + k);
		
		return g1_view * g1_light;
	}

	// Normal distribution function/term
	// Beckmann's model
	double ndf_beckmann()
	{
		double alpha = roughness * roughness;
		double alpha2 = alpha * alpha;
		double cos2_theta_h = hdn * hdn;
		double cos4_theta_h = cos2_theta_h * cos2_theta_h;
		double tan2_theta_h = (1 - cos2_theta_h) / cos2_theta_h;

		return exp(-tan2_theta_h / alpha2) / (M_PI * alpha2 * cos4_theta_h);
	}

	// GGX/Trowbridge-Reitz model
	double ndf_ggxtr()
	{
		double alpha = roughness * roughness;
		double alpha2 = alpha * alpha;
		double cos2_theta_h = hdn * hdn;

		return alpha2 / (M_PI * (cos2_theta_h * (alpha2 - 1.) + 1.) * (cos2_theta_h * (alpha2 - 1.) + 1.));
	}

	// GTR/Generalized Trowbridge-Reitz model
	// gamma = 1
	double ndf_gtr1()
	{
		double alpha = roughness * roughness;
		double alpha2 = alpha * alpha;
		double cos2_theta_h = hdn * hdn;
		double c = (alpha2 - 1.) / (M_PI * log(alpha2));

		return c / (1. + (alpha2 - 1.) * cos2_theta_h);
	}

	// gamma = 2
	double ndf_gtr2()
	{
		double alpha = roughness * roughness;
		double alpha2 = alpha * alpha;
		double cos2_theta_h = hdn * hdn;
		double c = alpha2 / M_PI;

		return c / pow(1. + (alpha2 - 1.) * cos2_theta_h, 2.);
	}
};



#endif // BRDF