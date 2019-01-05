//
//  triangle.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "triangle.hpp"


Triangle::Triangle(Vec3 a, Vec3 b, Vec3 c, Material* m) : _a(a), _b(b), _c(c), _mat(m)
{
	_ab = _a - _b;
	_bc = _b - _c;
	_ca = _c - _a;
	_n = Normalize(Cross(_ab, -_ca));
}

bool Triangle::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
	// compute the Dot product (cosine of the angle) between the normal and the ray direction
	const float dotDirNrm = Dot(Normalize(r.GetDirection()), _n);
	rec.mat = _mat;
	
	// check triangle not being perpendicular to ray
	if (dotDirNrm != 0)
	{
		const float t = Dot(_a - r.GetOrigin(), _n) / dotDirNrm;
		
		// evalute the intersection point
		const Vec3 p = r.GetOrigin() + Normalize(r.GetDirection()) * t;
		
		// vectors to intersection points
		const Vec3 vecAP = _a - p;
		const Vec3 vecBP = _b - p;
		const Vec3 vecCP = _c - p;
		
		// normals between triangle edges and vectors to int. points
		const Vec3 crsAB_AP = Cross(_ab, vecAP);
		const Vec3 crsBC_BP = Cross(_bc, vecBP);
		const Vec3 crsCA_CP = Cross(_ca, vecCP);
		
		// Dot products for checking intersection point position
		const float dot1 = Dot(crsAB_AP, crsBC_BP);
		const float dot2 = Dot(crsBC_BP, crsCA_CP);
		const float dot3 = Dot(crsCA_CP, crsAB_AP);
		
		if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
		{
			if (t > t_min && t < t_max)
			{
				rec.t = t;
				rec.p = p;
				rec.n = _n;
				return true;
			}
		}
	}
	return false;
}
