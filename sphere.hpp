//
//  sphere.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef sphere_hpp
#define sphere_hpp

#include "hitable.hpp"
#include "materials.hpp"

class Sphere: public Hitable
{
public:
	~Sphere(){}
	Sphere(char const* name, Vec3 cen, float r, Material const * mat, bool visible = true);
	bool HitPrimitive (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	bool SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	
private:
	Vec3 _center = Vec3(0.0);
	float _radius = 0.0;
};

#endif /* sphere_hpp */
