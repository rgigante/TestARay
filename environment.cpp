//
//  environment.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 15/02/2020.
//

#include "environment.hpp"



bool Environment::SetName(char const * name)
{
	_name = name;
	return (!name) ? false : true;
}

char const * Environment::GetName()
{
	if (_name)
		return _name;
	return nullptr;
}

Vec3 Gradient::Col(const Ray &rHit) const
{
	const float blend = _r * (rHit.GetDirection().y() + 1.0);
	return (Lerp(_c1, _c2, blend));
}
