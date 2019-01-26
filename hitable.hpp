//
//  hitable.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"

class Material;
class Matrix;

struct HitRecord
{
	float t = 0; // the ray parameter at hit point
	Vec3 p = Vec3(0,0,0); // the position in space at hit point
	Vec3 n = Vec3(0,0,0); // the normal at hit point
	Material* mat = nullptr; // the material found at the hit point
};

class Hitable
{
public:
	virtual ~Hitable(){}
	virtual bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr) = 0;
};

#endif /* hitable_hpp */
