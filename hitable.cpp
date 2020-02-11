//
//  hitable.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "hitable.hpp"

bool Hitable::InitTransformation()
{
	// compose the transformations
	for (int i = 0; i < _mtrs.size(); ++i)
	{
		// multiply the matrixes found in the transformation stack
		_gm = _gm * _mtrs[i];
	}
	_gim = _gm.GetInverse();
	
	return true;
}


bool Hitable::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
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
	bool aabbHitDetected = false;
	
#ifdef USE_BBOX
	// If the hitable is "visible" in the scene, try to pierce it
	if (IsVisible())
	{
		if (_bbox.IsValid())
		{
			aabbHitDetected = _bbox.HitBBox(ray, t_min, t_max, debugRay);
			if (aabbHitDetected)
			{
				hitDetected = Hit2(ray, t_min, t_max, rec, debugRay);
			
				// tranform back points and normals based on hitable global transformation
				rec.p = _gm * rec.p;
				rec.n = (_gim.Get3x3().Transpose() * rec.n).GetNormalized();
				rec.objID = _objID;
			}
		}
		else
		{
			hitDetected = Hit2(ray, t_min, t_max, rec, debugRay);
			
			// tranform back points and normals based on hitable global transformation
			rec.p = _gm * rec.p;
			rec.n = (_gim.Get3x3().Transpose() * rec.n).GetNormalized();
			rec.objID = _objID;
		}
	}
#else
	if (IsVisible())
	{
		hitDetected = Hit2(ray, t_min, t_max, rec, debugRay);
		
		// tranform back points and normals based on hitable global transformation
		rec.p = _gm * rec.p;
		rec.n = (_gim.Get3x3().Transpose() * rec.n).GetNormalized();
		rec.objID = _objID;
	}
#endif
	
	// return the hit case
	return (hitDetected);
}
