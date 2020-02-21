//
//  rectangle.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 18/02/2020.
//

#include "rectangle.hpp"

Rectangle::Rectangle(char const * name, float width, float height, Vec3 center, Vec3 normal, Material const * m)
{
	_w = width;
	_h = height;
	_c = center;
	_n = normal;
	
	// build the rectangle in the XY plane
	Vec3 pointA = Vec3(_c[0] + _w*0.5, _c[1] + _h*0.5, _c[2]);
	Vec3 pointB = Vec3(_c[0] - _w*0.5, _c[1] - _h*0.5, _c[2]);
	
	
	
	SetName(name);
	SetMaterial(m);
}

bool Rectangle::HitPrimitive (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	return false;
}

