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
	Sphere(char const* name, Vec3 cen, float r, Material const * mat, bool visible = true) : _center(cen), _radius(r) { SetName(name); SetVisible(visible); SetMaterial(mat); }
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	bool SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	
private:
	Vec3 _center;
	float _radius;
};

#endif /* sphere_hpp */
