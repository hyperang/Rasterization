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

// vec2
template<typename T>
class vec2
{
public:
	/* vec2 public methods */
	vec2() : e{0, 0} {}
	vec2(T e0, T e1) : e{e0, e1} {}

	T x() const 
	{
		return e[0];
	}
	
	T y() const 
	{
		return e[1];
	}

	T u() const 
	{
		return e[0];
	}
	
	T v() const 
	{
		return e[1];
	}

	vec2 operator-() const
	{
		return vec2(-e[0], -e[1]); 
	}

	T operator[](int i) const
	{
		return e[i];
	}
	
	T& operator[](int i)
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
		return sqrt(double(length_squared()));
	}

	T length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1];
	}

	void set_zero()
	{
		e[0] = 0;
		e[1] = 0;
	}

	/* vec2 public data */
	T e[2];
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

template<typename T> inline vec2<T> operator*(T t, const vec2<T>& v)
{
	return vec2<T>(t * v.e[0], t * v.e[1]);
}

template<typename T> inline vec2<T> operator*(const vec2<T>& u, const vec2<T>& v)
{
	return vec2<T>(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

template<typename T> inline vec2<T> operator/(const vec2<T>& u, T t)
{
	return (1 / t) * u;
}

template<typename T> inline vec2<T> operator+(const vec2<T>& u, const vec2<T>& v)
{
	return vec2<T>(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

template<typename T> inline vec2<T> normalize(const vec2<T>& v)
{
	double length = v.length();
	return v / length;
}

template<typename T> inline double dot(const vec2<T> &u, const vec2<T> &v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1];
}

// vec3
template<typename T>
class vec3
{
public:
	/* vec3 public methods */
	vec3() : e{0, 0, 0} {}
	vec3(T e0, T e1, T e2) : e{e0, e1, e2} {}

	T x() const 
	{
		return e[0];
	}
	
	T y() const 
	{
		return e[1];
	}

	T z() const
	{
		return e[2];
	}

	T r() const 
	{
		return e[0];
	}
	
	T g() const 
	{
		return e[1];
	}

	T b() const
	{
		return e[2];
	}

	vec3 operator-() const
	{
		return vec3(-e[0], -e[1], -e[2]); 
	}

	T operator[](int i) const
	{
		return e[i];
	}
	
	T& operator[](int i)
	{
		return e[i];
	}

	// Complex& operator -> return *this
	vec3& operator+=(const vec3 &v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return sqrt(double(length_squared()));
	}

	T length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	void set_zero()
	{
		e[0] = 0;
		e[1] = 0;
		e[2] = 0;
	}

	/* vec3 public data */
	T e[3];
};

using vec3i = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;

template<typename T> inline vec3<T> operator*(T t, const vec3<T>& v)
{
	return vec3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template<typename T> inline vec3<T> operator*(const vec3<T>& v, T t)
{
	return vec3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template<typename T> inline vec3<T> operator+(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template<typename T> inline vec3<T> operator-(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template<typename T> inline vec3<T> operator*(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template<typename T> inline vec3<T> operator/(const vec3<T>& u, T t)
{
	return (1 / t) * u;
}

template<typename T> inline vec3<T> normalize(const vec3<T>& v)
{
	double length = v.length();
	return v / length;
}

template<typename T> inline double dot(const vec3<T> &u, const vec3<T> &v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

template<typename T> inline vec3<T> cross(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// vec4
template<typename T>
class vec4
{
public:
	/* vec4 public methods */
	vec4() : e{0, 0, 0, 0} {}
	vec4(T e0, T e1, T e2, T e3) : e{e0, e1, e2, e3} {}

	T x() const 
	{
		return e[0];
	}
	
	T y() const 
	{
		return e[1];
	}
	
	T z() const 
	{
		return e[2];
	}

	T w() const
	{
		return e[3];
	}

	T r() const 
	{
		return e[0];
	}
	
	T g() const 
	{
		return e[1];
	}
	
	T b() const 
	{
		return e[2];
	}

	T a() const
	{
		return e[3];
	}

	vec4 operator-() const
	{
		return vec4(-e[0], -e[1], -e[2], -e[3]); 
	}

	T operator[](int i) const
	{
		return e[i];
	}
	
	T& operator[](int i)
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
		return sqrt(double(length_squared()));
	}

	T length_squared() const
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
	T e[4];
};

using vec4i = vec4<int>;
using vec4f = vec4<float>;
using vec4d = vec4<double>;
using color = vec4d;
using point = vec4d; // e[3] = 1
using vector = vec4d; // e[3] = 0

// vec4 inline methods
template<typename T> inline std::ostream& operator<<(std::ostream& out, const vec4<T>& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

template<typename T> inline vec4<T> operator+(const vec4<T>& u, const vec4<T>& v)
{
	return vec4<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

template<typename T> inline vec4<T> operator-(const vec4<T>& u, const vec4<T>& v)
{
	return vec4<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
}

template<typename T> inline vec4<T> operator*(const vec4<T>& u, const vec4<T>& v)
{
	return vec4<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

template<typename T> inline vec4<T> operator*(T t, const vec4<T>& v)
{
	return vec4<T>(t * v.e[0], t * v.e[1], t * v.e[2], t * v.e[3]);
}

template<typename T> inline vec4<T> operator*(const vec4<T>& v, T t)
{
	return t * v;
}

template<typename T> inline vec4<T> operator/(const vec4<T>& u, T t)
{
	return (1 / t) * u;
}

template<typename T> inline T dot(const vec4<T>& u, const vec4<T>& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2] + u.e[3] * v.e[3];
}

template<typename T> inline vec4<T> cross(const vec4<T>& u, const vec4<T>& v)
{
	return vec4<T>(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0],
				0);
}

template<typename T> inline vec4<T> normalize(const vec4<T>& v)
{
	double length = v.length();
	T mark = v.e[3];
	vec4<T> res = v;
	res /= length;
	res.e[3] = mark;
	return res;
}

// {vec4d,	row1
//	vec4d,	row2
//  vec4d,	row3
//  vec4d}	row4
using matrix4 = std::vector<vec4d>;

inline matrix4 matrixMulti(const vec4d &v0, const vec4d &v1)
{
	matrix4 mat { vec4d(v0.x() * v1.x(), v0.x() * v1.y(), v0.x() * v1.z(), v0.x() * v1.z()),
				  vec4d(v0.y() * v1.x(), v0.y() * v1.y(), v0.y() * v1.z(), v0.y() * v1.z()),
				  vec4d(v0.z() * v1.x(), v0.z() * v1.y(), v0.z() * v1.z(), v0.z() * v1.z()),
				  vec4d(v0.w() * v1.x(), v0.w() * v1.y(), v0.w() * v1.z(), v0.w() * v1.z())
				};

	return mat;
}

inline vec4d matrixMulti(const matrix4 &m, const vec4d &v)
{
	return vec4d(dot(m[0], v), dot(m[1], v), dot(m[2], v), dot(m[3], v));
}

inline matrix4 matrixMulti(const matrix4 &m0, const matrix4 &m1)
{
	matrix4 mat { vec4d(dot(m0[0], vec4d(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[0], vec4d(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[0], vec4d(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[0], vec4d(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4d(dot(m0[1], vec4d(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[1], vec4d(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[1], vec4d(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[1], vec4d(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4d(dot(m0[2], vec4d(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[2], vec4d(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[2], vec4d(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[2], vec4d(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w()))),
				  vec4d(dot(m0[3], vec4d(m1[0].x(), m1[1].x(), m1[2].x(), m1[3].x())), dot(m0[3], vec4d(m1[0].y(), m1[1].y(), m1[2].y(), m1[3].y())), dot(m0[3], vec4d(m1[0].z(), m1[1].z(), m1[2].z(), m1[3].z())), dot(m0[3], vec4d(m1[0].w(), m1[1].w(), m1[2].w(), m1[3].w())))
				};

	return mat;
}

inline matrix4 matrixMulti(const std::initializer_list<matrix4>& l)
{
	matrix4 res = { vec4d(1, 0, 0, 0), vec4d(0, 1, 0, 0), vec4d(0, 0, 1, 0), vec4d(0, 0, 0, 1) };

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

	vec3d barycentric(double x, double y) const
	{
		vec2d ab(p[1].x() - p[0].x(), p[1].y() - p[0].y());
		vec2d ac(p[2].x() - p[0].x(), p[2].y() - p[0].y());
		vec2d pa(p[0].x() - x, p[0].y() - y);

		vec3d xx(ab.x(), ac.x(), pa.x());
		vec3d yy(ab.y(), ac.y(), pa.y());

		vec3d uv = cross(xx, yy);

		if (std::abs(uv.z()) > 1e-4)
		{
			return vec3d(1. - (uv.x() + uv.y()) / uv.z(), uv.x() / uv.z(), uv.y() / uv.z());
		}

		return vec3d(-1, 1, 1);
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