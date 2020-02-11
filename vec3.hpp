//
//  vec3.h
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#ifndef vec3_hpp
#define vec3_hpp

#include <math.h>
#include <iostream>

#define WIN
#ifdef WIN
#define _USE_MATH_DEFINES
#ifndef MAXFLOAT
#define MAXFLOAT FLT_MAX
#endif
#include <cassert>
#include <stdio.h>
#include <stdarg.h>
#include <float.h>
#include "drand48.h"
#endif


class Vec3
{
public:
	Vec3() {}
	Vec3(float e0, float e1, float e2) {	e[0] = e0; e[1] = e1; e[2] = e2; }
	Vec3(float v) {	e[0] = v; e[1] = v; e[2] = v; }
	~Vec3()	{}
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }
	
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator -() const { return Vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }
	
	inline bool  operator==(const Vec3 &v);
	inline bool  operator!=(const Vec3 &v);
	inline Vec3& operator+=(const Vec3 &v);
	inline Vec3& operator-=(const Vec3 &v);
	inline Vec3& operator*=(const Vec3 &v);
	inline Vec3& operator/=(const Vec3 &v);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);
	
	inline float Length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float SqrLength() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline void Normalize(); //normalize vector
	inline Vec3 GetNormalized(); // return normalized vector
	
public:
	float e[3];
	
};

inline bool Vec3::operator==(const Vec3 &v)
{
	if (e[0] != v.e[0] || e[1] != v.e[1] || e[2] != v.e[2])
		return false;
	
	return true;
}

inline bool Vec3::operator!=(const Vec3 &v)
{
	return !((*this)==v);
}

inline void Vec3::Normalize()
{
	const float k = 1.0 / Length();
	e[0] *= k; e[1] *= k; e[2] *= k;
}

inline Vec3& Vec3::operator+=(const Vec3 &v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const Vec3 &v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v)
{
	if (v.e[0] != 0)
		e[0] /= v.e[0];
	else
		e[0] = MAXFLOAT;
	if (v.e[1] != 0)
		e[1] /= v.e[1];
	else
		e[1] = MAXFLOAT;
	if (v.e[2] != 0)
		e[2] /= v.e[2];
	else
		e[2] = MAXFLOAT;
	
	return *this;
}

inline Vec3& Vec3::operator*=(const float t) {
	e[0]  *= t;
	e[1]  *= t;
	e[2]  *= t;
	return *this;
}

inline Vec3& Vec3::operator/=(const float t) {
	float k = 1.0/t;
	
	e[0]  *= k;
	e[1]  *= k;
	e[2]  *= k;
	return *this;
}

inline Vec3 Vec3::GetNormalized()
{
	Vec3 res;
	const float k = (1.0 / this->Length());
	res[0] = this->e[0] * k;
	res[1] = this->e[1] * k;
	res[2] = this->e[2] * k;
	return res;
}

inline std::istream& operator>>(std::istream &is, Vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
	float d0, d1, d2;
	if (v2.e[0] != 0)
		d0 = v1.e[0] / v2.e[0];
	else
		d0 = MAXFLOAT;
	
	if (v2.e[1] != 0)
		d1 = v1.e[1] / v2.e[1];
	else
		d1 = MAXFLOAT;
	
	if (v2.e[2] != 0)
		d2 = v1.e[2] / v2.e[2];
	else
		d2 = MAXFLOAT;
	
	return Vec3(d0, d1, d2);
}

inline Vec3 operator*(const Vec3 &v, float t)
{
	return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3 operator*(float t, const Vec3 &v)
{
	return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
	if (t != 0)
		return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	else
		return Vec3(MAXFLOAT, MAXFLOAT, MAXFLOAT);
}

inline Vec3 operator/(float t, const Vec3 &v)
{
	if (t != 0)
		return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	else
		return Vec3(MAXFLOAT, MAXFLOAT, MAXFLOAT);
}

inline float Dot (const Vec3 &v1, const Vec3 &v2)
{
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

inline Vec3 Cross (const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.e[1] * v2.e[2] - v2.e[1] * v1.e[2],
							v1.e[2] * v2.e[0] - v2.e[2] * v1.e[0],
							v1.e[0] * v2.e[1] - v2.e[0] * v1.e[1]);
}

inline Vec3 Normalize(Vec3 v)
{
	const float k = 1.0 / v.Length();
	return Vec3(v[0] *= k, v[1] *= k, v[2] *= k);
}

// Generate a random point lying on a sphere
inline Vec3 RandomPointOnSphere(float radius = 1)
{
	Vec3 p;
	
	// algorithm of the rejection method
	do
		p = Vec3(drand48(), drand48(), drand48()) * 2 * radius - Vec3( 1, 1, 1) * radius;
	while (p.SqrLength() >= radius);
	
	return p;
}

inline Vec3 RandomPointOnDisk(float radius = 1)
{
	Vec3 p;
	
	// algorithm of the rejection method
	do
		p = Vec3(drand48(), drand48(), 0) * 2 * radius - Vec3( 1, 1, 0) * radius;
	while (p.SqrLength() >= radius);
	
	return p;
}

// Generate a reflected direction given an incident direction and the normal of the reflecting plane
inline Vec3 ReflectRay(const Vec3& in, const Vec3& n)
{
	const float inLength = in.Length();
	const float nLength = n.Length();
	const float dotLength = Dot(in, n);
	const float dotLengthByN = (2 * Dot(in, n) * n).Length();
	return (in - 2 * Dot(in, n) * n);
}

// Generate a refracted direction given an incident direction, the normal of the reflecting plane and the two indexes of refraction
inline Vec3 RefractRay(const Vec3& in, const Vec3& n, float ni_over_nt, bool& isRefracted)
{
	Vec3 uv = Normalize(in);	
	float dt = Dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0)
	{
		isRefracted = true;
		return ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
	}
	isRefracted = false;
	return Vec3(0,0,0);
}

#endif /* vec3_hpp */
