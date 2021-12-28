#pragma once
#ifndef CORE_OBJECT
#define CORE_OBJECT

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

#include "geometry.h"

class object
{
public:
	/* object public methods */
	object() {}
	~object() {}
	object(const char *filename)
	{
		std::ifstream in;
		in.open(filename, std::ifstream::in);

		if(in.fail()) return;
		std::string line;
		while(!in.eof())
		{
			std::getline(in, line);
			std::istringstream iss(line.c_str());
			char trash;
			if (!line.compare(0, 2, "v "))
			{
				iss >> trash;
				vector v;
				for (int i = 0; i < 4; ++i)
				{
					if (i == 3)
					{
						v.e[i] = 1;
					}
					else
					{
						iss >> v.e[i];
					}
				}
				vertslist.push_back(v);
			}
			else if (!line.compare(0, 3, "vn "))
			{
				iss >> trash >> trash;
				vector n;
				for (int i = 0; i < 4; ++i)
				{
					if (i == 3)
					{
						n.e[i] = 0;
					}
					else
					{
						iss >> n.e[i];
					}
				}
				normslist.push_back(n);
			}
			else if (!line.compare(0, 3, "vt "))
			{
				iss >> trash >> trash;
				vec2d uv;
				for (int i = 0; i < 2; ++i)
				{
					iss >> uv[i];
				}
				uvslist.push_back(uv);
			}
			else if (!line.compare(0, 2, "f "))
			{
				std::vector<vec3i> f;
				vec3i id;
				int idx;
				iss >> trash;
				// f x/y/z x/y/z x/y/z : x--vert, y---uv, z--normal
				if(line.find('/') != std::string::npos)
				{
					while(iss >> id[0] >> trash >> id[1] >> trash >> id[2])
					{
						for(int i = 0; i < 3; i++) id[i]--; // in wavefront obj all indices start at 1
						f.push_back(id);
					}
				}
				else
				{
					while(iss >> idx)
					{
						idx--; // in wavefront obj all indices start at 1
						vec3i tmp(idx, -1, -1);
						f.push_back(tmp);
					}
				}
				faceslist.push_back(f);
			}
		}
		std::cerr << "# v# " << vertslist.size() << " f# " << faceslist.size() << std::endl;
	}

	int numverts()
	{
		return (int)vertslist.size();
	}

	int numfaces()
	{
		return (int)faceslist.size();
	}

	std::vector<vec3i> face(int idx)
	{
		return faceslist[idx];
	}

	point vert(int idx)
	{
		return vertslist[idx];
	}

	/* object public data */
	std::vector<point> vertslist;
	std::vector<vector> normslist;
	std::vector<vec2d> uvslist;
	std::vector<std::vector<vec3i>> faceslist;
	point position;
};

#endif // CORE_OBJECT