//
//  trimesh.hpp
//  TraceARay01
//
//  Created by Riccardo Gigante on 10/01/2019.
//

#ifndef trimesh_hpp
#define trimesh_hpp

#include "matrix.hpp"
#include "triangle.hpp"

class TriMesh: public Hitable
{
public:
	TriMesh(char const * name, int trisCnt, Material const * mat);
	~TriMesh();
	bool Hit2 (const Ray& r, float t_min, float t_max, HitRecord& rec, bool debugRay = false);
	
	bool SetVertexes(Vec3* points, int pointsCnt);
	bool SetTriIndexes(int* triIndexes);
	bool InitTris();
	int GetVertexesCnt(){ return _vertexesCnt; }
	int GetTrisCnt(){ return _trisCnt; }
	Triangle2* GetTriangleAtIndex(int triIdx);
		
private:
	Vec3* _vertexes;
	int _vertexesCnt;
	int* _triIndexes;
	int _trisCnt;
	Triangle2** _tris;
//	Material* _mat;
	
	std::vector<Matrix> _mtrs;
	std::vector<Matrix> _invmtrs;
	Matrix _gm, _gim;
};

#endif /* trimesh_hpp */
