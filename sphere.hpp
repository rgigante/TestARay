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
	Sphere(char const* name, Vec3 cen, float r, Material* m) : _center(cen), _radius(r), _mat(m) { SetName(name); }
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	
private:
	Vec3 _center;
	float _radius;
	Material* _mat;
};


class Sphere2: public Hitable
{
#ifdef NEW_HITABLE
public:
	~Sphere2(){}
	Sphere2(char const* name, Vec3 cen, float r, Material* m) : _center(cen), _radius(r), _mat(m) { SetName(name); }
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	bool SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	
private:
	Vec3 _center;
	float _radius;
	Material* _mat;
#else
public:
	~Sphere2(){}
	Sphere2(char const* name, Vec3 cen, float r, Material* m) : _center(cen), _radius(r), _mat(m) { SetName(name); }
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	bool SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1);
	
private:
	Vec3 _center;
	float _radius;
	Material* _mat;
#endif
};

#endif /* sphere_hpp */
