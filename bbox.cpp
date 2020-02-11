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
	_a = _c + _r;
	_b = _c - _r;
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
	
	//check ray dir
	const float invRayDirX = abs(r.GetDirection().x()) >= _dirThreshold ? 1 /r.GetDirection().x() : _invDirThreshold;
	const float invRayDirY = abs(r.GetDirection().y()) >= _dirThreshold ? 1 /r.GetDirection().y() : _invDirThreshold;
	const float invRayDirZ = abs(r.GetDirection().z()) >= _dirThreshold ? 1 /r.GetDirection().z() : _invDirThreshold;
	
	Vec3 bRpos = _b - rpos;
	// check that ray position and bounding box don't overlap on each axis
	// if overlap make the term of the delta slightly positive
	bRpos[0] = abs(bRpos[0]) < _posThreshold ? _posThreshold : bRpos[0];
	bRpos[1] = abs(bRpos[1]) < _posThreshold ? _posThreshold : bRpos[1];
	bRpos[2] = abs(bRpos[2]) < _posThreshold ? _posThreshold : bRpos[2];
	assert(abs(bRpos[0]) >= _posThreshold && abs(bRpos[1]) >= _posThreshold && abs(bRpos[2]) >= _posThreshold );
	
	Vec3 aRpos = _a - rpos;
	// check that ray position and bounding box don't overlap on each axis
	// if overlap make the term of the delta slightly negative
	aRpos[0] = abs(aRpos[0]) < _posThreshold ? -_posThreshold : aRpos[0];
	aRpos[1] = abs(aRpos[1]) < _posThreshold ? -_posThreshold : aRpos[1];
	aRpos[2] = abs(aRpos[2]) < _posThreshold ? -_posThreshold : aRpos[2];
	assert(abs(aRpos[0]) >= _posThreshold && abs(aRpos[1]) >= _posThreshold && abs(aRpos[2]) >= _posThreshold );
	
	float smallest_tmax = 0, largest_tmin = 0;
	
	// calculate intersections for X
	float val_b = bRpos.x() * invRayDirX;
	float val_a = aRpos.x() * invRayDirX;
	// identify min and max values
	const float tminX = val_b < val_a ? val_b : val_a;
	const float tmaxX = val_b >= val_a ? val_b : val_a;
	
	// calculate intersections for Y
	val_b = bRpos.y() * invRayDirY;
	val_a = aRpos.y() * invRayDirY;
	// identify min and max values
	const float tminY = val_b < val_a ? val_b : val_a;
	const float tmaxY = val_b >= val_a ? val_b : val_a;
	
	// calculate intersections for Z
	val_b = bRpos.z() * invRayDirZ;
	val_a = aRpos.z() * invRayDirZ;
	// identify min and max values
	const float tminZ = val_b < val_a ? val_b : val_a;
	const float tmaxZ = val_b >= val_a ? val_b : val_a;
	
	// identify
	if (tminX >= tminY && tminX >= tminZ)
		largest_tmin = tminX;
	else if (tminY >= tminX && tminY >= tminZ)
		largest_tmin = tminY;
	else // if (tminZ >= tminX && tminZ >= tminY)
		largest_tmin = tminZ;
	
	if (tmaxX <= tmaxY && tmaxX <= tmaxZ)
		smallest_tmax = tmaxX;
	else if (tmaxY <= tmaxX && tmaxY <= tmaxZ)
		smallest_tmax = tmaxY;
	else // if (tmaxZ <= tmaxX && tmaxZ <= tmaxY)
		smallest_tmax = tmaxZ;
	
	
	if (debugRay) std::cout << "\t\t\t\t- a/b: "<< _a << "/" << _b << "\n"
		<< "\t\t\t\t- c/r: "<< _c << "/" << _r << "\n"
		<< "\t\t\t\t- tmin(s):" << tminX <<", " << tminY <<", " << tminZ << "\n"
		<< "\t\t\t\t- tmax(s):" << tmaxX <<", " << tmaxY <<", " << tmaxZ << "\n"
		<< "\t\t\t\t- smaller_tmax:" << smallest_tmax <<" / larger_tmin:" << largest_tmin << "\n";
	
	if (smallest_tmax >= largest_tmin && largest_tmin > t_min && largest_tmin < t_max)
			return true;
	
	return false;
}
