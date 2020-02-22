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
	virtual bool Emission(const Ray& rHIt, const HitRecord& rec, Vec3 & emission) const = 0;
	
	// name-related methods
	bool SetName(char const * name);
	char const * GetName();
	
	// materialID-related methods
	void SetMatID(unsigned long matID){ _matID = matID; return; };
	unsigned long GetMatID(){ return _matID;}
	
private:
	// the pointer to the string assigned to the hitable
	char const* _name = nullptr;
	// the index to the material;
	unsigned long _matID = 0;
};

class LambertianReflector : public Material
{
public:
	LambertianReflector(char const* name, const Vec3& a = Vec3(0.95), const Vec3& e = Vec3(0.0));
	~LambertianReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	bool Emission(const Ray& rHIt, const HitRecord& rec, Vec3 & emission) const;
	void SetAlbedo(const Vec3 & diffuseCol) { _albedo  = diffuseCol;}
	void SetEmission(const Vec3 & emissionCol) { _emission  = emissionCol;}
	
private:
	Vec3 _albedo = Vec3(0.0); // the color of the reflector
	Vec3 _emission = Vec3(0.0); // the color of the reflector
};

class MetalReflector : public Material
{
public:
	MetalReflector(char const* name, const Vec3& a = Vec3 (0.95), float r = 0, const Vec3& e = Vec3(0.0));
	~MetalReflector(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	bool Emission(const Ray& rHIt, const HitRecord& rec, Vec3 & emission) const ;
	void SetAlbedo(const Vec3 & diffuseCol) { _albedo  = diffuseCol;}
	void SetRoughness(const float & roughnessVal) { _roughness  = roughnessVal;}
	void SetEmission(const Vec3 & emissionCol) { _emission  = emissionCol;}
private:
	Vec3 _albedo = Vec3(0.0);
	float _roughness = 0.0;
	Vec3 _emission = Vec3(0.0); // the color of the reflector
};

class Dielectric : public Material
{
public:
	Dielectric(char const* name, float ri, const Vec3& a = Vec3(1.0), const Vec3& e = Vec3(0.0));
	~Dielectric(){};
	bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const;
	bool Emission(const Ray& rHIt, const HitRecord& rec, Vec3 & emission) const;
	void SetAbsorption(const Vec3 & absorptionCol) { _absorption  = absorptionCol;}
	void SetRefraction(const float & refrIdxVal) { _refrIndex = refrIdxVal;}
	void SetEmission(const Vec3 & emissionCol) { _emission  = emissionCol;}
private:
	float _refrIndex = 1.0;
	Vec3 _absorption = Vec3(0.0);
	Vec3 _emission = Vec3(0.0); // the color of the reflector
};

class DiffuseEmitter : public Material
{
public:
	DiffuseEmitter(char const* name, const Vec3 & e) : _emission(e) { SetName(name); }
	virtual bool Scatter(const Ray& rHit, const HitRecord& rec, Vec3& attenuation, Ray& rScatter) const { return false; }
	bool Emission(const Ray& rHit, const HitRecord& rec, Vec3& emission) const
	{

		float val = Dot(rHit.GetDirection(), rec.n);
		emission = _emission;
		if (_emission.Length() && val < 0)
			return true;
		else
			return false;
	}
	
private:
	Vec3 _emission = Vec3(0.0);
};

#endif /* materials_hpp */
