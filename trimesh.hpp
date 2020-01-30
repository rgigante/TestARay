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
	TriMesh(char const* name, int trisCnt, Material* mat);
	~TriMesh();
	
	bool Hit (const Ray& r, float t_min, float t_max, HitRecord& rec, Matrix* gm = nullptr, bool debugRay = false);
	
	bool SetVertexes(Vec3* points, int pointsCnt);
	bool SetTriIndexes(int* triIndexes);
	bool Init();
	int GetVertexesCnt(){ return _vertexesCnt; }
	int GetTrisCnt(){ return _trisCnt; }
	Triangle2* GetTriangleAtIndex(int triIdx);
	
	const Matrix& GetMatrixAt(int idx) { return _mtrs[idx]; }
	void DropMatrixAt(int idx){	_mtrs.erase(_mtrs.begin() + idx);	}
	void AddMatrix(Matrix trf){	_mtrs.push_back(trf);	}
	
private:
	Vec3* _vertexes;
	int _vertexesCnt;
	int* _triIndexes;
	int _trisCnt;
	Triangle2** _tris;
	Material* _mat;
	
	std::vector<Matrix> _mtrs;
	std::vector<Matrix> _invmtrs;
	Matrix _gm, _gim;
};

#endif /* trimesh_hpp */
