//
//  camera.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "camera.hpp"

Camera::Camera(const Vec3& pos, float filmWidth, int xRes, int yRes) : _eyePos(pos), _filmWidth(filmWidth), _xRes(xRes), _yRes(yRes)
{
	_ratio = float(_xRes) / float(_yRes);
	_filmHeight = _filmWidth / _ratio;
	_lowerLeftCorner = Vec3(-filmWidth / 2, -_filmHeight / 2, -1.0);
	_hVec = Vec3(_filmWidth, 0.0, 0.0);
	_vVec = Vec3(0.0, _filmHeight, 0.0);
}

Ray Camera::GetRay(float u, float v)
{
	const Ray r (_eyePos, _lowerLeftCorner + _hVec * u + _vVec * v);
	return r;
}
