//
//  triangle.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "triangle.hpp"

bool Triangle::HitPrimitive(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	rec.mat = GetMaterial();
	
	const Vec3 rpos = r.GetOrigin();
	const Vec3 rdir = r.GetDirection();
	
	if (debugRay) std::cout << "\t\t\t\t- a:" << _a <<", b:" << _b <<", c:" << _c << "\n";
	
	Vec3 ab = _a - _b;
	Vec3 bc = _b - _c;
	Vec3 ca = _c - _a;
	Vec3 n = Cross(ab, -ca).GetNormalized();
	
	if (debugRay) std::cout << "\t\t\t\t- ab:" << ab <<", bc:" << bc <<", ca:" << ca << ", n:" << n << "\n";
	
	// compute the Dot product (cosine of the angle) between the normal and the ray direction
	const float dotDirNrm = Dot(rdir, n);
	
	if (debugRay) std::cout << "\t\t\t\t- dotDirNrm:" << dotDirNrm << "\n";
	
	// check triangle not being perpendicular to ray
	if (dotDirNrm != 0)
	{
		const float t = Dot(_a - rpos, n) / dotDirNrm;
		if (debugRay) std::cout << "\t\t\t\t- t:" << t << "\n";

		if (t > t_min && t < t_max)
		{
			// evalute the intersection point
			const Vec3 p = rpos + rdir * t;
			if (debugRay) std::cout << "\t\t\t\t- p:" << p << "\n";
			
			// vectors to intersection points
			const Vec3 vecAP = _a - p;
			const Vec3 vecBP = _b - p;
			const Vec3 vecCP = _c - p;
			if (debugRay) std::cout << "\t\t\t\t- vecAP:" << vecAP <<", vecBP:" << vecBP <<", vecCP:" << vecCP << "\n";
			
			// normals between triangle edges and vectors to int. points
			const Vec3 crsAB_AP = Cross(ab, vecAP);
			const Vec3 crsBC_BP = Cross(bc, vecBP);
			const Vec3 crsCA_CP = Cross(ca, vecCP);
			if (debugRay) std::cout << "\t\t\t\t- crsAB_AP:" << crsAB_AP <<", crsBC_BP:" << crsBC_BP <<", crsCA_CP:" << crsCA_CP << "\n";
			
			// Dot products for checking intersection point position
			const float dot1 = Dot(crsAB_AP, crsBC_BP);
			const float dot2 = Dot(crsBC_BP, crsCA_CP);
			const float dot3 = Dot(crsCA_CP, crsAB_AP);
			if (debugRay) std::cout << "\t\t\t\t- dot1:" << dot1 <<", dot2:" << dot2 <<", dot3:" << dot3 << "\n";
			
			if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
			{
				rec.t = t;
				rec.p = p;
				rec.n = n;
				return true;
			}
		}
	}
	return false;
}
