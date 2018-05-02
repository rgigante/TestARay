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

class ray
{
public:
	ray(){}
	ray(const vec3& a, const vec3& b){ A = a; B = b; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(const float t) const { return (A + B * t); }
	
	
public:
	vec3 A; // ray firing position
	vec3 B; // ray firing direction
};

#endif /* ray_hpp */
