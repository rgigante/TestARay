//
//  ray.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 27/04/2018.
//
//
//	First committed on github on 02.05.2018

#ifndef ray_hpp
#define ray_hpp

#include "vec3.hpp"

class Ray
{
public:
	Ray(){}
	Ray(const Vec3& a, const Vec3& b){ A = a; B = b; }
	
	// retrieve the origin of a ray
	Vec3 GetOrigin() const { return A; }
	// retrieve the direction of a ray
	Vec3 GetDirection() const { return B; }
	// set the origin of a ray
	void SetOrigin(const Vec3& pos) { A = pos; }
	// set the direction of a ray
	void SetDirection(const Vec3& dir) { B = dir; }
	// given a parameter for a certain ray, return the position in space at parameter
	Vec3 PointAtParameter(const float t) const { return (A + B * t); }
	
	
private:
	Vec3 A; // ray firing position
	Vec3 B; // ray firing direction
};

#endif /* ray_hpp */
