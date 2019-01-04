//
//  hitable.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"

struct HitRecord
{
	float t; // the ray parameter at hit point
	Vec3 p; // the position in space at hit point
	Vec3 n; // the normal at hit point
};

class Hitable
{
public:
	virtual bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

#endif /* hitable_hpp */
