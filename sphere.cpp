//
//  sphere.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "sphere.hpp"
#include "matrix.hpp"

#define A

Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm)
{
	Ray ray = r;
	Vec3 rpos = ray.GetOrigin();
	Vec3 rdir = ray.GetDirection();
	Vec3 oc = rpos - _center;
	if (gm)
	{
#ifdef A
		ray = Ray(gm->GetInverse() * r.GetOrigin(), (gm->GetInverse().Get3x3() * r.GetDirection()).GetNormalized());
		rpos = ray.GetOrigin();
		rdir = ray.GetDirection();
		oc = rpos - _center;
#else
		oc = rpos - (*gm *  _center);
#endif
	}
	
	const float a = Dot(rdir, rdir);
	const float b = 2.0 * Dot(oc, rdir);
	const float c = Dot(oc, oc) - _radius * _radius;
	const float discriminant = b * b - 4 * a * c;
	rec.mat = _mat;
	if (discriminant > 0)
	{
		float t = 0;
		// evaluate first root
		t = ( -b - sqrt(discriminant) ) / (2 * a);

		rec.t = t;
		rec.p = ray.PointAtParameter(t);
		rec.n = (rec.p - _center) / _radius;
		if(gm)
		{
#ifdef A
			rec.p = *gm * ray.PointAtParameter(t);
			rec.n = (gm->Get3x3() * ((ray.PointAtParameter(t) - _center) / _radius)).GetNormalized();
			float valA = r.ParameterAtPoint(rec.p);
			float valB = ray.ParameterAtPoint(rec.p);
			rec.t = r.ParameterAtPoint(rec.p);
#else
			rec.p = ray.PointAtParameter(t);
			rec.n = (ray.PointAtParameter(t)   - (*gm * _center)) / _radius;
#endif
		}
		
//		if (t > t_min && t < t_max)
		if (rec.t > t_min && rec.t < t_max)
		{
			return true;
		}

		// evalute second root
		t = ( -b + sqrt(discriminant) ) / (2 * a);
		rec.t = t;
		rec.p =  ray.PointAtParameter(t);
		rec.n = (rec.p - _center) / _radius;
		if(gm)
		{
#ifdef A
			rec.p = *gm  * ray.PointAtParameter(t);
			rec.n = (gm->Get3x3() * ((ray.PointAtParameter(t)   - _center) / _radius)).GetNormalized();
			float valA = r.ParameterAtPoint(rec.p);
			float valB = ray.ParameterAtPoint(rec.p);
			rec.t = r.ParameterAtPoint(rec.p);
#else
			rec.p = ray.PointAtParameter(t);
			rec.n = (ray.PointAtParameter(t)   - (*gm * _center)) / _radius;
#endif
		}
		
//		if (t > t_min && t < t_max)
		if (rec.t > t_min && rec.t < t_max)
		{

			return true;
		}
	}

	return false;
}




