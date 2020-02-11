//
//  bbox.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 11/02/2020.
//

#include "bbox.hpp"


BBox::BBox(Vec3 pt1, Vec3 pt2)
{
	SetPoints(pt1, pt2);
}


void BBox::SetPoints(Vec3 pt1, Vec3 pt2)
{
	_a[0] = pt1.x() > pt2.x() ? pt1.x() : pt2.x();
	_b[0] = pt1.x() > pt2.x() ? pt2.x() : pt1.x();
	
	
	_a[1] = pt1.y() > pt2.y() ? pt1.y() : pt2.y();
	_b[1] = pt1.y() > pt2.y() ? pt2.y() : pt1.y();
	
	
	_a[2] = pt1.z() > pt2.z() ? pt1.z() : pt2.z();
	_b[2] = pt1.z() > pt2.z() ? pt2.z() : pt1.z();
	
	_c = (_a + _b) / 2;
	_r = _a - _c;
}

void BBox::SetCenterAndRadius(Vec3 c, Vec3 r)
{
	_c = c;
	_r = r;
	_a = _c + _r * 0.5;
	_b = _c - _r * 0.5;
}

void BBox::AddPoint(Vec3 pt)
{
	_a[0] = pt[0] > _a[0] ? pt[0] : _a[0];
	_b[0] = pt[0] < _b[0] ? pt[0] : _b[0];
	
	_a[1] = pt[1] > _a[1] ? pt[1] : _a[1];
	_b[1] = pt[1] < _b[1] ? pt[1] : _b[1];
	
	_a[2] = pt[2] > _a[2] ? pt[2] : _a[2];
	_b[2] = pt[2] < _b[2] ? pt[2] : _b[2];
	
	_c = (_a + _b) / 2;
	_r = _a - _c;
}

bool BBox::HitBBox (const Ray& r, float t_min, float t_max, bool debugRay /*= false*/)
{
	Ray ray(r);
	const Vec3 rpos = r.GetOrigin();
	const float invRayDirX = abs(r.GetDirection().x()) >= 1e-6 ? 1 /r.GetDirection().x() : 1e6;
	const float invRayDirY = abs(r.GetDirection().y()) >= 1e-6 ? 1 /r.GetDirection().y() : 1e6;
	const float invRayDirZ = abs(r.GetDirection().z()) >= 1e-6 ? 1 /r.GetDirection().z() : 1e6;
	const Vec3 bRpos = _b - rpos;
	const Vec3 aRpos = _a - rpos;
	
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
	
	if (smaller_tmax >= larger_tmin && larger_tmin > t_min && larger_tmin < t_max)
			return true;
	
	return false;
}
