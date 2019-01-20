//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"

bool HitableInstance::Hit(const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance) const
{
	Vec3 pos = r.GetOrigin();
	for (int i = 0; i < _trfs.size(); ++i)
	{
		Transformation trf = _trfs[i];
		pos = ~trf * pos;
	}
	return (_obj->Hit(Ray(pos, r.GetDirection()), t_min, t_max, rec, true));
}
