//
//  box.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 10/02/2020.
//

#ifndef box_hpp
#define box_hpp

#include "hitable.hpp"
#include "materials.hpp"

class Box: public Hitable
{
public:
	~Box(){}
	Box(char const* name, const Vec3 & pt1, const Vec3 & pt2, Material const * mat, bool visible = true);
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
	Vec3 GetA(){ return _a; }
	Vec3 GetB(){ return _b; }
	Vec3 GetCenter() { return _c; }
	Vec3 GetRadius() { return _r; }
	void SetPoints(const Vec3 & pt1, const Vec3 & pt2);
	void SetCenterAndRadius(const Vec3 & c, const Vec3 & r);
	
private:
	void UpdateBoxCenterAndRadius();
	
private:
	Vec3 _a = Vec3(0.0); // _a represents the further positive point
	Vec3 _b = Vec3(0.0); // _b represents the further negative point
	Vec3 _c = Vec3(0.0); // _c represents the box center
	Vec3 _r = Vec3(0.0); // _r represents the box radius
	
	const float _dirThreshold = 1e-6;
	const float _invDirThreshold = 1 / _dirThreshold;
	const float _posThreshold = 1e-3;
};

#endif /* box_hpp */
