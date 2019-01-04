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

class Vec3
{
public:
	Vec3() {}
	Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	
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
	
	inline Vec3& operator+=(const Vec3 &v);
	inline Vec3& operator-=(const Vec3 &v);
	inline Vec3& operator*=(const Vec3 &v);
	inline Vec3& operator/=(const Vec3 &v);
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);
	
	inline float Lenght() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float SqrLenght() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline void Normalize(); //normalize vector
	
public:
	float e[3];
	
};

inline void Vec3::Normalize()
{
	const float k = 1.0 / Lenght();
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

inline Vec3 operator/(const Vec3 &v, float t)
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
	return v / v.Lenght();
}

#endif /* vec3_hpp */
