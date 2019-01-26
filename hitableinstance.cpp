//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"

bool HitableInstance::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm)
{
	return (_obj->Hit(r, t_min, t_max, rec, &_gm));
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
