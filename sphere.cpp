//
//  sphere.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "sphere.hpp"

bool Sphere::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
	const Vec3 oc = r.GetOrigin() - _center;
	const float a = Dot(r.GetDirection(), r.GetDirection());
	const float b = 2.0 * Dot(oc, r.GetDirection());
	const float c = Dot(oc, oc) - _radius * _radius;
	const float discriminant = b * b - 4 * a * c;
	rec.mat = _mat;
	if (discriminant > 0)
	{
		float t = 0;
		// evaluate first root
		t = ( -b - sqrt(discriminant) ) / (2 * a);
		if (t > t_min && t < t_max)
		{
			rec.t = t;
			rec.p = r.PointAtParameter(t);
			rec.n = (rec.p - _center) / _radius;
			return true;
		}

		// evalute second root
		t = ( -b + sqrt(discriminant) ) / (2 * a);
		if (t > t_min && t < t_max)
		{
			rec.t = t;
			rec.p = r.PointAtParameter(t);
			rec.n = (rec.p - _center) / _radius;
			return true;
		}
	}

	return false;
}


