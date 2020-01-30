//
//  hitable.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 04/01/2019.
//

#ifndef hitable_hpp
#define hitable_hpp

#include "ray.hpp"
#include "matrix.hpp"

#define NEW_HITABLE

class Material;
class Matrix;

struct HitRecord
{
	float t = 0; // the ray parameter at hit point
	Vec3 p = Vec3(0,0,0); // the position in space at hit point
	Vec3 n = Vec3(0,0,0); // the normal at hit point
	Material* mat = nullptr; // the material found at the hit point
	
	friend std::ostream& operator<<(std::ostream &os, const HitRecord& h)
	{
		std::cout << std::fixed;
		os << "t[" << h.t << "] / p[" << h.p << "] / n[" << h.n << "]";
		return os;
	}
};

class Hitable
{
#ifdef NEW_HITABLE
public:
	virtual ~Hitable(){}
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	
	virtual bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false) = 0;
	
	bool SetName(char const* name){ _name = name; return (!name) ? false : true; };
	char const* GetName(){ if (_name) return _name; return nullptr;}
	
	bool Init();
	
	const Matrix& GetMatrixAt(int idx) { return _mtrs[idx]; }
	const Matrix& GetInverseMatrixAt(int idx) { return _invmtrs[idx]; }
	void DropMatrixAt(int idx){	_mtrs.erase(_mtrs.begin() + idx);	}
	void AddMatrix(Matrix trf){	_mtrs.push_back(trf);	}
	const Matrix& GetGlobalMatrix() { return _gm; }
	const Matrix& GetGlobalInverseMatrix() { return _gim; }
	
public:
	char const* _name = "";
	
	std::vector<Matrix> _mtrs;
	std::vector<Matrix> _invmtrs;
	Matrix _gm, _gim;
	Material *_mat;
#else
public:
	virtual ~Hitable(){}
	virtual bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false) = 0;
	bool SetName(char const* name){ _name = name; return (!name) ? false : true; };
	char const* GetName(){ if (_name) return _name; return nullptr;}
	
public:
	char const* _name = "";
#endif
};

#endif /* hitable_hpp */
