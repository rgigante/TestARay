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
	LambertianReflector(char const* name, const Vec3& a);
	~LambertianReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	
private:
	Vec3 _albedo; // the color of the reflector
	char const* _name;
};

class MetalReflector : public Material
{
public:
	MetalReflector(char const* name, const Vec3& a, float r = 0);
	~MetalReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
private:
	Vec3 _albedo;
	float _roughness;
	char const* _name;
};

class Dielectric : public Material
{
public:
	Dielectric(char const* name, float ri);
	~Dielectric(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
private:
	float _refrIndex;
	char const* _name;
};

#endif /* materials_hpp */
