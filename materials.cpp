//
//  materials.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "materials.hpp"


bool Material::SetName(char const * name)
{
	_name = name;
	return (!name) ? false : true;
}

char const * Material::GetName()
{
	if (_name)
		return _name;
	return nullptr;
}

LambertianReflector::LambertianReflector (char const * name, const Vec3& a/* = Vec3 (0.95)*/, const Vec3& e /* = Vec3 (0.0)*/) : _albedo(a), _emission(e){ SetName(name); }

bool LambertianReflector::Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const
{
	const Vec3 rndDir = rec.n + RandomPointOnSphere();
	rScatter = Ray(rec.p, rndDir);
	attenuation = _albedo;
	return true;
}

bool LambertianReflector::Emission(const Ray& rHit, const HitRecord& rec, Vec3& emission) const
{
	emission = _emission;
	if (_emission.Length())
		return true;
	else
		return false;
}

MetalReflector::MetalReflector(char const * name, const Vec3& a /* = Vec3 (0.95)*/, float r /*= 0*/, const Vec3& e /* = Vec3 (0.0)*/) : _albedo(a), _roughness(r), _emission(e){ SetName(name); }

bool MetalReflector::Scatter(const Ray &rHit, const HitRecord &rec, Vec3 &attenuation, Ray &rScatter) const
{
	const Vec3 rflDir = ReflectRay(rHit.GetDirection(), rec.n);
	if (_roughness)
		rScatter = Ray(rec.p, rflDir + RandomPointOnSphere(_roughness));
	else
		rScatter = Ray(rec.p, rflDir);
	attenuation = _albedo;
	
	const float rflDirCheck = 1e-6;
	const float rflInOutDiffLength = (Cross(rflDir, rec.n) - Cross(rHit.GetDirection(), rec.n)).Length();
	
	if (rflInOutDiffLength > rflDirCheck)
		std::cout << "WARNING - Reflected ray correctness check failed [ diff:"<< rflInOutDiffLength <<"]\n"; // this should be almost zero
	
	if (Dot(rflDir, rec.n) > 0)
		return true;
	
	return false;
}

bool MetalReflector::Emission(const Ray& rHit, const HitRecord& rec, Vec3& emission) const
{
	emission = _emission;
	if (_emission.Length())
		return true;
	else
		return false;
}
Dielectric::Dielectric(char const * name, float ri, const Vec3& a, const Vec3& e) : _absorption(a), _emission(e), _refrIndex(ri){ SetName(name); }

bool Dielectric::Scatter(const Ray &rHit, const HitRecord &rec, Vec3 &attenuation, Ray &rScatter) const
{
	Vec3 adjustedNormal(0,0,0);
	Vec3 reflDir = ReflectRay(rHit.GetDirection(), rec.n);

	float niOverNt = 0.0, reflProb = 1.0, cosine = 0.0;

	attenuation = _absorption;
	if (Dot(rHit.GetDirection(), rec.n) > 0)
	{
		adjustedNormal = -rec.n;
		niOverNt = _refrIndex;
		cosine = _refrIndex * Dot(rHit.GetDirection(), rec.n) / rHit.GetDirection().Length();
	}
	else
	{
		adjustedNormal = rec.n;
		niOverNt = 1.0 /_refrIndex;
		cosine = -Dot(rHit.GetDirection(), rec.n) / rHit.GetDirection().Length();
	}

	bool isRefracted;
	const Vec3 refrDir = RefractRay(rHit.GetDirection(), adjustedNormal, niOverNt, isRefracted);
	if (isRefracted)
		reflProb = schlick(cosine, _refrIndex);

	if (drand48() < reflProb)
		rScatter = Ray(rec.p, reflDir);
	else
		rScatter = Ray(rec.p, refrDir);

	return true;
}

bool Dielectric::Emission(const Ray& rHit, const HitRecord& rec, Vec3& emission) const
{
	emission = _emission;
	if (_emission.Length())
		return true;
	else
		return false;
}
