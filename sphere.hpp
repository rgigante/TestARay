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
	Sphere(){}
	~Sphere();
	Sphere(char const* name, Vec3 cen, float r, Material* m) : _name(name), _center(cen), _radius(r), _mat(m) {};
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance = false) const;
	
private:
	Vec3 _center;
	float _radius;
	Material* _mat;
	char const* _name;
};

#endif /* sphere_hpp */
