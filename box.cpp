//
//  box.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 10/02/2020.
//

#include "box.hpp"

Box::Box(char const* name, Vec3 pt1, Vec3 pt2, Material const * mat, bool visible /*= true*/)
{
	SetPoints(pt1, pt2);
	SetName(name);
	SetVisible(visible);
	SetMaterial(mat);
}


void Box::SetPoints(Vec3 pt1, Vec3 pt2)
{
	if (pt1.x() > pt2.x())
	{
		_a[0] = pt1.x();
		_b[0] = pt2.x();
	}
	else
	{
		_a[0] = pt2.x();
		_b[0] = pt1.x();
	}
	
	if (pt1.y() > pt2.y())
	{
		_a[1] = pt1.y();
		_b[1] = pt2.y();
	}
	else
	{
		_a[1] = pt2.y();
		_b[1] = pt1.y();
	}
	
	if (pt1.z() > pt2.z())
	{
		_a[2] = pt1.z();
		_b[2] = pt2.z();
	}
	else
	{
		_a[2] = pt2.z();
		_b[2] = pt1.z();
	}
	
	_c = (_a + _b) / 2;
	_r = _a - _c;
}

bool Box::Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	Ray ray(r);
	const Vec3 rpos = r.GetOrigin();
	const float invRayDirX = abs(r.GetDirection().x()) >= 1e-6 ? 1 /r.GetDirection().x() : 1e6;
	const float invRayDirY = abs(r.GetDirection().y()) >= 1e-6 ? 1 /r.GetDirection().y() : 1e6;
	const float invRayDirZ = abs(r.GetDirection().z()) >= 1e-6 ? 1 /r.GetDirection().z() : 1e6;
	const Vec3 bRpos = _b - rpos;
	const Vec3 aRpos = _a - rpos;
	
	rec.mat = GetMaterial();
	
	float smaller_tmax = 0, larger_tmin = 0;

	float val_b = bRpos.x() * invRayDirX;
	float val_a = aRpos.x() * invRayDirX;
	const float tminX = val_b < val_a ? val_b : val_a;
	const float tmaxX = val_b >= val_a ? val_b : val_a;
	
	val_b = bRpos.y() * invRayDirY;
	val_a = aRpos.y() * invRayDirY;
	const float tminY = val_b < val_a ? val_b : val_a;
	const float tmaxY = val_b >= val_a ? val_b : val_a;
	
	val_b = bRpos.z() * invRayDirZ;
	val_a = aRpos.z() * invRayDirZ;
	const float tminZ = val_b < val_a ? val_b : val_a;
	const float tmaxZ = val_b >= val_a ? val_b : val_a;

	if (tminX >= tminY && tminX >= tminZ)
		larger_tmin = tminX;
	else if (tminY >= tminX && tminY >= tminZ)
		larger_tmin = tminY;
	else // if (tminZ >= tminX && tminZ >= tminY)
		larger_tmin = tminZ;
	
	if (tmaxX <= tmaxY && tmaxX <= tmaxZ)
		smaller_tmax = tmaxX;
	else if (tmaxY <= tmaxX && tmaxY <= tmaxZ)
		smaller_tmax = tmaxY;
	else // if (tmaxZ <= tmaxX && tmaxZ <= tmaxY)
		smaller_tmax = tmaxZ;
	
	
	if (debugRay) std::cout << "\t\t\t\t- a/b: "<< _a << "/" << _b << "\n"
		<< "\t\t\t\t- c/r: "<< _c << "/" << _r << "\n"
		<< "\t\t\t\t- tmin(s):" << tminX <<", " << tminY <<", " << tminZ << "\n"
		<< "\t\t\t\t- tmax(s):" << tmaxX <<", " << tmaxY <<", " << tmaxZ << "\n"
		<< "\t\t\t\t- smaller_tmax:" << smaller_tmax <<" / larger_tmin:" << larger_tmin << "\n";

	if (smaller_tmax >= larger_tmin)
	{
		rec.t = larger_tmin;
		rec.p = ray.PointAtParameter(larger_tmin);
		if (abs(rec.p.z() - _a.z()) < 1e-6)
			rec.n = Vec3(0,0,1);
		else if (abs(rec.p.z() - _b.z()) < 1e-6)
			rec.n = Vec3(0,0,-1);
		else if (abs(rec.p.y() - _a.y()) < 1e-6)
			rec.n = Vec3(0,1,0);
		else if (abs(rec.p.y() - _b.y()) < 1e-6)
			rec.n = Vec3(0,-1,0);
		else if (abs(rec.p.x() - _a.x()) < 1e-6)
			rec.n = Vec3(1,0,0);
		else //if (abs(rec.p.x() - _b.x()) < 1e-6)
			rec.n = Vec3(-1,0,0);
		
		if (rec.t > t_min && rec.t < t_max)
			return true;
	}
	
	return false;
}
