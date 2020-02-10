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
	Box(char const* name, Vec3 pt1, Vec3 pt2, Material const * mat, bool visible = true);
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	Vec3 GetA(){ return _a; }
	Vec3 GetB(){ return _b; }
	Vec3 GetCenter() { return _c; }
	Vec3 GetRadius() { return _r; }
	void SetPoints(Vec3 pt1, Vec3 pt2);
	
private:
	Vec3 _a, _b; // _a represents the further positive coordinate, _b represents the further negative coordinate
	Vec3 _c, _r; // _c represents the box center, _r represents the box radius
};

#endif /* box_hpp */
