//
//  hitablearray.cpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#include "hitablearray.hpp"

HitableArray::~HitableArray()
{
	for (int i = 0; i < _hitablesSize; ++i)
	{
		delete (_hitables[i]);
		_hitables[i] = nullptr;
	}
}

bool HitableArray::Hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t_max;
	
	for (int i = 0; i < _hitablesSize; ++i)
	{
		if (_hitables[i] && _hitables[i]->Hit(r, t_min, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}

