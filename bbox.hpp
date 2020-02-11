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
	
private:
	Vec3 _a, _b; // _a represents the further positive point, _b represents the further negative point
	Vec3 _c, _r; // _c represents the box center, _r represents the box radius
};


#endif /* bbox_hpp */
