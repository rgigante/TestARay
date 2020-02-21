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
	const float dotDirN = Dot(rdir, _n);
	
	if (abs(dotDirN) > 0)
	{
		const float t = Dot((_p - rpos), _n)/dotDirN;
		if (abs(t) < 1e-6)
			return false;
		const Vec3 pR = rpos + t * rdir;
		const Vec3 ppR = pR - _p;
		const float ppRd1 = Dot(ppR, _d1);
		const float ppRd2 = Dot(ppR, _d2);
		const bool cond1 = (ppRd1 > 0 && ppRd1 < _w);
		const bool cond2 = (ppRd2 > 0 && ppRd2 < _h);
		
		if (cond1 && cond2)
		{
			rec.p = pR;
			rec.n = _n;
			rec.t = t;
			return true;
		}
	}
	return false;
}

