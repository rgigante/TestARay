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
	Vec3 _eyePos = Vec3(0.0), _u = Vec3(0.0), _v = Vec3(0.0), _w = Vec3(0.0);
	Vec3 _lowerLeftCorner = Vec3(0.0), _hVec = Vec3(0.0), _vVec = Vec3(0.0);
	float _ratio = 0.0, _filmWidth = 0.0, _filmHeight = 0.0, _vFOV = 0.0, _aperture = 0.0, _focusDist = 0.0;
	int _xRes = 0, _yRes = 0;
};

#endif /* camera_hpp */
