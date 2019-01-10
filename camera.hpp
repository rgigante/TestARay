//
//  camera.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef camera_hpp
#define camera_hpp

#include "ray.hpp"

class Camera
{
public:
	Camera(const Vec3& from, const Vec3& to, const Vec3& up, float vfov, float aperture, float focusDistance, int xRes, int yRes);
	Ray CreateRay(float u, float v);
	int GetXRes(){ return _xRes; }
	int GetYRes(){ return _yRes; }
	
private:
	Vec3 _eyePos, _u, _v, _w;
	Vec3 _lowerLeftCorner, _hVec, _vVec;
	float _ratio, _filmWidth, _filmHeight, _vFOV, _aperture, _focusDist;
	int _xRes, _yRes;
};

#endif /* camera_hpp */
