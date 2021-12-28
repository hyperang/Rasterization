#pragma once
#ifndef SCENE
#define SCENE

#include "../core/geometry.h"
#include "../core/transformation.h"
// #include "../cameras/orthocamera.h"
// #include "../cameras/perspcamera.h"
#include "../objects/object.h"
// #include "../lights/directlight.h"

#include <vector>

class scene
{
public:
	/* scene public methods */
	scene() {}
	~scene() {}

	void add_object(shared_ptr<object> o)
	{
		objectslist.push_back(o);
	}

	/* scene public data */
	std::vector<shared_ptr<object>> objectslist;
};

#endif // SCENE