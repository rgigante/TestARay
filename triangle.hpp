//
//  triangle.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef triangle_hpp
#define triangle_hpp

#include "transformation.hpp"
#include "hitable.hpp"
#include "materials.hpp"

class Triangle: public Hitable
{
public:
//	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false);
	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false, Matrix gm = Matrix(), Matrix gim = Matrix());
	~Triangle();
	bool SetName(char const* name){ _name = name; return (!name) ? false : true; };
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance = false) const;
	
private:
	Vec3 _a, _b, _c;
	Vec3 _ab, _bc, _ca, _n;
	Material* _mat;
	char const* _name;
	Matrix _gm, _gim;
	bool _isTriMesh;
};

#endif /* triangle_hpp */
