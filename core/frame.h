#pragma once
#ifndef CORE_FRAME
#define CORE_FRAME

#include "geometry.h"
#include "transformation.h"
#include "deepmap.h"

#include <vector>
#include <math.h>

class frame
{
public:
	/* frame public methods */
	frame() {}
	frame(int w, int h) : width(w), height(h)
	{
		_frame = std::vector<std::vector<color>>(width, std::vector<color>(height, color(0, 0, 0, 0)));
	}

	// original Bresenham's line algorithm
	void bresenham(int &sx, int &sy, int &ex, int &ey, color &col)
	{
		int x = sx;
		int y = sy;
		int dx = ex - sx;
		int dy = ey - sy;
		int p = 2 * dy - dx;
		int step = 0;

		while(step <= dx)
		{
			if(x >= width || x < 0 || y >= height || y < 0) break;

			_frame[x][y] = col;
			x++;
			step++;
			if(p < 0) p = p + 2 * dy;
			else
			{
				p = p + 2 * (dy - dx);
				y++;
			}
		}
	}

	void drawline(int &sx, int &sy, int &ex, int &ey, color &col)
	{
		int _sx = sx;
		int _sy = sy;
		int _ex = ex;
		int _ey = ey;

		if (_sx < 0) _sx = 0;
		if (_sx > width - 1) _sx = width - 1;
		if (_ex < 0) _ex = 0;
		if (_ex > width - 1) _ex = width - 1;
		if (_sy < 0) _sy = 0;
		if (_sy > height - 1) _sy = height - 1;
		if (_ey < 0) _ey = 0;
		if (_ey > height - 1) _ey = height - 1; 

		if(_sx > _ex) { std::swap(_sx, _ex); std::swap(_sy, _ey); }
		if(_sx == _ex) { if(_sy > _ey) { std::swap(_sx, _ex); std::swap(_sy, _ey); } }

		int dx = _ex - _sx;
		int dy = _ey - _sy;

		if(std::abs(dx) >= std::abs(dy))
		{
			if (dy >= 0) bresenham(_sx, _sy, _ex, _ey, col);
			else 
			{
				int x = _sx;
				int y = -_sy;
				int step = 0;
				
				int p =-2 * dy - dx;

				while(step <= dx)
				{
					if(x >= width || x < 0 || -y >= height || -y < 0) break;

					_frame[x][-y] = col;
					x++;
					step++;
					if(p < 0) p = p - 2 * dy;
					else
					{
						p = p + 2 * (-dy - dx);
						y++;
					}
				}
			}
		}
		
		else
		{
			if(dy >= 0)
			{
				int x = _sx;
				int y = _sy;
				int step = 0;
				
				int p =2 * dx - dy;

				while(step <= std::abs(dy))
				{
					if(x >= width || x < 0 || y >= height || y < 0) break;

					_frame[x][y] = col;
					y++;
					step++;
					if(p < 0) p = p + 2 * dx;
					else
					{
						p = p + 2 * (dx - dy);
						x++;
					}
				}
			}
			else
			{
				int x = _sx;
				int y = -_sy;
				int step = 0;
				
				int p =2 * dx + dy;

				while(step <= std::abs(dy))
				{
					if(x >= width || x < 0 || -y >= height || -y < 0) break;

					_frame[x][-y] = col;
					y++;
					step++;
					if(p < 0) p = p + 2 * dx;
					else
					{
						p = p + 2 * (dx + dy);
						x++;
					}
				}
			}
		}
	}

	inline void drawpixel(const int& x, const int& y, const color& col)
	{
		_frame[x][y] = col;
	}

	color pixelcol(int& x, int& y)
	{
		return _frame[x][y];
	}

	inline void drawtriangle(const triangle& t, deepmap& dp, const color& col)
	{
		if(t.edge[0] - double(width) > 1e-7 || t.edge[1] - 0. < 1e-7 || t.edge[2] - double(height) > 1e-7 || t.edge[3] - 0. < 1e-7)
		{
			// not render
		}
		else
		{
			int xbegin = (t.edge[0] - 0. > 1e-7) ? int(t.edge[0]) : 0;
			int ybegin = (t.edge[2] - 0. > 1e-7)  ? int(t.edge[2]) : 0;
			int xend = (t.edge[1] - double(width) < 1e-7) ? int(t.edge[1]) : width;
			int yend = (t.edge[3] - double(height) < 1e-7) ? int(t.edge[3]) : height;

			// update deepmap and frame
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
					if(dp.update(i, j, z))
					{
						this->drawpixel(i, j, col);
					}
				}
			}
		}
	}

	
	/* frame public data */
	int height, width;
	std::vector<std::vector<color>> _frame;
};

#endif // CORE_FRAME