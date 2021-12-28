#pragma once
#ifndef ORTHOCAMERA
#define ORTHOCAMERA 

#include "camera.h"

class orthocamera : public camera
{
public:
	/* orthocamera public methods */
	orthocamera() {}
	orthocamera(point p, vector l, vector u, int ph, int pw, double n, double f, double h, double w) : height(h), width(w)
	{
		pos = p;

		lookat = normalize(l);

		up = normalize(u);

		pheight = ph;

		pwidth = pw;

		near = n;

		far = f;

		lcu = normalize(cross(lookat, up));

		matrix4 tview = { vec4d(1, 0, 0, -pos.x()), vec4d(0, 1, 0, -pos.y()), vec4d(0, 0, 1, -pos.z()), vec4d(0, 0, 0, 1) };
		
		matrix4 rview = { vec4d(lcu.x(), lcu.y(), lcu.z(), 0), vec4d(up.x(), up.y(), up.z(), 0), vec4d(-lookat.x(), -lookat.y(), -lookat.z(), 0), vec4d(0, 0, 0, 1) };

		matrix4 tortho = { vec4d(1, 0, 0, 0), vec4d(0, 1, 0, 0), vec4d(0, 0, 1, -(near + far) / 2), vec4d(0, 0, 0, 1) };

		matrix4 sortho = { vec4d(2 / width, 0, 0, 0), vec4d(0, 2 / height, 0, 0), vec4d(0, 0, 2 / (near - far), 0), vec4d(0, 0, 0, 1) };

		matrix4 mviewport = { vec4d(pwidth / 2, 0, 0, pwidth / 2), vec4d(0, pheight / 2, 0, pheight / 2), vec4d(0, 0, 1, 0), vec4d(0, 0, 0, 1) };

		world2clamp = matrixMulti({ tview, rview, tortho, sortho, mviewport });
	}

	virtual matrix4 world2clampMat()
	{
		return world2clamp;
	}

	/* orthocamera public data */
	double height;
	double width;
	matrix4 world2clamp;
};

#endif // ORTHOCAMERA