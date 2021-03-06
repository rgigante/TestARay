//
//  camera.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#include "camera.hpp"

Camera::Camera(const Vec3& from, const Vec3& to, const Vec3& up, float vfov, float aperture, float focusDistance, int xRes, int yRes) : _eyePos(from), _vFOV(vfov), _aperture(aperture), _focusDist(focusDistance), _xRes(xRes), _yRes(yRes)
{
	_ratio = float(_xRes) / float(_yRes);
	const float theta = _vFOV * M_PI / 180;
	_filmHeight = 2 * tan((theta / 2));
	_filmWidth = _filmHeight * _ratio;
	
	_w = (from - to).GetNormalized();
	_u = Cross(up, _w).GetNormalized();
	_v = Cross(_w, _u);
	
	
	_lowerLeftCorner = _eyePos - _focusDist * _filmWidth * 0.5 * _u - _focusDist * _filmHeight * 0.5 * _v - _focusDist * _w;
	_hVec = _focusDist * _filmWidth * _u;
	_vVec = _focusDist * _filmHeight * _v;
}

Ray Camera::CreateRay(float u, float v)
{
	if (_aperture > 0)
	{
		const Vec3 rd = _aperture * RandomPointOnDisk();
		const Vec3 offset = _u * rd[0] + _v * rd[1];
		const Vec3 eyeDir = (_lowerLeftCorner + _hVec * u + _vVec * v - _eyePos - offset).GetNormalized();
		const Vec3 eyePos = _eyePos + offset;
		return Ray(eyePos, eyeDir, u, v);
	}
	else
	{
		const Vec3 eyeDir = (_lowerLeftCorner + _hVec * u + _vVec * v - _eyePos).GetNormalized();
		return Ray(_eyePos, eyeDir);
	}
}
