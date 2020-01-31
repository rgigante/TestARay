//
//  hitable_instance.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#ifndef hitable_instance_hpp
#define hitable_instance_hpp

#include "hitable.hpp"

class HitableInstance : public Hitable
{
public:
	HitableInstance(Hitable* obj):_obj(obj){}
	~HitableInstance(){}
	
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
private:
	Hitable* _obj;
};

#endif /* hitable_instance_hpp */
