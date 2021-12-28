#pragma once
#ifndef LIGHT
#define LIGHT

#include "..\core\geometry.h"
#include "..\core\transformation.h"

class light
{
public:
	/* light public methods */
	camera() {}
	camera(point p, vector d, vector u, int h, int w, double n, double f) : pos(p), lookat(l), up(u), pheight(h), pwidth(w), near(n), far(f) { lcu = cross(lookat, up); }

	/* light public data */
	point pos;
	vector direction;
	color col;
	double strength;
}

#endif // LIGHT