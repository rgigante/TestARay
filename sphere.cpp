//
//  sphere.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "sphere.hpp"
#include "matrix.hpp"

#define A

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay /*= false*/)
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

bool Sphere2::SolveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
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
#ifdef NEW_HITABLE
bool Sphere2::Hit2(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay  /*= false*/)
{
	Ray ray(r);
	
	const Vec3 rpos = ray.GetOrigin();
	const Vec3 rdir = ray.GetDirection();
	const Vec3 oc = rpos - _center;

	rec.mat = _mat;
	
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
#else
bool Sphere2::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay  /*= false*/)
{
	Ray ray = r;
	
	const Vec3 rpos = ray.GetOrigin();
	const Vec3 rdir = ray.GetDirection();
	const Vec3 oc = rpos - _center;
	
	rec.mat = _mat;
	
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

#endif



