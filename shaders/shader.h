#pragma once
#ifndef SHADER
#define SHADER

#include "..\core\geometry.h"
#include "..\core\object.h"
#include "..\core\frame.h"

#include <memory>

template<typename T0, typename T1>
class shader
{
public:
	/* shader public methods */
	//virtual ~shader();
	virtual T1 vertex(T0& vertin) = 0;
	virtual void fragment(T1& vertout, std::shared_ptr<deepmap> dp, std::shared_ptr<frame> rf) = 0;
};

struct vin
{
	// image info
	int image_width;
	double aspect_ratio;
	// world info
	std::shared_ptr<object> obj;
	matrix4 obj2world;
	vector lightdir;
	// camera info
	vector lookat;
	point camworldpos;
	matrix4 world2clamp;
};

struct v2f
{
	std::vector<point> worldverts;
	std::vector<vector> worldnorms;
	std::vector<vec2d> uvs;
	std::vector<point> clampverts;
	std::vector<std::vector<vec3i>> candidates;
	// image info
	int image_width;
	double aspect_ratio;
	// light info
	vector lightdir;
	// camera info
	point camerapos;
};

double saturate(const double& value)
{
	if(value < 0) return 0;
	if(value > 1) return 1;
	
	return value;
}

double max(const double& a, const double& b)
{
	return a > b ? a : b;
}

#endif // SHADER