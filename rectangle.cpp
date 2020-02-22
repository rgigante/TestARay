//
//  rectangle.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 18/02/2020.
//

#include "rectangle.hpp"

Rectangle::Rectangle(char const * name, const Vec3 p, const Vec3 d1, const Vec3 d2, Material const * m)
{
	_p = p;
	_d1 = d1;
	_w = _d1.Length();
	_d1.Normalize();
	
	_d2 = d2;
	_h = _d2.Length();
	_d2.Normalize();
	
	_n = Cross(_d1, _d2);
	
	SetName(name);
	SetMaterial(m);
}

bool Rectangle::HitPrimitive (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	rec.mat = GetMaterial();
	
	const Vec3 rpos = r.GetOrigin();
	const Vec3 rdir = r.GetDirection();
	const float dotDirNrm = Dot(rdir, _n);
	
	if (abs(dotDirNrm) > 0)
	{
		const float t = Dot((_p - rpos), _n)/dotDirNrm;
		if (t > t_min && t < t_max)
		{
			// evalute the intersection point
			const Vec3 p = rpos + t * rdir;
			
			// vector to intersection points
			const Vec3 pp = p - _p;
			
			// projection of intersection point vector of rectangle vectors
			const float ppd1 = Dot(pp, _d1);
			const float ppd2 = Dot(pp, _d2);
			
			// check of point hit being inside width and height
			const bool cond1 = (ppd1 > 0 && ppd1 < _w);
			const bool cond2 = (ppd2 > 0 && ppd2 < _h);
			
			if (cond1 && cond2)
			{
				rec.p = p;
				rec.n = _n;
				rec.t = t;
				return true;
			}
		}
	}
	return false;
}

