//
//  hitable_instance.hpp
//  TraceARay
//
//  Created by Riccardo Gigante on 19/01/2019.
//

#ifndef hitable_instance_hpp
#define hitable_instance_hpp

#include "hitable.hpp"
#include "matrix.hpp"

class HitableInstance : public Hitable
{
public:
	HitableInstance(Hitable* obj):_obj(obj){}
	~HitableInstance(){}
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr);
	bool Init();
	const Matrix& GetMatrixAt(int idx) { return _mtrs[idx]; }
	void DropMatrixAt(int idx){	_mtrs.erase(_mtrs.begin() + idx);	}
	void AddMatrix(Matrix trf){	_mtrs.push_back(trf);	}
private:
	Hitable* _obj;
	
	std::vector<Matrix> _mtrs;
	std::vector<Matrix> _invmtrs;
	Matrix _gm, _gim;
	Material *_mat;
};

#endif /* hitable_instance_hpp */
