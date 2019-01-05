//
//  hitablearray.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef hitablearray_hpp
#define hitablearray_hpp

#include "hitable.hpp"

class HitableArray : public Hitable
{
public:
	HitableArray(){}
	HitableArray(Hitable** h, int n) { _hitables = h; _hitablesSize = n; }
	~HitableArray();
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec) const;
	
private:
	Hitable** _hitables;
	int _hitablesSize;
};

#endif /* hitablearray_hpp */
