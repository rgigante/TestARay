//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"

bool HitableInstance::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm, bool debugRay /*= false*/)
{
	Ray ray = Ray(_gim * r.GetOrigin(), (_gim.Get3x3() * r.GetDirection()).GetNormalized());
	bool hit = _obj->Hit(ray, t_min, t_max, rec, &_gm);
	float tAtR = r.ParameterAtPoint(rec.p);
	float tAtRay = ray.ParameterAtPoint(rec.p);
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
