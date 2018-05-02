//
//  vec3.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#include "vec3.hpp"

//inline std::istream& operator>>(std::istream &is, vec3 &t)
//{
//	is >> t.e[0] >> t.e[1] >> t.e[2];
//	return is;
//}
//
//inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
//{
//	os << t.e[0] << t.e[1] << t.e[2];
//	return os;
//}
//
//inline void vec3::make_unit_vector()
//{
//	const float k = 1.0 / length();
//	e[0] *= k; e[1] *= k; e[2] *= k;
//}
//
//inline vec3 operator+(const vec3 &v1, const vec3 &v2)
//{
//	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
//}
//
//inline vec3 operator-(const vec3 &v1, const vec3 &v2)
//{
//	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
//}
//
//inline vec3 operator*(const vec3 &v1, const vec3 &v2)
//{
//	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
//}
//
//inline vec3 operator/(const vec3 &v1, const vec3 &v2)
//{
//	float d0, d1, d2;
//	if (v2.e[0] != 0)
//		d0 = v1.e[0] / v2.e[0];
//	else
//		d0 = MAXFLOAT;
//		
//	if (v2.e[1] != 0)
//		d1 = v1.e[1] / v2.e[1];
//	else
//		d1 = MAXFLOAT;
//
//	if (v2.e[2] != 0)
//		d2 = v1.e[2] / v2.e[2];
//	else
//		d2 = MAXFLOAT;
//	
//	return vec3(d0, d1, d2);
//}
//
//inline vec3 operator*(const vec3 &v, float t)
//{
//	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
//}
//
//inline vec3 operator/(const vec3 &v, float t)
//{
//	if (t != 0)
//		return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
//	else
//		return vec3(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//}
//
//inline float dot (const vec3 &v1, const vec3 &v2)
//{
//	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
//}
//
//inline vec3 cross (const vec3 &v1, const vec3 &v2)
//{
//	return vec3(v1.e[1] * v2.e[2] - v2.e[1] * v1.e[2],
//							v1.e[2] * v2.e[0] - v2.e[2] * v1.e[0],
//							v1.e[0] * v2.e[1] - v2.e[0] * v1.e[1]);
//}
//
//inline vec3& vec3::operator+=(const vec3 &v)
//{
//	e[0] += v.e[0];
//	e[1] += v.e[1];
//	e[2] += v.e[2];
//	return *this;
//}
//
//inline vec3& vec3::operator-=(const vec3 &v)
//{
//	e[0] -= v.e[0];
//	e[1] -= v.e[1];
//	e[2] -= v.e[2];
//	return *this;
//}
//inline vec3& vec3::operator*=(const vec3 &v)
//{
//	e[0] *= v.e[0];
//	e[1] *= v.e[1];
//	e[2] *= v.e[2];
//	return *this;
//}
//
//inline vec3& vec3::operator/=(const vec3 &v)
//{
//	if (v.e[0] != 0)
//		e[0] /= v.e[0];
//	else
//		e[0] = MAXFLOAT;
//	if (v.e[1] != 0)
//		e[1] /= v.e[1];
//	else
//		e[1] = MAXFLOAT;
//	if (v.e[2] != 0)
//		e[2] /= v.e[2];
//	else
//		e[2] = MAXFLOAT;
//	
//	return *this;
//}
//
//inline vec3 unit_vector(vec3 v)
//{
//	return v / v.length();
//}
