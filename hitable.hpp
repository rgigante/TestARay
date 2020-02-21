//
//  hitable.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"
#include "bbox.hpp"
#include "matrix.hpp"

#define USE_BBOX

class Material;
class Matrix;

struct HitRecord
{
	float t = 0; // the ray parameter at hit point
	Vec3 p = Vec3(0,0,0); // the position in space at hit point
	Vec3 n = Vec3(0,0,0); // the normal at hit point
	Material const * mat = nullptr; // the material found at the hit point
	unsigned long objID = 0; // the object ID hit point
	
	friend std::ostream& operator<<(std::ostream &os, const HitRecord& h)
	{
		std::cout << std::fixed;
		os << "t[" << h.t << "]"<<
		" / p[" << h.p << "]"<<
		" / n[" << h.n << "]"<<
		" / objID[" << h.objID << "]";
		
		return os;
	}
};

class Hitable
{
public:
	virtual ~Hitable(){}
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
	// name-related methods
	bool SetName(char const * name){ _name = name; return (!name) ? false : true; };
	char const * GetName(){ if (_name) return _name; return nullptr;}
	
	// visibility-related methods
	void SetVisible(const bool visible){ _visible = visible; return; };
	bool IsVisible(){ return _visible;}
	
	// objectID-related methods
	void SetObjID(unsigned long objID){ _objID = objID; return; };
	unsigned long GetObjID(){ return _objID;}
	
	// material-related methods
	bool SetMaterial(Material const * mat){ _mat = mat; return (!mat) ? false : true; };
	Material const * GetMaterial()  { if (_mat) return _mat; return nullptr;}
	
	// bbox-related methods
	BBox * GetBBox() { return &_bbox; }
	
	// transformation-related methods
	bool InitTransformation();
	const Matrix& GetMatrixAt(int idx) { return _mtrs[idx]; }
	void DropMatrixAt(int idx){	_mtrs.erase(_mtrs.begin() + idx);	}
	void AddMatrix(Matrix trf){	_mtrs.push_back(trf);	}
	const Matrix& GetGlobalMatrix() { return _gm; }
	const Matrix& GetGlobalInverseMatrix() { return _gim; }
	
	// Virtual methods (override in derived classes)
	virtual bool HitPrimitive (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false) = 0;
	
private:
	// the transformation stack
	std::vector<Matrix> _mtrs;
	// the global transformation matrix
	Matrix _gm = Matrix();
	// the global inverse transformation matrix
	Matrix _gim = Matrix();
	// the visiblity flag
	bool _visible = true;
	// the index to the object;
	unsigned long _objID = 0;
	// the pointer to the material assigned to the hitable
	Material const * _mat = nullptr;
	// the pointer to the string assigned to the hitable
	char const * _name = "";
	// the hitable BBox (aabb)
	BBox _bbox;
	
};

#endif /* hitable_hpp */
