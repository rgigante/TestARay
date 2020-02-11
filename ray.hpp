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
	Ray(const Ray& r):_pos(r._pos), _dir(r._dir){}
	Ray(const Vec3& pos, const Vec3& dir):_pos(pos), _dir(dir){}
	Ray(const Vec3& pos, const Vec3& dir, const float u, const float v):_pos(pos), _dir(dir), _u(u), _v(v){}
	
	// retrieve the origin of a ray
	Vec3 GetOrigin() const { return _pos; }
	// retrieve the direction of a ray
	Vec3 GetDirection() const { return _dir; }
	
	Vec3 GetUV() const { return Vec3(_u, _v, 0); }
	// set the origin of a ray
	void SetOrigin(const Vec3& pos) { _pos = pos; }
	// set the direction of a ray
	void SetDirection(const Vec3& dir) { _dir = dir; }
	// given a parameter for a certain ray, return the position in space at parameter
	Vec3 PointAtParameter(const float t) const { return (_pos + _dir * t); }
	float ParameterAtPoint(const Vec3 pnt) const {
//		assert ((pnt[0] - _pos[0])/_dir[0] == (pnt[1] - _pos[1])/_dir[1] && (pnt[1] - _pos[1])/_dir[1] == (pnt[2] - _pos[2])/_dir[2]);
		return (pnt[0] - _pos[0])/_dir[0]; }
	
	friend std::ostream& operator<<(std::ostream &os, const Ray& r)
	{
		std::cout << std::fixed;
		os << "p [" << r.GetOrigin() << "] / d[" << r.GetDirection() << "]";
		return os;
	}
	
private:
	Vec3 _pos = Vec3(0.0); // ray firing position
	Vec3 _dir = Vec3(0.0); // ray firing direction
	float _u = 0.0, _v = 0.0;
};

#endif /* ray_hpp */
