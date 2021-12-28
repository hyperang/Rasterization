#pragma once
#ifndef CORE_TRANSFORMATION
#define CORE_TRANSFORMATION

#include "geometry.h"

inline vec4d scale(double sx, double sy, double sz, const vec4d &v)
{
//	matrix4 smatrix = {vec4(sx, 0, 0, 0), vec4(0, sy, 0, 0), vec4(0, 0, sz, 0), vec4(0, 0, 0, 1)};
	return vec4d(v.x() * sx, v.y() * sy, v.z() * sz, v.w());
}

inline point translation(double tx, double ty, double tz, const point &p)
{
//	matrix4 tmatrix = {vec4(1, 0, 0, st), vec4(0, 1, 0, ty), vec4(0, 0, 1, tz), vec4(0, 0, 0, 1)};
	return point(p.x() + tx, p.y() + ty, p.z() + tz, p.w());
}

inline vec4d rotationx(double cosine, const vec4d &v)
{
//	matrix4 rxmatrix = {vec4(1, 0, 0, 0), vec4(0, cosine, -sine, 0), vec4(0, sine, cosine, 0), vec4(0, 0, 0, 1)};
	double sine = std::sqrt(1 - cosine * cosine);
	return vec4d(v.x(), v.y() * cosine - v.z() * sine, v.y() * sine + v.z() * cosine, v.w());
}

inline vec4d rotationy(double cosine, const vec4d &v)
{
//	matrix4 rymatrix = {vec4(cosine, 0, sine, 0), vec4(0, 1, 0, 0), vec4(-sine, 0, cosine, 0), vec4(0, 0, 0, 1)};
	double sine = std::sqrt(1 - cosine * cosine);
	return vec4d(v.x() * cosine + v.z() * sine, v.y(), v.z() * cosine - v.x() * sine, v.w());
}

inline vec4d rotationz(double cosine, const vec4d &v)
{
//	matrix4 rzmatrix = {vec4(cosine, -sine, 0, 0), vec4(sine, cosine, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1)};
	double sine = std::sqrt(1 - cosine * cosine);
	return vec4d(v.x() * cosine - v.y() * sine, v.x() * sine + v.y() * cosine, v.z(), v.w());
}

inline void translation(double tx, double ty, double tz, triangle &t)
{
	for(int k = 0; k < 3; k++)
	{
		t.p[k].e[0] += tx;
		t.p[k].e[1] += ty;
		t.p[k].e[2] += tz;
	}
}

inline void scale(double sx, double sy, double sz, triangle &t)
{
	//point p = t.p[0];
	//translation(-p.x(), -p.y(), -p.z(), t);

	//int i = 0;
	for(int k = 0; k < 3; k++)
	{
		t.p[k].e[0] *= sx;
		t.p[k].e[1] *= sy;
		t.p[k].e[2] *= sz;
	}

	//translation(p.x(), p.y(), p.z(), t);
}

inline void rotationx(double cosine, triangle &t)
{
	double sine = std::sqrt(1 - cosine * cosine);
	for(auto i : t.p)
	{
		i = rotationx(cosine, i);
	}
}

inline void rotationy(double cosine, triangle &t)
{
	double sine = std::sqrt(1 - cosine * cosine);
	for(auto i : t.p)
	{
		i = rotationy(cosine, i);
	}
}

inline void rotationz(double cosine, triangle &t)
{
	double sine = std::sqrt(1 - cosine * cosine);
	for(auto i : t.p)
	{
		i = rotationz(cosine, i);
	}
}

// method from "Efficiently Building a Matrix to Rotate One Vector to Another" by T. Moller and J.F. Hugues (1999)
inline matrix4 getRotationMat(vector from, vector to)
{
	vector f = normalize(from);
	vector t = normalize(to);
	vector v = cross(f, t);
	double c = dot(f, t);
	double h = 1 / (1 + c);
	matrix4 rmat = { vec4d(c + h * v.x() * v.x(), h * v.x() * v.y() - v.z(), h * v.x() * v.z() + v.y(), 0),
					 vec4d(h * v.x() * v.y() + v.z(), c + h * v.y() * v.y(), h * v.y() * v.z() - v.x(), 0),
					 vec4d(h * v.x() * v.z() - v.y(), h * v.y() * v.z() + v.x(), c + h * v.z() * v.z(), 0),
					 vec4d(0, 0, 0, 1) };
	return rmat;
}

inline double clamp(double x, double min, double max)
{
	if (x - min < 1e-4)
	{
		return min;
	}
	if (x - max > 1e-4)
	{
		return max;
	}
	return x;
}

#endif // CORE_TRANSFORMATION