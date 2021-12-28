#pragma once
#ifndef CORE_DEEPMAP
#define CORE_DEEPMAP

#include "geometry.h"
#include "transformation.h"

#include <vector>

class deepmap
{
public:
	/* deepmap public methods */
	deepmap() {};
	deepmap(int w, int h) : width(w), height(h)
	{
		_deepmap = std::vector<std::vector<double>>(width, std::vector<double>(height, 1));
	}

	bool update(int x, int y, double z)
	{
		if(z < _deepmap[x][y]) 
		{
			_deepmap[x][y] = z;
			return true;
		}

		return false;
	}
	
	/* deepmap public data */
	int height, width;
	std::vector<std::vector<double>> _deepmap;
};

#endif // CORE_DEEPMAP