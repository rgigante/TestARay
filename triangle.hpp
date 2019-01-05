//
//  triangle.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef triangle_hpp
#define triangle_hpp

#include "hitable.hpp"

class Triangle: public Hitable
{
public:
	Triangle(){}
	Triangle(Vec3 a, Vec3 b, Vec3 c, Material* m);
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	
private:
	Vec3 _a, _b, _c;
	Vec3 _ab, _bc, _ca, _n;
	Material* _mat;
};

#endif /* triangle_hpp */
