//
//  hitable_instance.cpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#include "hitableinstance.hpp"

bool HitableInstance::Hit2(const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay /*= false*/)
{
	// store the material for the current hitable
	Material const * objMat = _obj->GetMaterial();
	
	bool hitDetected = false;
	
	// use instance's material only if it has been assigned
	if (GetMaterial())
	{	// override material to use the one assigned to the hitableinstance
		_obj->SetMaterial(GetMaterial());
		
		// hit using the overriden material
		hitDetected = _obj->Hit2(r, t_min, t_max, rec, debugRay);
		
		// restore the material originally assigned to the current hitable
		_obj->SetMaterial(objMat);
	}
	else
		hitDetected = _obj->Hit2(r, t_min, t_max, rec, debugRay);
		
	
	return (hitDetected);
}
