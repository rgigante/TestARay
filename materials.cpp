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
	
	const float rflDirCheck = 1e-6;
	if (((Cross(rflDir, rec.n) - Cross(rec.n, -rHit.GetDirection())).Length()) > rflDirCheck)
		std::cout << "WARNING - Reflected ray correctness check failed ["<< rflDirCheck <<"]\n"; // this should be almost zero
	if (Dot(rflDir, rec.n) > 0)
		return true;
	
	return false;
	
}
