#pragma once
#ifndef CAMERA
#define CAMERA

#include "..\core\geometry.h"
#include "..\core\transformation.h"

class camera
{
public:
	/* camera public methods */
	virtual matrix4 world2clampMat() = 0;

	/* camera public data */
	point pos;
	vector lookat;
	vector up;
	vector lcu;
	int pheight, pwidth;
	double near, far;
};

#endif // CAMERA