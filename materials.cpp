//
//  materials.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "materials.hpp"

LambertianReflector::LambertianReflector(const Vec3& a) : _albedo(a){}

bool LambertianReflector::Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const
{
	const Vec3 rndDir = rec.n + RandomPointOnSphere();
	rScatter = Ray(rec.p, rndDir);
	attenuation = _albedo;
	return true;
}

MetalReflector::MetalReflector(const Vec3& a) : _albedo(a){}

bool MetalReflector::Scatter(const Ray &rHit, const HitRecord &rec, Vec3 &attenuation, Ray &rScatter) const
{
	const Vec3 rflDir = ReflectRay(rHit.GetDirection(), rec.n);
	rScatter = Ray(rec.p, rflDir);
	attenuation = _albedo;
	const float rSctDotN = Dot(rflDir, rec.n);
//	Vec3 A = Cross(rflDir, rec.n) - Cross(rec.n, -rHit.GetDirection());
	if (rSctDotN > 0)
		return true;
	
	return false;
	
}
