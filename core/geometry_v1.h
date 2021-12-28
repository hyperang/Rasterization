#pragma once
#ifndef CORE_GEOMETRY
#define CORE_GEOMETRY

#include <cmath>
#include <iostream>
#include <assert.h>
#include <limits>
#include <vector>
#include <initializer_list>

using std::sqrt;
using std::fabs;

class vec2
{
public:
	/* vec2 public methods */
	vec2() : e{0, 0} {}
	vec2(double e0, double e1) : e{e0, e1} {}

	double x() const 
	{
		return e[0];
	}
	
	double y() const 
	{
		return e[1];
	}

	double u() const 
	{
		return e[0];
	}
	
	double v() const 
	{
		return e[1];
	}

	vec2 operator-() const
	{
		return vec2(-e[0], -e[1]); 
	}

	double operator[](int i) const
	{
		return e[i];
	}
	
	double& operator[](int i)
	{
		return e[i];
	}

	// Complex& operator -> return *this
	vec2& operator+=(const vec2 &v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		return *this;
	}

	vec2& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		return *this;
	}

	vec2& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1];
	}

	void set_zero()
	{
		e[0] = 0;
		e[1] = 0;
	}

	/* vec2 public data */
	double e[2];
};

inline vec2 operator*(double t, const vec2& v)
{
	return vec2(t * v.e[0], t * v.e[1]);
}

inline vec2 operator*(const vec2& u, const vec2& v)
{
	return vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

inline vec2 operator/(const vec2& u, double t)
{
	return (1 / t) * u;
}

inline vec2 normalize(const vec2& v)
{
	double length = v.length();
	return v / length;
}

inline double dot(const vec2 &u, const vec2 &v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1];
}

class vec4
{
public:
	/* vec4 public methods */
	vec4() : e{0, 0, 0, 0} {}
	vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}

	double x() const 
	{
		return e[0];
	}
	
	double y() const 
	{
		return e[1];
	}
	
	double z() const 
	{
		return e[2];
	}

	double w() const
	{
		return e[3];
	}

	double r() const 
	{
		return e[0];
	}
	
	double g() const 
	{
		return e[1];
	}
	
	double b() const 
	{
		return e[2];
	}

	double a() const
	{
		return e[3];
	}

	vec4 operator-() const
	{
		return vec4(-e[0], -e[1], -e[2], -e[3]); 
	}

	double operator[](int i) const
	{
		return e[i];
	}
	
	double& operator[](int i)
	{
		return e[i];
	}

	// Complex& operator -> return *this
	vec4& operator+=(const vec4 &v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		e[3] += v.e[3];
		return *this;
	}

	vec4& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		e[3] *= t;
		return *this;
	}

	vec4& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2] + e[3] * e[3];
	}

	void set_zero()
	{
		e[0] = 0;
		e[1] = 0;
		e[2] = 0;
		e[3] = 0;
	}

	void set_point()
	{
		e[3] = 1;
	}

	void set_vector()
	{
		e[3] = 0;
	}

	/* vec4 public data */
	double e[4];
};

using color = vec4;
using point = vec4; // e[3] = 1
using vector = vec4; // e[3] = 0

// vec4 inline methods
inline std::ostream& operator<<(std::ostream& out, const vec4& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

inline vec4 operator+(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

inline vec4 operator-(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
}

inline vec4 operator*(const vec4& u, const vec4& v)
{
	return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

inline vec4 operator*(double t, const vec4& v)
{
	return vec4(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
}

inline vec4 operator*(const vec4& v, double t)
{
	return t * v;
}

inline vec4 operator/(const vec4& u, double t)
{
	return (1 / t) * u;
}

inline double dot(const vec4& u, const vec4& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2] + u.e[3] * v.e[3];
}

inline vec4 cross(const vec4& u, const vec4& v)
{
	return vec4(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0],
				0);
}

inline vector normalize(const vector& v)
{
	double length = v.length();
	double mark = v.e[3];
	vector res = v;
	res /= length;
	res.e[3] = mark;
	return res;
}

// {vec4,	row1
//	vec4,	row2
//  vec4,	row3
//  vec4}	row4
using matrix4 = std::vector<vec4>;

inline matrix4 matrixMulti(const vec4 &v0, const vec4 &v1)
{
	matrix4 mat { vec4(v0.x() * v1.x(), v0.x() * v1.y(), v0.x() * v1.z(), v0.x() * v1.z()),
				  vec4(v0.y() * v1.x(), v0.y() * v1.y(), v0.y() * v1.z(), v0.y() * v1.z()),
				  vec4(v0.z() * v1.x(), v0.z() * v1.y(), v0.z() * v1.z(), v0.z() * v1.z()),
				  vec4(v0.w() * v1.x(), v0.w() * v1.y(), v0.w() * v1.z(), v0.w() * v1.z())
				};

	return mat;
}

inline vec4 matrixMulti(const matrix4 &m, const vec4 &v)
{
	return vec4(dot(m[0], v), dot(m[1], v), dot(m[2], v), dot(m[3], v));
}

inline matrix4 matrixMulti(const matrix4 &m0, const matrix4 &m1)
{
	matrix4 mat { vec4(dot(m0[0], vec4(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[0], vec4(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[0], vec4(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[0], vec4(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4(dot(m0[1], vec4(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[1], vec4(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[1], vec4(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[1], vec4(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4(dot(m0[2], vec4(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[2], vec4(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[2], vec4(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[2], vec4(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4(dot(m0[3], vec4(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[3], vec4(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[3], vec4(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[3], vec4(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w())))
				};

	return mat;
}

inline matrix4 matrixMulti(const std::initializer_list<matrix4>& l)
{
	matrix4 res = { vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1) };

	for(auto it = l.begin(); it != l.end(); ++it)
	{
		matrix4 temp = matrixMulti(*it, res);
		res = temp;
	}

	return res;
}

inline std::ostream& operator<<(std::ostream& out, const matrix4& m)
{
	return out << m[0].e[0] << ' ' << m[0].e[1] << ' ' << m[0].e[2] << ' ' << m[0].e[3] << std::endl
			   << m[1].e[0] << ' ' << m[1].e[1] << ' ' << m[1].e[2] << ' ' << m[1].e[3] << std::endl
			   << m[2].e[0] << ' ' << m[2].e[1] << ' ' << m[2].e[2] << ' ' << m[2].e[3] << std::endl
			   << m[3].e[0] << ' ' << m[3].e[1] << ' ' << m[3].e[2] << ' ' << m[3].e[3];
}

class triangle
{
public:
	/* triangle public methods */
	triangle() {}
	triangle(const point &p0, const point &p1, const point &p2) : p{p0, p1, p2} 
	{
		setedge();
	}

	point operator[](int i) const
	{
		return p[i];
	}

	point& operator[](int i)
	{
		return p[i];
	}

	void setedge()
	{
		edge[0] = std::min(std::min(p[0].x(), p[1].x()), p[2].x());
		edge[1] = std::max(std::max(p[0].x(), p[1].x()), p[2].x());
		edge[2] = std::min(std::min(p[0].y(), p[1].y()), p[2].y());
		edge[3] = std::max(std::max(p[0].y(), p[1].y()), p[2].y());
		edge[4] = std::min(std::min(p[0].z(), p[1].z()), p[2].z());
		edge[5] = std::max(std::max(p[0].z(), p[1].z()), p[2].z());
	}

	double* getedge()
	{
		double *p;
		p = edge;
		return p;
	}

	void transform(matrix4& mat)
	{
		for(int i = 0; i < 3; i++)
		{
			point tmp = matrixMulti(mat, p[i]);
			p[i] = tmp;
		}

		setedge();
	}

	bool isInTriangle(double x, double y)
	{
		if(x < edge[0] || x > edge[1] || y < edge[2] || y > edge[3]) return false;

		vec2 v0 = vec2(p[1].x() - p[0].x(), p[1].y() - p[0].y());
		vec2 v1 = vec2(p[2].x() - p[0].x(), p[2].y() - p[0].y());
		vec2 v2 = vec2(x - p[0].x(), y - p[0].y());

		double dot00 = dot(v0, v0);
		double dot01 = dot(v0, v1);
		double dot02 = dot(v0, v2);
		double dot11 = dot(v1, v1);
		double dot12 = dot(v1, v2);

		double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

		double u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
		if(u < 0 || u > 1) return false;
		double v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
		if(v < 0 || v > 1) return false;

		return u + v <= 1;
	}

	vec4 barycentric(double x, double y)
	{
		vec2 v0 = vec2(p[1].x() - p[0].x(), p[1].y() - p[0].y());
		vec2 v1 = vec2(p[2].x() - p[0].x(), p[2].y() - p[0].y());
		vec2 v2 = vec2(x - p[0].x(), y - p[0].y());

		double dot00 = dot(v0, v0);
		double dot01 = dot(v0, v1);
		double dot02 = dot(v0, v2);
		double dot11 = dot(v1, v1);
		double dot12 = dot(v1, v2);

		double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

		double u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
		double v = (dot00 * dot12 - dot01 * dot02) * inverDeno;

		return vec4((1 - u - v), u, v, 0);
	}

	double getz(double x, double y) const
	{
		// if(!isInTriangle(x, y)) return 1;
		if(x < edge[0] || x > edge[1] || y < edge[2] || y > edge[3]) return 1;

		vec2 v0 = vec2(p[1].x() - p[0].x(), p[1].y() - p[0].y());
		vec2 v1 = vec2(p[2].x() - p[0].x(), p[2].y() - p[0].y());
		vec2 v2 = vec2(x - p[0].x(), y - p[0].y());

		double dot00 = dot(v0, v0);
		double dot01 = dot(v0, v1);
		double dot02 = dot(v0, v2);
		double dot11 = dot(v1, v1);
		double dot12 = dot(v1, v2);

		double inverDeno = 1. / (dot00 * dot11 - dot01 * dot01);

		double u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
		if(u - 0. < 1e-9 || u - 1. > 1e-9) return 1.;
		double v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
		if(v - 0. < 1e-9 || v - 1. > 1e-9) return 1.;

		if(u + v - 1. > 1e-9) return 1.;
		
		// func from https://zhuanlan.zhihu.com/p/403259571
		//double z = 1 / (u / p[1].z() + v / p[2].z() + (1 - u - v) / p[0].z());
		double z = u * p[1].z() + v * p[2].z() + (1 - u - v) * p[0].z();

		return (z - 1.) / 2. * (-1.);
	}

	/* triangle public data */
	point p[3];
	vector n;
	double edge[6]; // edge{ xmin, xmax, ymin, ymax, zmin, zmax }
};

inline std::ostream& operator<<(std::ostream& out, const triangle& t)
{
	return out << t.p[0] << std::endl << t.p[1] << std::endl << t.p[2];
}

class line
{
public:
	/* line public method */
	line() {}
	line(double x0, double y0, double x1, double y1) : startx(int(x0)), starty(int(y0)), endx(int(x1)), endy(int(y1))
	{
		gradient = (y1 - y0) / (x1 - x0);
	}

	/* line public data */
	int startx, starty;
	int endx, endy;
	double gradient;
};

#endif // CORE_GEOMETRY