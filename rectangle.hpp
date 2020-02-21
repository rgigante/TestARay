//
//  rectangle.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 18/02/2020.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "hitable.hpp"
#include "materials.hpp"

class Rectangle: public Hitable
{
public:
	Rectangle(char const * name, const Vec3 p, const Vec3 d1, const Vec3 d2, Material const * m);
	
	~Rectangle(){}
	
	bool HitPrimitive (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
private:
	float _w = 0.0;
	float _h = 0.0;
	
	Vec3 _p = Vec3(0.0);
	Vec3 _n = Vec3(0.0);
	Vec3 _d1 = Vec3(0.0);
	Vec3 _d2 = Vec3(0.0);
};

#endif /* rectangle_hpp */
