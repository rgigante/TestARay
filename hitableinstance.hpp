//
//  hitable_instance.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#ifndef hitable_instance_hpp
#define hitable_instance_hpp

#include "hitable.hpp"
#include "transformation.hpp"

class HitableInstance : public Hitable
{
public:
	HitableInstance(Hitable* obj):_obj(obj){}
	~HitableInstance(){}
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool isInstance = false) const;
	const Transformation& GetTransformationAt(int idx) { return _trfs[idx]; }
	void DropTransformationAt(int idx){	_trfs.erase(_trfs.begin() + idx);	}
	void AddTransformation(Transformation trf){	_trfs.push_back(trf);	}
	
private:
	Hitable* _obj;
	
	std::vector<Transformation> _trfs;
};

#endif /* hitable_instance_hpp */
