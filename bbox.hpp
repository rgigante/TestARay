//
//  bbox.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 11/02/2020.
//

#ifndef bbox_hpp
#define bbox_hpp
//
//#include "hitable.hpp"

#include "ray.hpp"

class BBox
{
public:
	BBox(){}
	BBox(Vec3 pt1, Vec3 pt2);
	bool HitBBox (const Ray& r, float t_min, float t_max, bool debugRay = false);
	
	Vec3 GetA(){ return _a; }
	Vec3 GetB(){ return _b; }
	Vec3 GetCenter() { return _c; }
	Vec3 GetRadius() { return _r; }
	void SetPoints(Vec3 pt1, Vec3 pt2);
	void AddPoint(Vec3 pt);
	void SetCenterAndRadius(Vec3 c, Vec3 r);
	bool IsValid() { return _a != _b; }
	
private:
	Vec3 _a = Vec3(0.0); // _a represents the further positive point
	Vec3 _b = Vec3(0.0); // _b represents the further negative point
	Vec3 _c = Vec3(0.0); // _c represents the box center
	Vec3 _r = Vec3(0.0); // _r represents the box radius
	
	const float _dirThreshold = 1e-6;
	const float _invDirThreshold = 1 / _dirThreshold;
	const float _posThreshold = 1e-3;
};


#endif /* bbox_hpp */
