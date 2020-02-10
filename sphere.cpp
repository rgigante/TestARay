//
//  sphere.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "sphere.hpp"
#include "matrix.hpp"

bool Sphere::SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return false;
	else if (discr == 0)
		x0 = x1 = - 0.5 * b / a;
	else
	{
		float q = (b > 0) ?	-0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);
	
	return true;
}

bool Sphere::Hit2(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay  /*= false*/)
{
	Ray ray(r);
	
	const Vec3 rpos = ray.GetOrigin();
	const Vec3 rdir = ray.GetDirection();
	const Vec3 oc = rpos - _center;

	rec.mat = GetMaterial();
	
	const float a = Dot(rdir, rdir);
	const float b = 2.0 * Dot(oc, rdir);
	const float c = Dot(oc, oc) - _radius * _radius;
	float t0, t1;
	if (SolveQuadratic(a, b, c, t0, t1))
	{
		if (t1 < t0)
			std::swap(t0, t1);
		
		rec.t = t0;
		rec.p = ray.PointAtParameter(t0);
		rec.n = (rec.p - _center) / _radius;
		
		if (rec.t > t_min && rec.t < t_max)
			return true;
	}

	return false;
}



