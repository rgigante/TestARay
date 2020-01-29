//
//  triangle.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 05/01/2019.
//

#ifndef triangle_hpp
#define triangle_hpp

#include "matrix.hpp"
#include "hitable.hpp"
#include "materials.hpp"

class Triangle: public Hitable
{
public:
//	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false);
	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false, Matrix* gm = nullptr);
	~Triangle();
	bool SetName(char const* name){ _name = name; return (!name) ? false : true; };
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	
private:
	Vec3 _a, _b, _c, _ab, _bc, _ca, _n;
	Material* _mat;
	char const* _name;
	Matrix* _gm;
	bool _isTriMesh;
};

class Triangle2: public Hitable
{
public:
	//	Triangle(char const* name, Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false);
	Triangle2(Vec3 a, Vec3 b, Vec3 c, Material* m, bool isTriMesh = false, Matrix* gm = nullptr);
	~Triangle2();
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	
private:
	Vec3 _a, _b, _c, _ab, _bc, _ca, _n;
	Material* _mat;
	Matrix* _gm;
	bool _isTriMesh;
};

#endif /* triangle_hpp */
