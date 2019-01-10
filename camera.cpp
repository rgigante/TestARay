//
//  camera.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "camera.hpp"

Camera::Camera(const Vec3& pos, float vfov, int xRes, int yRes) : _eyePos(pos), _vFOV(vfov), _xRes(xRes), _yRes(yRes)
{
	_ratio = float(_xRes) / float(_yRes);
	_filmHeight = tan((_vFOV * M_PI / 180));
	_filmWidth = _filmHeight * _ratio;
	_lowerLeftCorner = Vec3(-_filmWidth * 0.5, -_filmHeight * 0.5, -1.0);
	_hVec = Vec3(_filmWidth, 0.0, 0.0);
	_vVec = Vec3(0.0, _filmHeight, 0.0);
}

Camera::Camera(const Vec3& from, const Vec3& to, const Vec3& up, float vfov, int xRes, int yRes) : _eyePos(from), _vFOV(vfov), _xRes(xRes), _yRes(yRes)
{
	_ratio = float(_xRes) / float(_yRes);
	_filmHeight = tan((_vFOV * M_PI / 180));
	_filmWidth = _filmHeight * _ratio;
	
	_w = (from - to).GetNormalized();
	_u = Cross(up, _w).GetNormalized();
	_v = Cross(_w, _u);
	

	_lowerLeftCorner = _eyePos - _filmWidth * 0.5 * _u -_filmHeight * 0.5 * _v - _w;
	_hVec = _filmWidth * _u;
	_vVec = _filmHeight * _v;
}

Ray Camera::CreateRay(float u, float v)
{
	Vec3 eyeDir = _lowerLeftCorner + _hVec * u + _vVec * v - _eyePos;
	return Ray(_eyePos, eyeDir.GetNormalized());
}
