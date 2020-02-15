//
//  environment.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 15/02/2020.
//

#ifndef environment_hpp
#define environment_hpp

#include "ray.hpp"
#include "utils.hpp"

class Environment
{
public:
	virtual ~Environment(){}
	
	// Virtual methods (override in derived classes)
	virtual Vec3 Col(const Ray& rHit) const = 0;
	
	// name-related methods
	bool SetName(char const * name);
	char const * GetName();
	
private:
	// the pointer to the string assigned to the hitable
	char const* _name = nullptr;
};

class Gradient : public Environment
{
public:
	Gradient(char const* name, const Vec3& col1 = Vec3(0.95), const Vec3& col2 = Vec3(0.0), float ratio = 0.5) : _c1(col1), _c2(col2), _r(ratio) { SetName(name); }
	~Gradient(){};
	Vec3 Col(const Ray &rHit) const;
	
private:
	Vec3 _c1 = Vec3(0.0); // the color of the reflector
	Vec3 _c2 = Vec3(0.0); // the color of the reflector
	float _r = 0.5;
};
#endif /* environment_hpp */
