//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"
//#define RAY_NOSCALE

bool HitableInstance::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay /*= false*/)
{
	Ray ray(r);
#ifdef RAY_NOSCALE
	ray.SetDirection(((_gim.Get3x3() * r.GetDirection()) * _gm.GetScaleNU()).GetNormalized());
	ray.SetOrigin(_gim * r.GetOrigin());
#else
	ray.SetDirection((_gim.Get3x3() * r.GetDirection()));
	ray.SetOrigin(_gim * r.GetOrigin());
#endif
	
	if (debugRay) std::cout << "\t\t\t(instance intersection)\n"<<
		"\t\t\t- oldray:"<< r << "\n"<<
		"\t\t\t- newray:"<< ray <<"\n";
	bool hit = _obj->Hit(ray, t_min, t_max, rec, nullptr, debugRay);
	float tAtR = r.ParameterAtPoint(rec.p);
	float tAtRay = ray.ParameterAtPoint(rec.p);
	rec.p = _gm * rec.p;
	rec.n = (_gm.Get3x3() * rec.n).GetNormalized();
	if (debugRay && hit) std::cout <<
		"\t\t\t- tAtOldRay"<< tAtR <<"\n"<<
		"\t\t\t- tAtNewRay"<< tAtRay <<"\n";
//	std::cout << "tAtR [ "<<tAtR<<" ] - " << "tAtRay [ "<<tAtRay<<" ] \n";
//	if (hit)
//		assert (tAtR != tAtRay);

	return (hit);
}

bool HitableInstance::Init()
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
