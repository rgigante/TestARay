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
	
	// Virtual methods (override in derived classes)
	virtual bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const = 0;
	
	// name-related methods
	bool SetName(char const * name);
	char const * GetName();
	
	// materialID-related methods
	void SetMatID(unsigned long matID){ _matID = matID; return; };
	unsigned long GetMatID(){ return _matID;}
	
private:
	// the pointer to the string assigned to the hitable
	char const* _name;
	// the index to the material;
	unsigned long _matID = 0;
};

class LambertianReflector : public Material
{
public:
	LambertianReflector(char const* name, const Vec3& a);
	~LambertianReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	
private:
	Vec3 _albedo; // the color of the reflector
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
};

class Dielectric : public Material
{
public:
	Dielectric(char const* name, float ri);
	~Dielectric(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
private:
	float _refrIndex;
};

#endif /* materials_hpp */
