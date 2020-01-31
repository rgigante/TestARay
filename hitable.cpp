//
//  hitable.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "hitable.hpp"

#ifdef NEW_HITABLE
bool Hitable::InitTransformation()
{
	// create global trf matrixes
	for (int i = 0; i < _mtrs.size(); ++i)
	{
		_gm = _gm * _mtrs[i];
		_invmtrs.push_back(_mtrs[i].GetInverse());
	}
	_gim = _gm.GetInverse();
	
	return true;
}


bool Hitable::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay /*= false*/)
{
	// allocate a temp ray  to be transformed based on hitable global transformation
	Ray ray(r);
	
	// update origin and direction of the ray
	ray.SetDirection((_gim.Get3x3() * r.GetDirection()));
	ray.SetOrigin(_gim * r.GetOrigin());
	
	if (debugRay) std::cout << "\t\t\t(instance intersection)\n"<<
		"\t\t\t- oldray:"<< r << "\n"<<
		"\t\t\t- newray:"<< ray <<"\n";
	
	
	// allocate a temp bool to store the hit case
	bool hitDetected = false;
	
	// If the hitable is "visible" in the scene, try to pierce it
	if (IsVisible())
		hitDetected = Hit2(ray, t_min, t_max, rec, debugRay);
	
	// tranform back points and normals based on hitable global transformation
	rec.p = _gm * rec.p;
	rec.n = (_gim.Get3x3().Transpose() * rec.n).GetNormalized();
	
	// return the hit case
	return (hitDetected);
}
#endif
