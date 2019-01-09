//
//  materials.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef materials_hpp
#define materials_hpp

#include "hitable.hpp"
#include "utils.hpp"

class Material
{
public:
	virtual ~Material(){}
	virtual bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const = 0;
};

class LambertianReflector : public Material
{
public:
	LambertianReflector(const Vec3& a);
	~LambertianReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	
private:
	Vec3 _albedo; // the color of the reflector
};

class MetalReflector : public Material
{
public:
	MetalReflector(const Vec3& a, float r = 0);
	~MetalReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
private:
	Vec3 _albedo;
	float _roughness;
};

class Dielectric : public Material
{
public:
	Dielectric(float ri);
	~Dielectric(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
private:
	float _refrIndex;
};

#endif /* materials_hpp */
