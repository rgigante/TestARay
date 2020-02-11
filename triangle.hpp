//
//  triangle.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef triangle_hpp
#define triangle_hpp

#include "matrix.hpp"
#include "hitable.hpp"
#include "materials.hpp"

class Triangle: public Hitable
{
public:
	//	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false);
	Triangle(char const * name, Vec3 a, Vec3 b, Vec3 c, Material const * m, bool isTriMesh = false) : _a(a), _b(b), _c(c), _isTriMesh(isTriMesh) { SetName(name); SetMaterial(m); }
	~Triangle(){}
	
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
private:
	Vec3 _a = Vec3(0.0), _b = Vec3(0.0), _c = Vec3(0.0);
	Vec3 _ab = Vec3(0.0), _bc = Vec3(0.0), _ca = Vec3(0.0);
	Vec3 _n = Vec3(0.0);
	bool _isTriMesh = false;
};

#endif /* triangle_hpp */
