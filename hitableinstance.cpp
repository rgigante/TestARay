//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"

#ifdef NEW_HITABLE
bool HitableInstance::Hit2(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	// store the material for the current hitable
	Material const * objMat = _obj->GetMaterial();
	
	// override material to use the one assigned to the hitableinstance
	_obj->SetMaterial(GetMaterial());
	
	// hit using the overriden material
	bool hit = _obj->Hit2(r, t_min, t_max, rec, debugRay);
	
	// restore the material originally assigned to the current hitable
	_obj->SetMaterial(objMat);
	
	return (hit);
}
#else
bool HitableInstance::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay /*= false*/)
{
	Ray ray(r);
	ray.SetDirection((_gim.Get3x3() * r.GetDirection()));
	ray.SetOrigin(_gim * r.GetOrigin());
	
	if (debugRay) std::cout << "\t\t\t(instance intersection)\n"<<
		"\t\t\t- oldray:"<< r << "\n"<<
		"\t\t\t- newray:"<< ray <<"\n";
	bool hit = _obj->Hit(ray, t_min, t_max, rec, nullptr, debugRay);
	float tAtR = r.ParameterAtPoint(rec.p);
	float tAtRay = ray.ParameterAtPoint(rec.p);
	rec.p = _gm * rec.p;
//	rec.n = (_gm.Get3x3() * rec.n).GetNormalized();
	rec.n = (_gim.Get3x3().Transpose() * rec.n).GetNormalized();
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
#endif
